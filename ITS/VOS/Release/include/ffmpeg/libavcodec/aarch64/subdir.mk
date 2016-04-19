################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/libavcodec/aarch64/fft_init_aarch64.c \
../include/ffmpeg/libavcodec/aarch64/h264chroma_init_aarch64.c \
../include/ffmpeg/libavcodec/aarch64/h264dsp_init_aarch64.c \
../include/ffmpeg/libavcodec/aarch64/h264qpel_init_aarch64.c \
../include/ffmpeg/libavcodec/aarch64/hpeldsp_init_aarch64.c \
../include/ffmpeg/libavcodec/aarch64/mpegaudiodsp_init.c \
../include/ffmpeg/libavcodec/aarch64/neontest.c \
../include/ffmpeg/libavcodec/aarch64/opus_imdct_init.c \
../include/ffmpeg/libavcodec/aarch64/rv40dsp_init_aarch64.c \
../include/ffmpeg/libavcodec/aarch64/vc1dsp_init_aarch64.c \
../include/ffmpeg/libavcodec/aarch64/videodsp_init.c \
../include/ffmpeg/libavcodec/aarch64/vorbisdsp_init.c 

S_UPPER_SRCS += \
../include/ffmpeg/libavcodec/aarch64/fft_neon.S \
../include/ffmpeg/libavcodec/aarch64/h264cmc_neon.S \
../include/ffmpeg/libavcodec/aarch64/h264dsp_neon.S \
../include/ffmpeg/libavcodec/aarch64/h264idct_neon.S \
../include/ffmpeg/libavcodec/aarch64/h264qpel_neon.S \
../include/ffmpeg/libavcodec/aarch64/hpeldsp_neon.S \
../include/ffmpeg/libavcodec/aarch64/mdct_neon.S \
../include/ffmpeg/libavcodec/aarch64/mpegaudiodsp_neon.S \
../include/ffmpeg/libavcodec/aarch64/neon.S \
../include/ffmpeg/libavcodec/aarch64/opus_imdct_neon.S \
../include/ffmpeg/libavcodec/aarch64/videodsp.S \
../include/ffmpeg/libavcodec/aarch64/vorbisdsp_neon.S 

OBJS += \
./include/ffmpeg/libavcodec/aarch64/fft_init_aarch64.o \
./include/ffmpeg/libavcodec/aarch64/fft_neon.o \
./include/ffmpeg/libavcodec/aarch64/h264chroma_init_aarch64.o \
./include/ffmpeg/libavcodec/aarch64/h264cmc_neon.o \
./include/ffmpeg/libavcodec/aarch64/h264dsp_init_aarch64.o \
./include/ffmpeg/libavcodec/aarch64/h264dsp_neon.o \
./include/ffmpeg/libavcodec/aarch64/h264idct_neon.o \
./include/ffmpeg/libavcodec/aarch64/h264qpel_init_aarch64.o \
./include/ffmpeg/libavcodec/aarch64/h264qpel_neon.o \
./include/ffmpeg/libavcodec/aarch64/hpeldsp_init_aarch64.o \
./include/ffmpeg/libavcodec/aarch64/hpeldsp_neon.o \
./include/ffmpeg/libavcodec/aarch64/mdct_neon.o \
./include/ffmpeg/libavcodec/aarch64/mpegaudiodsp_init.o \
./include/ffmpeg/libavcodec/aarch64/mpegaudiodsp_neon.o \
./include/ffmpeg/libavcodec/aarch64/neon.o \
./include/ffmpeg/libavcodec/aarch64/neontest.o \
./include/ffmpeg/libavcodec/aarch64/opus_imdct_init.o \
./include/ffmpeg/libavcodec/aarch64/opus_imdct_neon.o \
./include/ffmpeg/libavcodec/aarch64/rv40dsp_init_aarch64.o \
./include/ffmpeg/libavcodec/aarch64/vc1dsp_init_aarch64.o \
./include/ffmpeg/libavcodec/aarch64/videodsp.o \
./include/ffmpeg/libavcodec/aarch64/videodsp_init.o \
./include/ffmpeg/libavcodec/aarch64/vorbisdsp_init.o \
./include/ffmpeg/libavcodec/aarch64/vorbisdsp_neon.o 

C_DEPS += \
./include/ffmpeg/libavcodec/aarch64/fft_init_aarch64.d \
./include/ffmpeg/libavcodec/aarch64/h264chroma_init_aarch64.d \
./include/ffmpeg/libavcodec/aarch64/h264dsp_init_aarch64.d \
./include/ffmpeg/libavcodec/aarch64/h264qpel_init_aarch64.d \
./include/ffmpeg/libavcodec/aarch64/hpeldsp_init_aarch64.d \
./include/ffmpeg/libavcodec/aarch64/mpegaudiodsp_init.d \
./include/ffmpeg/libavcodec/aarch64/neontest.d \
./include/ffmpeg/libavcodec/aarch64/opus_imdct_init.d \
./include/ffmpeg/libavcodec/aarch64/rv40dsp_init_aarch64.d \
./include/ffmpeg/libavcodec/aarch64/vc1dsp_init_aarch64.d \
./include/ffmpeg/libavcodec/aarch64/videodsp_init.d \
./include/ffmpeg/libavcodec/aarch64/vorbisdsp_init.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/libavcodec/aarch64/%.o: ../include/ffmpeg/libavcodec/aarch64/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/ffmpeg/libavcodec/aarch64/%.o: ../include/ffmpeg/libavcodec/aarch64/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


