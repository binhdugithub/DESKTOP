################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg-2.7.2/libavresample/audio_convert.c \
../include/ffmpeg-2.7.2/libavresample/audio_data.c \
../include/ffmpeg-2.7.2/libavresample/audio_mix.c \
../include/ffmpeg-2.7.2/libavresample/audio_mix_matrix.c \
../include/ffmpeg-2.7.2/libavresample/avresample-test.c \
../include/ffmpeg-2.7.2/libavresample/dither.c \
../include/ffmpeg-2.7.2/libavresample/options.c \
../include/ffmpeg-2.7.2/libavresample/resample.c \
../include/ffmpeg-2.7.2/libavresample/resample_template.c \
../include/ffmpeg-2.7.2/libavresample/utils.c 

OBJS += \
./include/ffmpeg-2.7.2/libavresample/audio_convert.o \
./include/ffmpeg-2.7.2/libavresample/audio_data.o \
./include/ffmpeg-2.7.2/libavresample/audio_mix.o \
./include/ffmpeg-2.7.2/libavresample/audio_mix_matrix.o \
./include/ffmpeg-2.7.2/libavresample/avresample-test.o \
./include/ffmpeg-2.7.2/libavresample/dither.o \
./include/ffmpeg-2.7.2/libavresample/options.o \
./include/ffmpeg-2.7.2/libavresample/resample.o \
./include/ffmpeg-2.7.2/libavresample/resample_template.o \
./include/ffmpeg-2.7.2/libavresample/utils.o 

C_DEPS += \
./include/ffmpeg-2.7.2/libavresample/audio_convert.d \
./include/ffmpeg-2.7.2/libavresample/audio_data.d \
./include/ffmpeg-2.7.2/libavresample/audio_mix.d \
./include/ffmpeg-2.7.2/libavresample/audio_mix_matrix.d \
./include/ffmpeg-2.7.2/libavresample/avresample-test.d \
./include/ffmpeg-2.7.2/libavresample/dither.d \
./include/ffmpeg-2.7.2/libavresample/options.d \
./include/ffmpeg-2.7.2/libavresample/resample.d \
./include/ffmpeg-2.7.2/libavresample/resample_template.d \
./include/ffmpeg-2.7.2/libavresample/utils.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg-2.7.2/libavresample/%.o: ../include/ffmpeg-2.7.2/libavresample/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


