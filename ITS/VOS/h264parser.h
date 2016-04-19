/*
 * h264parser.h
 *
 *  Created on: Dec 19, 2012
 *      Author: hungnv
 */

#ifndef H264PARSER_H_
#define H264PARSER_H_

#ifdef __cplusplus

#define BEGIN_C_DECLARE extern "C" {
#define END_C_DECLARE }

#else

#define BEGIN_C_DECLARE
#define END_C_DECLARE

#endif

BEGIN_C_DECLARE

typedef struct h264_common_info_t
{
	int width;
	int height;
	int gop_size;
	int fps_num;
	int fps_den;
	int profile;
	int level_idc;
	int max_b_frame;
}h264_common_info;

int h264_parse_sps(h264_common_info* info, unsigned char* buff, int length);

END_C_DECLARE

#endif /* H264PARSER_H_ */
