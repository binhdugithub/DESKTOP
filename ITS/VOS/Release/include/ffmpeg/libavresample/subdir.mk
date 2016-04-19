################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/libavresample/audio_convert.c \
../include/ffmpeg/libavresample/audio_data.c \
../include/ffmpeg/libavresample/audio_mix.c \
../include/ffmpeg/libavresample/audio_mix_matrix.c \
../include/ffmpeg/libavresample/avresample-test.c \
../include/ffmpeg/libavresample/dither.c \
../include/ffmpeg/libavresample/options.c \
../include/ffmpeg/libavresample/resample.c \
../include/ffmpeg/libavresample/resample_template.c \
../include/ffmpeg/libavresample/utils.c 

OBJS += \
./include/ffmpeg/libavresample/audio_convert.o \
./include/ffmpeg/libavresample/audio_data.o \
./include/ffmpeg/libavresample/audio_mix.o \
./include/ffmpeg/libavresample/audio_mix_matrix.o \
./include/ffmpeg/libavresample/avresample-test.o \
./include/ffmpeg/libavresample/dither.o \
./include/ffmpeg/libavresample/options.o \
./include/ffmpeg/libavresample/resample.o \
./include/ffmpeg/libavresample/resample_template.o \
./include/ffmpeg/libavresample/utils.o 

C_DEPS += \
./include/ffmpeg/libavresample/audio_convert.d \
./include/ffmpeg/libavresample/audio_data.d \
./include/ffmpeg/libavresample/audio_mix.d \
./include/ffmpeg/libavresample/audio_mix_matrix.d \
./include/ffmpeg/libavresample/avresample-test.d \
./include/ffmpeg/libavresample/dither.d \
./include/ffmpeg/libavresample/options.d \
./include/ffmpeg/libavresample/resample.d \
./include/ffmpeg/libavresample/resample_template.d \
./include/ffmpeg/libavresample/utils.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/libavresample/%.o: ../include/ffmpeg/libavresample/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


