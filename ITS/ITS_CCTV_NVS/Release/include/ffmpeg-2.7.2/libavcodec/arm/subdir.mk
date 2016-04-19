################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg-2.7.2/libavcodec/arm/aacpsdsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/ac3dsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/audiodsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/audiodsp_init_neon.c \
../include/ffmpeg-2.7.2/libavcodec/arm/blockdsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/blockdsp_init_neon.c \
../include/ffmpeg-2.7.2/libavcodec/arm/dcadsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/dct-test.c \
../include/ffmpeg-2.7.2/libavcodec/arm/fft_fixed_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/fft_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/flacdsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/fmtconvert_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/g722dsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/h264chroma_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/h264dsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/h264pred_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/h264qpel_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/hevcdsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/hevcdsp_init_neon.c \
../include/ffmpeg-2.7.2/libavcodec/arm/hpeldsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/hpeldsp_init_armv6.c \
../include/ffmpeg-2.7.2/libavcodec/arm/hpeldsp_init_neon.c \
../include/ffmpeg-2.7.2/libavcodec/arm/idctdsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/idctdsp_init_armv5te.c \
../include/ffmpeg-2.7.2/libavcodec/arm/idctdsp_init_armv6.c \
../include/ffmpeg-2.7.2/libavcodec/arm/idctdsp_init_neon.c \
../include/ffmpeg-2.7.2/libavcodec/arm/lossless_audiodsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/me_cmp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/mlpdsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/mpegaudiodsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/mpegvideo_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/mpegvideo_armv5te.c \
../include/ffmpeg-2.7.2/libavcodec/arm/mpegvideoencdsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/neontest.c \
../include/ffmpeg-2.7.2/libavcodec/arm/pixblockdsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/rv34dsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/rv40dsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/sbrdsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/vc1dsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/vc1dsp_init_neon.c \
../include/ffmpeg-2.7.2/libavcodec/arm/videodsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/videodsp_init_armv5te.c \
../include/ffmpeg-2.7.2/libavcodec/arm/vorbisdsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/vp3dsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/vp6dsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/vp8dsp_init_arm.c \
../include/ffmpeg-2.7.2/libavcodec/arm/vp8dsp_init_armv6.c \
../include/ffmpeg-2.7.2/libavcodec/arm/vp8dsp_init_neon.c 

S_UPPER_SRCS += \
../include/ffmpeg-2.7.2/libavcodec/arm/aacpsdsp_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/ac3dsp_arm.S \
../include/ffmpeg-2.7.2/libavcodec/arm/ac3dsp_armv6.S \
../include/ffmpeg-2.7.2/libavcodec/arm/ac3dsp_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/audiodsp_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/blockdsp_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/dcadsp_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/dcadsp_vfp.S \
../include/ffmpeg-2.7.2/libavcodec/arm/fft_fixed_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/fft_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/fft_vfp.S \
../include/ffmpeg-2.7.2/libavcodec/arm/flacdsp_arm.S \
../include/ffmpeg-2.7.2/libavcodec/arm/fmtconvert_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/fmtconvert_vfp.S \
../include/ffmpeg-2.7.2/libavcodec/arm/g722dsp_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/h264cmc_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/h264dsp_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/h264idct_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/h264pred_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/h264qpel_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/hevcdsp_deblock_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/hevcdsp_idct_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/hevcdsp_qpel_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/hpeldsp_arm.S \
../include/ffmpeg-2.7.2/libavcodec/arm/hpeldsp_armv6.S \
../include/ffmpeg-2.7.2/libavcodec/arm/hpeldsp_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/idctdsp_arm.S \
../include/ffmpeg-2.7.2/libavcodec/arm/idctdsp_armv6.S \
../include/ffmpeg-2.7.2/libavcodec/arm/idctdsp_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/int_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/jrevdct_arm.S \
../include/ffmpeg-2.7.2/libavcodec/arm/lossless_audiodsp_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/mdct_fixed_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/mdct_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/mdct_vfp.S \
../include/ffmpeg-2.7.2/libavcodec/arm/me_cmp_armv6.S \
../include/ffmpeg-2.7.2/libavcodec/arm/mlpdsp_armv5te.S \
../include/ffmpeg-2.7.2/libavcodec/arm/mlpdsp_armv6.S \
../include/ffmpeg-2.7.2/libavcodec/arm/mpegaudiodsp_fixed_armv6.S \
../include/ffmpeg-2.7.2/libavcodec/arm/mpegvideo_armv5te_s.S \
../include/ffmpeg-2.7.2/libavcodec/arm/mpegvideo_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/mpegvideoencdsp_armv6.S \
../include/ffmpeg-2.7.2/libavcodec/arm/neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/pixblockdsp_armv6.S \
../include/ffmpeg-2.7.2/libavcodec/arm/rdft_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/rv34dsp_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/rv40dsp_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/sbrdsp_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/simple_idct_arm.S \
../include/ffmpeg-2.7.2/libavcodec/arm/simple_idct_armv5te.S \
../include/ffmpeg-2.7.2/libavcodec/arm/simple_idct_armv6.S \
../include/ffmpeg-2.7.2/libavcodec/arm/simple_idct_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/startcode_armv6.S \
../include/ffmpeg-2.7.2/libavcodec/arm/synth_filter_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/synth_filter_vfp.S \
../include/ffmpeg-2.7.2/libavcodec/arm/vc1dsp_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/videodsp_armv5te.S \
../include/ffmpeg-2.7.2/libavcodec/arm/vorbisdsp_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/vp3dsp_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/vp6dsp_neon.S \
../include/ffmpeg-2.7.2/libavcodec/arm/vp8_armv6.S \
../include/ffmpeg-2.7.2/libavcodec/arm/vp8dsp_armv6.S \
../include/ffmpeg-2.7.2/libavcodec/arm/vp8dsp_neon.S 

OBJS += \
./include/ffmpeg-2.7.2/libavcodec/arm/aacpsdsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/aacpsdsp_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/ac3dsp_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/ac3dsp_armv6.o \
./include/ffmpeg-2.7.2/libavcodec/arm/ac3dsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/ac3dsp_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/audiodsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/audiodsp_init_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/audiodsp_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/blockdsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/blockdsp_init_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/blockdsp_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/dcadsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/dcadsp_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/dcadsp_vfp.o \
./include/ffmpeg-2.7.2/libavcodec/arm/dct-test.o \
./include/ffmpeg-2.7.2/libavcodec/arm/fft_fixed_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/fft_fixed_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/fft_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/fft_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/fft_vfp.o \
./include/ffmpeg-2.7.2/libavcodec/arm/flacdsp_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/flacdsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/fmtconvert_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/fmtconvert_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/fmtconvert_vfp.o \
./include/ffmpeg-2.7.2/libavcodec/arm/g722dsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/g722dsp_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/h264chroma_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/h264cmc_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/h264dsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/h264dsp_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/h264idct_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/h264pred_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/h264pred_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/h264qpel_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/h264qpel_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/hevcdsp_deblock_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/hevcdsp_idct_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/hevcdsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/hevcdsp_init_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/hevcdsp_qpel_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/hpeldsp_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/hpeldsp_armv6.o \
./include/ffmpeg-2.7.2/libavcodec/arm/hpeldsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/hpeldsp_init_armv6.o \
./include/ffmpeg-2.7.2/libavcodec/arm/hpeldsp_init_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/hpeldsp_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/idctdsp_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/idctdsp_armv6.o \
./include/ffmpeg-2.7.2/libavcodec/arm/idctdsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/idctdsp_init_armv5te.o \
./include/ffmpeg-2.7.2/libavcodec/arm/idctdsp_init_armv6.o \
./include/ffmpeg-2.7.2/libavcodec/arm/idctdsp_init_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/idctdsp_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/int_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/jrevdct_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/lossless_audiodsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/lossless_audiodsp_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/mdct_fixed_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/mdct_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/mdct_vfp.o \
./include/ffmpeg-2.7.2/libavcodec/arm/me_cmp_armv6.o \
./include/ffmpeg-2.7.2/libavcodec/arm/me_cmp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/mlpdsp_armv5te.o \
./include/ffmpeg-2.7.2/libavcodec/arm/mlpdsp_armv6.o \
./include/ffmpeg-2.7.2/libavcodec/arm/mlpdsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/mpegaudiodsp_fixed_armv6.o \
./include/ffmpeg-2.7.2/libavcodec/arm/mpegaudiodsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/mpegvideo_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/mpegvideo_armv5te.o \
./include/ffmpeg-2.7.2/libavcodec/arm/mpegvideo_armv5te_s.o \
./include/ffmpeg-2.7.2/libavcodec/arm/mpegvideo_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/mpegvideoencdsp_armv6.o \
./include/ffmpeg-2.7.2/libavcodec/arm/mpegvideoencdsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/neontest.o \
./include/ffmpeg-2.7.2/libavcodec/arm/pixblockdsp_armv6.o \
./include/ffmpeg-2.7.2/libavcodec/arm/pixblockdsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/rdft_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/rv34dsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/rv34dsp_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/rv40dsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/rv40dsp_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/sbrdsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/sbrdsp_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/simple_idct_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/simple_idct_armv5te.o \
./include/ffmpeg-2.7.2/libavcodec/arm/simple_idct_armv6.o \
./include/ffmpeg-2.7.2/libavcodec/arm/simple_idct_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/startcode_armv6.o \
./include/ffmpeg-2.7.2/libavcodec/arm/synth_filter_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/synth_filter_vfp.o \
./include/ffmpeg-2.7.2/libavcodec/arm/vc1dsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/vc1dsp_init_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/vc1dsp_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/videodsp_armv5te.o \
./include/ffmpeg-2.7.2/libavcodec/arm/videodsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/videodsp_init_armv5te.o \
./include/ffmpeg-2.7.2/libavcodec/arm/vorbisdsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/vorbisdsp_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/vp3dsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/vp3dsp_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/vp6dsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/vp6dsp_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/vp8_armv6.o \
./include/ffmpeg-2.7.2/libavcodec/arm/vp8dsp_armv6.o \
./include/ffmpeg-2.7.2/libavcodec/arm/vp8dsp_init_arm.o \
./include/ffmpeg-2.7.2/libavcodec/arm/vp8dsp_init_armv6.o \
./include/ffmpeg-2.7.2/libavcodec/arm/vp8dsp_init_neon.o \
./include/ffmpeg-2.7.2/libavcodec/arm/vp8dsp_neon.o 

C_DEPS += \
./include/ffmpeg-2.7.2/libavcodec/arm/aacpsdsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/ac3dsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/audiodsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/audiodsp_init_neon.d \
./include/ffmpeg-2.7.2/libavcodec/arm/blockdsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/blockdsp_init_neon.d \
./include/ffmpeg-2.7.2/libavcodec/arm/dcadsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/dct-test.d \
./include/ffmpeg-2.7.2/libavcodec/arm/fft_fixed_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/fft_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/flacdsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/fmtconvert_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/g722dsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/h264chroma_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/h264dsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/h264pred_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/h264qpel_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/hevcdsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/hevcdsp_init_neon.d \
./include/ffmpeg-2.7.2/libavcodec/arm/hpeldsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/hpeldsp_init_armv6.d \
./include/ffmpeg-2.7.2/libavcodec/arm/hpeldsp_init_neon.d \
./include/ffmpeg-2.7.2/libavcodec/arm/idctdsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/idctdsp_init_armv5te.d \
./include/ffmpeg-2.7.2/libavcodec/arm/idctdsp_init_armv6.d \
./include/ffmpeg-2.7.2/libavcodec/arm/idctdsp_init_neon.d \
./include/ffmpeg-2.7.2/libavcodec/arm/lossless_audiodsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/me_cmp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/mlpdsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/mpegaudiodsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/mpegvideo_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/mpegvideo_armv5te.d \
./include/ffmpeg-2.7.2/libavcodec/arm/mpegvideoencdsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/neontest.d \
./include/ffmpeg-2.7.2/libavcodec/arm/pixblockdsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/rv34dsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/rv40dsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/sbrdsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/vc1dsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/vc1dsp_init_neon.d \
./include/ffmpeg-2.7.2/libavcodec/arm/videodsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/videodsp_init_armv5te.d \
./include/ffmpeg-2.7.2/libavcodec/arm/vorbisdsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/vp3dsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/vp6dsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/vp8dsp_init_arm.d \
./include/ffmpeg-2.7.2/libavcodec/arm/vp8dsp_init_armv6.d \
./include/ffmpeg-2.7.2/libavcodec/arm/vp8dsp_init_neon.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg-2.7.2/libavcodec/arm/%.o: ../include/ffmpeg-2.7.2/libavcodec/arm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/ffmpeg-2.7.2/libavcodec/arm/%.o: ../include/ffmpeg-2.7.2/libavcodec/arm/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


