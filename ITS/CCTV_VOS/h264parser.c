/*
 * h264parser.c
 *
 *  Created on: Dec 19, 2012
 *      Author: hungnv
 */

#include <stdio.h>
#include <stdlib.h>
#include "bs.h"
#include "h264parser.h"
#include <stdint.h>
#include <string.h>

//Appendix E. Table E-1  Meaning of sample aspect ratio indicator
#define SAR_Unspecified  0           // Unspecified
#define SAR_1_1        1             //  1:1
#define SAR_12_11      2             // 12:11
#define SAR_10_11      3             // 10:11
#define SAR_16_11      4             // 16:11
#define SAR_40_33      5             // 40:33
#define SAR_24_11      6             // 24:11
#define SAR_20_11      7             // 20:11
#define SAR_32_11      8             // 32:11
#define SAR_80_33      9             // 80:33
#define SAR_18_11     10             // 18:11
#define SAR_15_11     11             // 15:11
#define SAR_64_33     12             // 64:33
#define SAR_160_99    13             // 160:99
                                     // 14..254           Reserved
#define SAR_Extended      255        // Extended_SAR

/**
   Sequence Parameter Set
   @see 7.3.2.1 Sequence parameter set RBSP syntax
   @see read_seq_parameter_set_rbsp
   @see write_seq_parameter_set_rbsp
   @see debug_sps
*/
typedef struct
{
    int profile_idc;
    int constraint_set0_flag;
    int constraint_set1_flag;
    int constraint_set2_flag;
    int constraint_set3_flag;
    int constraint_set4_flag;
    int constraint_set5_flag;
    int reserved_zero_2bits;
    int level_idc;
    int seq_parameter_set_id;
    int chroma_format_idc;
    int residual_colour_transform_flag;
    int bit_depth_luma_minus8;
    int bit_depth_chroma_minus8;
    int qpprime_y_zero_transform_bypass_flag;
    int seq_scaling_matrix_present_flag;
      int seq_scaling_list_present_flag[8];
      int* ScalingList4x4[6];
      int UseDefaultScalingMatrix4x4Flag[6];
      int* ScalingList8x8[2];
      int UseDefaultScalingMatrix8x8Flag[2];
    int log2_max_frame_num_minus4;
    int pic_order_cnt_type;
      int log2_max_pic_order_cnt_lsb_minus4;
      int delta_pic_order_always_zero_flag;
      int offset_for_non_ref_pic;
      int offset_for_top_to_bottom_field;
      int num_ref_frames_in_pic_order_cnt_cycle;
      int offset_for_ref_frame[256];
    int num_ref_frames;
    int gaps_in_frame_num_value_allowed_flag;
    int pic_width_in_mbs_minus1;
    int pic_height_in_map_units_minus1;
    int frame_mbs_only_flag;
    int mb_adaptive_frame_field_flag;
    int direct_8x8_inference_flag;
    int frame_cropping_flag;
      int frame_crop_left_offset;
      int frame_crop_right_offset;
      int frame_crop_top_offset;
      int frame_crop_bottom_offset;
    int vui_parameters_present_flag;

    struct
    {
        int aspect_ratio_info_present_flag;
          int aspect_ratio_idc;
            int sar_width;
            int sar_height;
        int overscan_info_present_flag;
          int overscan_appropriate_flag;
        int video_signal_type_present_flag;
          int video_format;
          int video_full_range_flag;
          int colour_description_present_flag;
            int colour_primaries;
            int transfer_characteristics;
            int matrix_coefficients;
        int chroma_loc_info_present_flag;
          int chroma_sample_loc_type_top_field;
          int chroma_sample_loc_type_bottom_field;
        int timing_info_present_flag;
          int num_units_in_tick;
          int time_scale;
          int fixed_frame_rate_flag;
        int nal_hrd_parameters_present_flag;
        int vcl_hrd_parameters_present_flag;
          int low_delay_hrd_flag;
        int pic_struct_present_flag;
        int bitstream_restriction_flag;
          int motion_vectors_over_pic_boundaries_flag;
          int max_bytes_per_pic_denom;
          int max_bits_per_mb_denom;
          int log2_max_mv_length_horizontal;
          int log2_max_mv_length_vertical;
          int num_reorder_frames;
          int max_dec_frame_buffering;
    } vui;

    struct
    {
        int cpb_cnt_minus1;
        int bit_rate_scale;
        int cpb_size_scale;
          int bit_rate_value_minus1[32]; // up to cpb_cnt_minus1, which is <= 31
          int cpb_size_value_minus1[32];
          int cbr_flag[32];
        int initial_cpb_removal_delay_length_minus1;
        int cpb_removal_delay_length_minus1;
        int dpb_output_delay_length_minus1;
        int time_offset_length;
    } hrd;

} sps_t;


/**
   Picture Parameter Set
   @see 7.3.2.2 Picture parameter set RBSP syntax
   @see read_pic_parameter_set_rbsp
   @see write_pic_parameter_set_rbsp
   @see debug_pps
*/
typedef struct
{
    int pic_parameter_set_id;
    int seq_parameter_set_id;
    int entropy_coding_mode_flag;
    int pic_order_present_flag;
    int num_slice_groups_minus1;
    int slice_group_map_type;
      int run_length_minus1[8]; // up to num_slice_groups_minus1, which is <= 7 in Baseline and Extended, 0 otheriwse
      int top_left[8];
      int bottom_right[8];
      int slice_group_change_direction_flag;
      int slice_group_change_rate_minus1;
      int pic_size_in_map_units_minus1;
      int slice_group_id[256]; // FIXME what size?
    int num_ref_idx_l0_active_minus1;
    int num_ref_idx_l1_active_minus1;
    int weighted_pred_flag;
    int weighted_bipred_idc;
    int pic_init_qp_minus26;
    int pic_init_qs_minus26;
    int chroma_qp_index_offset;
    int deblocking_filter_control_present_flag;
    int constrained_intra_pred_flag;
    int redundant_pic_cnt_present_flag;

    // set iff we carry any of the optional headers
    int _more_rbsp_data_present;

    int transform_8x8_mode_flag;
    int pic_scaling_matrix_present_flag;
       int pic_scaling_list_present_flag[8];
       int* ScalingList4x4[6];
       int UseDefaultScalingMatrix4x4Flag[6];
       int* ScalingList8x8[2];
       int UseDefaultScalingMatrix8x8Flag[2];
    int second_chroma_qp_index_offset;
} pps_t;


/**
  Slice Header
  @see 7.3.3 Slice header syntax
  @see read_slice_header_rbsp
  @see write_slice_header_rbsp
  @see debug_slice_header_rbsp
*/
typedef struct
{
    int first_mb_in_slice;
    int slice_type;
    int pic_parameter_set_id;
    int frame_num;
    int field_pic_flag;
      int bottom_field_flag;
    int idr_pic_id;
    int pic_order_cnt_lsb;
    int delta_pic_order_cnt_bottom;
    int delta_pic_order_cnt[ 2 ];
    int redundant_pic_cnt;
    int direct_spatial_mv_pred_flag;
    int num_ref_idx_active_override_flag;
    int num_ref_idx_l0_active_minus1;
    int num_ref_idx_l1_active_minus1;
    int cabac_init_idc;
    int slice_qp_delta;
    int sp_for_switch_flag;
    int slice_qs_delta;
    int disable_deblocking_filter_idc;
    int slice_alpha_c0_offset_div2;
    int slice_beta_offset_div2;
    int slice_group_change_cycle;


    struct
    {
        int luma_log2_weight_denom;
        int chroma_log2_weight_denom;
        int luma_weight_l0_flag[64];
        int luma_weight_l0[64];
        int luma_offset_l0[64];
        int chroma_weight_l0_flag[64];
        int chroma_weight_l0[64][2];
        int chroma_offset_l0[64][2];
        int luma_weight_l1_flag[64];
        int luma_weight_l1[64];
        int luma_offset_l1[64];
        int chroma_weight_l1_flag[64];
        int chroma_weight_l1[64][2];
        int chroma_offset_l1[64][2];
    } pwt; // predictive weight table

    struct // FIXME stack or array
    {
        int ref_pic_list_reordering_flag_l0;
        int ref_pic_list_reordering_flag_l1;
        int reordering_of_pic_nums_idc;
        int abs_diff_pic_num_minus1;
        int long_term_pic_num;
    } rplr; // ref pic list reorder

    struct // FIXME stack or array
    {
        int no_output_of_prior_pics_flag;
        int long_term_reference_flag;
        int adaptive_ref_pic_marking_mode_flag;
        int memory_management_control_operation;
        int difference_of_pic_nums_minus1;
        int long_term_pic_num;
        int long_term_frame_idx;
        int max_long_term_frame_idx_plus1;
    } drpm; // decoded ref pic marking

} slice_header_t;


/**
   Access unit delimiter
   @see 7.3.1 NAL unit syntax
   @see read_nal_unit
   @see write_nal_unit
   @see debug_nal
*/
typedef struct
{
    int primary_pic_type;
} aud_t;

/**
   Network Abstraction Layer (NAL) unit
   @see 7.3.1 NAL unit syntax
   @see read_nal_unit
   @see write_nal_unit
   @see debug_nal
*/
typedef struct
{
    int forbidden_zero_bit;
    int nal_ref_idc;
    int nal_unit_type;
    void* parsed; // FIXME
    int sizeof_parsed;

    //uint8_t* rbsp_buf;
    //int rbsp_size;
} nal_t;

typedef struct
{
    int _is_initialized;
    int sps_id;
    int initial_cpb_removal_delay;
    int initial_cpb_delay_offset;
} sei_buffering_t;

typedef struct
{
    int clock_timestamp_flag;
        int ct_type;
        int nuit_field_based_flag;
        int counting_type;
        int full_timestamp_flag;
        int discontinuity_flag;
        int cnt_dropped_flag;
        int n_frames;

        int seconds_value;
        int minutes_value;
        int hours_value;

        int seconds_flag;
        int minutes_flag;
        int hours_flag;

        int time_offset;
} picture_timestamp_t;

typedef struct
{
  int _is_initialized;
  int cpb_removal_delay;
  int dpb_output_delay;
  int pic_struct;
  picture_timestamp_t clock_timestamps[3]; // 3 is the maximum possible value
} sei_picture_timing_t;

typedef struct
{
    int payloadType;
    int payloadSize;
    uint8_t* payload;
} sei_t;


typedef struct
{
  int rbsp_size;
  uint8_t* rbsp_buf;
} slice_data_rbsp_t;

/**
   H264 stream
   Contains data structures for all NAL types that can be handled by this library.
   When reading, data is read into those, and when writing it is written from those.
   The reason why they are all contained in one place is that some of them depend on others, we need to
   have all of them available to read or write correctly.
 */
typedef struct
{
    nal_t* nal;
    sps_t* sps;
    pps_t* pps;
    aud_t* aud;
    sei_t* sei; //This is a TEMP pointer at whats in h->seis...
    int num_seis;
    slice_header_t* sh;
    slice_data_rbsp_t* slice_data;

    sps_t* sps_table[32];
    pps_t* pps_table[256];
    sei_t** seis;

} h264_stream_t;

/***************************** reading ******************************/

/**
 Create a new H264 stream object.  Allocates all structures contained within it.
 @return    the stream object
 */
static h264_stream_t* h264_new()
{
	//printf("size of h264_stream_t = %d\n", sizeof(h264_stream_t));
    //h264_stream_t* h = (h264_stream_t*)calloc(1, sizeof(h264_stream_t));
	h264_stream_t* h = (h264_stream_t*)malloc(sizeof(h264_stream_t));

    h->nal = (nal_t*)calloc(1, sizeof(nal_t));

    // initialize tables
    int i;
    for ( i = 0; i < 32; i++ ) { h->sps_table[i] = (sps_t*)calloc(1, sizeof(sps_t)); }
    for ( i = 0; i < 256; i++ ) { h->pps_table[i] = (pps_t*)calloc(1, sizeof(pps_t)); }

    h->sps = h->sps_table[0];
    h->pps = h->pps_table[0];
    h->aud = (aud_t*)calloc(1, sizeof(aud_t));
    h->num_seis = 0;
    h->seis = NULL;
    h->sei = NULL;  //This is a TEMP pointer at whats in h->seis...
    h->sh = (slice_header_t*)calloc(1, sizeof(slice_header_t));

    return h;
}

sei_t* sei_new()
{
    sei_t* s = (sei_t*)malloc(sizeof(sei_t));
    memset(s, 0, sizeof(sei_t));
    s->payload = NULL;
    return s;
}

void sei_free(sei_t* s)
{
    if ( s->payload != NULL ) free(s->payload);
    free(s);
}


/**
 Free an existing H264 stream object.  Frees all contained structures.
 @param[in,out] h   the stream object
 */
static void h264_free(h264_stream_t* h)
{
    free(h->nal);

    int i;
    for ( i = 0; i < 32; i++ ) { free( h->sps_table[i] ); }
    for ( i = 0; i < 256; i++ ) { free( h->pps_table[i] ); }

    free(h->aud);
    if(h->seis != NULL)
    {
        for( i = 0; i < h->num_seis; i++ )
        {
            sei_t* sei = h->seis[i];
            sei_free(sei);
        }
        free(h->seis);
    }
    free(h->sh);
    free(h);
}

/**
   Convert NAL data (Annex B format) to RBSP data.
   The size of rbsp_buf must be the same as size of the nal_buf to guarantee the output will fit.
   If that is not true, output may be truncated and an error will be returned.
   Additionally, certain byte sequences in the input nal_buf are not allowed in the spec and also cause the conversion to fail and an error to be returned.
   @param[in] nal_buf   the nal data
   @param[in,out] nal_size  as input, pointer to the size of the nal data; as output, filled in with the actual size of the nal data
   @param[in,out] rbsp_buf   allocated memory in which to put the rbsp data
   @param[in,out] rbsp_size  as input, pointer to the maximum size of the rbsp data; as output, filled in with the actual size of rbsp data
   @return  actual size of rbsp data, or -1 on error
 */
// 7.3.1 NAL unit syntax
// 7.4.1.1 Encapsulation of an SODB within an RBSP
static int nal_to_rbsp(const uint8_t* nal_buf, int* nal_size, uint8_t* rbsp_buf, int* rbsp_size)
{
    int i;
    int j     = 0;
    int count = 0;

    for( i = 1; i < *nal_size; i++ )
    {
        // in NAL unit, 0x000000, 0x000001 or 0x000002 shall not occur at any byte-aligned position
        if( ( count == 2 ) && ( nal_buf[i] < 0x03) )
        {
            return -1;
        }

        if( ( count == 2 ) && ( nal_buf[i] == 0x03) )
        {
            // check the 4th byte after 0x000003, except when cabac_zero_word is used, in which case the last three bytes of this NAL unit must be 0x000003
            if((i < *nal_size - 1) && (nal_buf[i+1] > 0x03))
            {
                return -1;
            }

            // if cabac_zero_word is used, the final byte of this NAL unit(0x03) is discarded, and the last two bytes of RBSP must be 0x0000
            if(i == *nal_size - 1)
            {
                break;
            }

            i++;
            count = 0;
        }

        if ( j >= *rbsp_size )
        {
            // error, not enough space
            return -1;
        }

        rbsp_buf[j] = nal_buf[i];
        if(nal_buf[i] == 0x00)
        {
            count++;
        }
        else
        {
            count = 0;
        }
        j++;
    }

    *nal_size = i;
    *rbsp_size = j;
    return j;
}

//Appendix E.1.2 HRD parameters syntax
void read_hrd_parameters(h264_stream_t* h, bs_t* b)
{
    sps_t* sps = h->sps;
    int SchedSelIdx;

    sps->hrd.cpb_cnt_minus1 = bs_read_ue(b);
    sps->hrd.bit_rate_scale = bs_read_u(b,4);
    sps->hrd.cpb_size_scale = bs_read_u(b,4);
    for( SchedSelIdx = 0; SchedSelIdx <= sps->hrd.cpb_cnt_minus1; SchedSelIdx++ )
    {
        sps->hrd.bit_rate_value_minus1[ SchedSelIdx ] = bs_read_ue(b);
        sps->hrd.cpb_size_value_minus1[ SchedSelIdx ] = bs_read_ue(b);
        sps->hrd.cbr_flag[ SchedSelIdx ] = bs_read_u1(b);
    }
    sps->hrd.initial_cpb_removal_delay_length_minus1 = bs_read_u(b,5);
    sps->hrd.cpb_removal_delay_length_minus1 = bs_read_u(b,5);
    sps->hrd.dpb_output_delay_length_minus1 = bs_read_u(b,5);
    sps->hrd.time_offset_length = bs_read_u(b,5);
}

//Appendix E.1.1 VUI parameters syntax
static void read_vui_parameters(h264_stream_t* h, bs_t* b)
{
    sps_t* sps = h->sps;

    sps->vui.aspect_ratio_info_present_flag = bs_read_u1(b);
    if( sps->vui.aspect_ratio_info_present_flag )
    {
        sps->vui.aspect_ratio_idc = bs_read_u8(b);
        if( sps->vui.aspect_ratio_idc == SAR_Extended )
        {
            sps->vui.sar_width = bs_read_u(b,16);
            sps->vui.sar_height = bs_read_u(b,16);
        }
    }
    sps->vui.overscan_info_present_flag = bs_read_u1(b);
    if( sps->vui.overscan_info_present_flag )
    {
        sps->vui.overscan_appropriate_flag = bs_read_u1(b);
    }
    sps->vui.video_signal_type_present_flag = bs_read_u1(b);
    if( sps->vui.video_signal_type_present_flag )
    {
        sps->vui.video_format = bs_read_u(b,3);
        sps->vui.video_full_range_flag = bs_read_u1(b);
        sps->vui.colour_description_present_flag = bs_read_u1(b);
        if( sps->vui.colour_description_present_flag )
        {
            sps->vui.colour_primaries = bs_read_u8(b);
            sps->vui.transfer_characteristics = bs_read_u8(b);
            sps->vui.matrix_coefficients = bs_read_u8(b);
        }
    }
    sps->vui.chroma_loc_info_present_flag = bs_read_u1(b);
    if( sps->vui.chroma_loc_info_present_flag )
    {
        sps->vui.chroma_sample_loc_type_top_field = bs_read_ue(b);
        sps->vui.chroma_sample_loc_type_bottom_field = bs_read_ue(b);
    }
    sps->vui.timing_info_present_flag = bs_read_u1(b);
    if( sps->vui.timing_info_present_flag )
    {
        sps->vui.num_units_in_tick = bs_read_u(b,32);
        sps->vui.time_scale = bs_read_u(b,32);
        sps->vui.fixed_frame_rate_flag = bs_read_u1(b);
    }
    sps->vui.nal_hrd_parameters_present_flag = bs_read_u1(b);
    if( sps->vui.nal_hrd_parameters_present_flag )
    {
        read_hrd_parameters(h, b);
    }
    sps->vui.vcl_hrd_parameters_present_flag = bs_read_u1(b);
    if( sps->vui.vcl_hrd_parameters_present_flag )
    {
        read_hrd_parameters(h, b);
    }
    if( sps->vui.nal_hrd_parameters_present_flag || sps->vui.vcl_hrd_parameters_present_flag )
    {
        sps->vui.low_delay_hrd_flag = bs_read_u1(b);
    }
    sps->vui.pic_struct_present_flag = bs_read_u1(b);
    sps->vui.bitstream_restriction_flag = bs_read_u1(b);
    if( sps->vui.bitstream_restriction_flag )
    {
        sps->vui.motion_vectors_over_pic_boundaries_flag = bs_read_u1(b);
        sps->vui.max_bytes_per_pic_denom = bs_read_ue(b);
        sps->vui.max_bits_per_mb_denom = bs_read_ue(b);
        sps->vui.log2_max_mv_length_horizontal = bs_read_ue(b);
        sps->vui.log2_max_mv_length_vertical = bs_read_ue(b);
        sps->vui.num_reorder_frames = bs_read_ue(b);
        sps->vui.max_dec_frame_buffering = bs_read_ue(b);
    }
}

//7.3.2.11 RBSP trailing bits syntax
static void read_rbsp_trailing_bits(h264_stream_t* h, bs_t* b)
{
    int rbsp_stop_one_bit = bs_read_u1( b ); // equal to 1

    while( !bs_byte_aligned(b) )
    {
        int rbsp_alignment_zero_bit = bs_read_u1( b ); // equal to 0
    }
}

//7.3.2.1.1 Scaling list syntax
void read_scaling_list(bs_t* b, int* scalingList, int sizeOfScalingList, int useDefaultScalingMatrixFlag )
{
    int j;
    if(scalingList == NULL)
    {
        return;
    }

    int lastScale = 8;
    int nextScale = 8;
    for( j = 0; j < sizeOfScalingList; j++ )
    {
        if( nextScale != 0 )
        {
            int delta_scale = bs_read_se(b);
            nextScale = ( lastScale + delta_scale + 256 ) % 256;
            useDefaultScalingMatrixFlag = ( j == 0 && nextScale == 0 );
        }
        scalingList[ j ] = ( nextScale == 0 ) ? lastScale : nextScale;
        lastScale = scalingList[ j ];
    }
}

//7.3.2.1 Sequence parameter set RBSP syntax
static void read_seq_parameter_set_rbsp(h264_stream_t* h, bs_t* b)
{
    int i;

    // NOTE can't read directly into sps because seq_parameter_set_id not yet known and so sps is not selected

    int profile_idc = bs_read_u8(b);
    int constraint_set0_flag = bs_read_u1(b);
    int constraint_set1_flag = bs_read_u1(b);
    int constraint_set2_flag = bs_read_u1(b);
    int constraint_set3_flag = bs_read_u1(b);
    int constraint_set4_flag = bs_read_u1(b);
    int constraint_set5_flag = bs_read_u1(b);
    int reserved_zero_2bits  = bs_read_u(b,2);  /* all 0's */
    int level_idc = bs_read_u8(b);
    int seq_parameter_set_id = bs_read_ue(b);

    // select the correct sps
    h->sps = h->sps_table[seq_parameter_set_id];
    sps_t* sps = h->sps;
    memset(sps, 0, sizeof(sps_t));

    sps->chroma_format_idc = 1;

    sps->profile_idc = profile_idc; // bs_read_u8(b);
    sps->constraint_set0_flag = constraint_set0_flag;//bs_read_u1(b);
    sps->constraint_set1_flag = constraint_set1_flag;//bs_read_u1(b);
    sps->constraint_set2_flag = constraint_set2_flag;//bs_read_u1(b);
    sps->constraint_set3_flag = constraint_set3_flag;//bs_read_u1(b);
    sps->constraint_set4_flag = constraint_set4_flag;//bs_read_u1(b);
    sps->constraint_set5_flag = constraint_set5_flag;//bs_read_u1(b);
    sps->reserved_zero_2bits = reserved_zero_2bits;//bs_read_u(b,2);
    sps->level_idc = level_idc; //bs_read_u8(b);
    sps->seq_parameter_set_id = seq_parameter_set_id; // bs_read_ue(b);
    if( sps->profile_idc == 100 || sps->profile_idc == 110 ||
        sps->profile_idc == 122 || sps->profile_idc == 144 )
    {
        sps->chroma_format_idc = bs_read_ue(b);
        if( sps->chroma_format_idc == 3 )
        {
            sps->residual_colour_transform_flag = bs_read_u1(b);
        }
        sps->bit_depth_luma_minus8 = bs_read_ue(b);
        sps->bit_depth_chroma_minus8 = bs_read_ue(b);
        sps->qpprime_y_zero_transform_bypass_flag = bs_read_u1(b);
        sps->seq_scaling_matrix_present_flag = bs_read_u1(b);
        if( sps->seq_scaling_matrix_present_flag )
        {
            for( i = 0; i < 8; i++ )
            {
                sps->seq_scaling_list_present_flag[ i ] = bs_read_u1(b);
                if( sps->seq_scaling_list_present_flag[ i ] )
                {
                    if( i < 6 )
                    {
                        read_scaling_list( b, sps->ScalingList4x4[ i ], 16,
                                      sps->UseDefaultScalingMatrix4x4Flag[ i ]);
                    }
                    else
                    {
                        read_scaling_list( b, sps->ScalingList8x8[ i - 6 ], 64,
                                      sps->UseDefaultScalingMatrix8x8Flag[ i - 6 ] );
                    }
                }
            }
        }
    }
    sps->log2_max_frame_num_minus4 = bs_read_ue(b);
    sps->pic_order_cnt_type = bs_read_ue(b);
    if( sps->pic_order_cnt_type == 0 )
    {
        sps->log2_max_pic_order_cnt_lsb_minus4 = bs_read_ue(b);
    }
    else if( sps->pic_order_cnt_type == 1 )
    {
        sps->delta_pic_order_always_zero_flag = bs_read_u1(b);
        sps->offset_for_non_ref_pic = bs_read_se(b);
        sps->offset_for_top_to_bottom_field = bs_read_se(b);
        sps->num_ref_frames_in_pic_order_cnt_cycle = bs_read_ue(b);
        for( i = 0; i < sps->num_ref_frames_in_pic_order_cnt_cycle; i++ )
        {
            sps->offset_for_ref_frame[ i ] = bs_read_se(b);
        }
    }
    sps->num_ref_frames = bs_read_ue(b);
    sps->gaps_in_frame_num_value_allowed_flag = bs_read_u1(b);
    sps->pic_width_in_mbs_minus1 = bs_read_ue(b);
    sps->pic_height_in_map_units_minus1 = bs_read_ue(b);
    sps->frame_mbs_only_flag = bs_read_u1(b);
    if( !sps->frame_mbs_only_flag )
    {
        sps->mb_adaptive_frame_field_flag = bs_read_u1(b);
    }
    sps->direct_8x8_inference_flag = bs_read_u1(b);
    sps->frame_cropping_flag = bs_read_u1(b);
    if( sps->frame_cropping_flag )
    {
        sps->frame_crop_left_offset = bs_read_ue(b);
        sps->frame_crop_right_offset = bs_read_ue(b);
        sps->frame_crop_top_offset = bs_read_ue(b);
        sps->frame_crop_bottom_offset = bs_read_ue(b);
    }
    sps->vui_parameters_present_flag = bs_read_u1(b);
    if( sps->vui_parameters_present_flag )
    {
        read_vui_parameters(h, b);
    }
    read_rbsp_trailing_bits(h, b);
}
/**************************************************************************************/

int h264_parse_sps(h264_common_info* info, unsigned char* buff, int length)
{
	//printf("h264_parse_sps was called\n");
	memset(info, 0, sizeof(h264_common_info));

	int nal_size = length;
	int rbsp_size = length;
	uint8_t* rbsp_buf = (uint8_t*)malloc(rbsp_size);
	int rc = nal_to_rbsp(buff, &nal_size, rbsp_buf, &rbsp_size);

	if (rc < 0)
	{
		printf("h264_parse_sps was called, but can not convert NAL into RBSP\n");
		free(rbsp_buf);
		return -1;
	} // handle conversion error

	bs_t* b = bs_new(rbsp_buf, rbsp_size);

	if(!b)
	{
		printf("h264_parse_sps was called but can not create bit stream\n");
		free(rbsp_buf);
		return -1;
	}

	h264_stream_t* h = h264_new();
	if(!h)
	{
		printf("h264_parse_sps was called but can not create H.264 structure\n");
		bs_free(b);
		free(rbsp_buf);
		return -1;
	}

	read_seq_parameter_set_rbsp(h, b);

	info->profile = h->sps->profile_idc;
	info->level_idc = h->sps->level_idc;
	info->width = (h->sps->pic_width_in_mbs_minus1 + 1) * 16;
	info->height = (h->sps->pic_height_in_map_units_minus1 + 1) * 16;

	if(h->sps->vui_parameters_present_flag && h->sps->vui.timing_info_present_flag)
	{
		info->fps_den = h->sps->vui.num_units_in_tick*2;
		info->fps_num = h->sps->vui.time_scale;
	}
	else
	{
		info->fps_den = 1001;
		info->fps_num = 30000;
	}

	/* some info need fixed */
	info->gop_size = 5; // can not determine from sps
	if(h->sps->vui.num_reorder_frames)
		info->max_b_frame = 3; // can not determine from sps
	else
		info->max_b_frame = 0;

	h264_free(h);
	bs_free(b);
	free(rbsp_buf);

	return 0;
}
