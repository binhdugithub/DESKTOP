################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg-2.7.2/doc/examples/avio_list_dir.c \
../include/ffmpeg-2.7.2/doc/examples/avio_reading.c \
../include/ffmpeg-2.7.2/doc/examples/decoding_encoding.c \
../include/ffmpeg-2.7.2/doc/examples/demuxing_decoding.c \
../include/ffmpeg-2.7.2/doc/examples/extract_mvs.c \
../include/ffmpeg-2.7.2/doc/examples/filter_audio.c \
../include/ffmpeg-2.7.2/doc/examples/filtering_audio.c \
../include/ffmpeg-2.7.2/doc/examples/filtering_video.c \
../include/ffmpeg-2.7.2/doc/examples/metadata.c \
../include/ffmpeg-2.7.2/doc/examples/muxing.c \
../include/ffmpeg-2.7.2/doc/examples/qsvdec.c \
../include/ffmpeg-2.7.2/doc/examples/remuxing.c \
../include/ffmpeg-2.7.2/doc/examples/resampling_audio.c \
../include/ffmpeg-2.7.2/doc/examples/scaling_video.c \
../include/ffmpeg-2.7.2/doc/examples/transcode_aac.c \
../include/ffmpeg-2.7.2/doc/examples/transcoding.c 

OBJS += \
./include/ffmpeg-2.7.2/doc/examples/avio_list_dir.o \
./include/ffmpeg-2.7.2/doc/examples/avio_reading.o \
./include/ffmpeg-2.7.2/doc/examples/decoding_encoding.o \
./include/ffmpeg-2.7.2/doc/examples/demuxing_decoding.o \
./include/ffmpeg-2.7.2/doc/examples/extract_mvs.o \
./include/ffmpeg-2.7.2/doc/examples/filter_audio.o \
./include/ffmpeg-2.7.2/doc/examples/filtering_audio.o \
./include/ffmpeg-2.7.2/doc/examples/filtering_video.o \
./include/ffmpeg-2.7.2/doc/examples/metadata.o \
./include/ffmpeg-2.7.2/doc/examples/muxing.o \
./include/ffmpeg-2.7.2/doc/examples/qsvdec.o \
./include/ffmpeg-2.7.2/doc/examples/remuxing.o \
./include/ffmpeg-2.7.2/doc/examples/resampling_audio.o \
./include/ffmpeg-2.7.2/doc/examples/scaling_video.o \
./include/ffmpeg-2.7.2/doc/examples/transcode_aac.o \
./include/ffmpeg-2.7.2/doc/examples/transcoding.o 

C_DEPS += \
./include/ffmpeg-2.7.2/doc/examples/avio_list_dir.d \
./include/ffmpeg-2.7.2/doc/examples/avio_reading.d \
./include/ffmpeg-2.7.2/doc/examples/decoding_encoding.d \
./include/ffmpeg-2.7.2/doc/examples/demuxing_decoding.d \
./include/ffmpeg-2.7.2/doc/examples/extract_mvs.d \
./include/ffmpeg-2.7.2/doc/examples/filter_audio.d \
./include/ffmpeg-2.7.2/doc/examples/filtering_audio.d \
./include/ffmpeg-2.7.2/doc/examples/filtering_video.d \
./include/ffmpeg-2.7.2/doc/examples/metadata.d \
./include/ffmpeg-2.7.2/doc/examples/muxing.d \
./include/ffmpeg-2.7.2/doc/examples/qsvdec.d \
./include/ffmpeg-2.7.2/doc/examples/remuxing.d \
./include/ffmpeg-2.7.2/doc/examples/resampling_audio.d \
./include/ffmpeg-2.7.2/doc/examples/scaling_video.d \
./include/ffmpeg-2.7.2/doc/examples/transcode_aac.d \
./include/ffmpeg-2.7.2/doc/examples/transcoding.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg-2.7.2/doc/examples/%.o: ../include/ffmpeg-2.7.2/doc/examples/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


