################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/doc/examples/avio_reading.c \
../include/ffmpeg/doc/examples/decoding_encoding.c \
../include/ffmpeg/doc/examples/demuxing_decoding.c \
../include/ffmpeg/doc/examples/filter_audio.c \
../include/ffmpeg/doc/examples/filtering_audio.c \
../include/ffmpeg/doc/examples/filtering_video.c \
../include/ffmpeg/doc/examples/metadata.c \
../include/ffmpeg/doc/examples/muxing.c \
../include/ffmpeg/doc/examples/remuxing.c \
../include/ffmpeg/doc/examples/resampling_audio.c \
../include/ffmpeg/doc/examples/scaling_video.c \
../include/ffmpeg/doc/examples/transcode_aac.c \
../include/ffmpeg/doc/examples/transcoding.c 

OBJS += \
./include/ffmpeg/doc/examples/avio_reading.o \
./include/ffmpeg/doc/examples/decoding_encoding.o \
./include/ffmpeg/doc/examples/demuxing_decoding.o \
./include/ffmpeg/doc/examples/filter_audio.o \
./include/ffmpeg/doc/examples/filtering_audio.o \
./include/ffmpeg/doc/examples/filtering_video.o \
./include/ffmpeg/doc/examples/metadata.o \
./include/ffmpeg/doc/examples/muxing.o \
./include/ffmpeg/doc/examples/remuxing.o \
./include/ffmpeg/doc/examples/resampling_audio.o \
./include/ffmpeg/doc/examples/scaling_video.o \
./include/ffmpeg/doc/examples/transcode_aac.o \
./include/ffmpeg/doc/examples/transcoding.o 

C_DEPS += \
./include/ffmpeg/doc/examples/avio_reading.d \
./include/ffmpeg/doc/examples/decoding_encoding.d \
./include/ffmpeg/doc/examples/demuxing_decoding.d \
./include/ffmpeg/doc/examples/filter_audio.d \
./include/ffmpeg/doc/examples/filtering_audio.d \
./include/ffmpeg/doc/examples/filtering_video.d \
./include/ffmpeg/doc/examples/metadata.d \
./include/ffmpeg/doc/examples/muxing.d \
./include/ffmpeg/doc/examples/remuxing.d \
./include/ffmpeg/doc/examples/resampling_audio.d \
./include/ffmpeg/doc/examples/scaling_video.d \
./include/ffmpeg/doc/examples/transcode_aac.d \
./include/ffmpeg/doc/examples/transcoding.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/doc/examples/%.o: ../include/ffmpeg/doc/examples/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


