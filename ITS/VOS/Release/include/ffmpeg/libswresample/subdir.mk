################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/libswresample/audioconvert.c \
../include/ffmpeg/libswresample/dither.c \
../include/ffmpeg/libswresample/dither_template.c \
../include/ffmpeg/libswresample/log2_tab.c \
../include/ffmpeg/libswresample/noise_shaping_data.c \
../include/ffmpeg/libswresample/options.c \
../include/ffmpeg/libswresample/rematrix.c \
../include/ffmpeg/libswresample/rematrix_template.c \
../include/ffmpeg/libswresample/resample.c \
../include/ffmpeg/libswresample/resample_dsp.c \
../include/ffmpeg/libswresample/resample_template.c \
../include/ffmpeg/libswresample/soxr_resample.c \
../include/ffmpeg/libswresample/swresample-test.c \
../include/ffmpeg/libswresample/swresample.c 

OBJS += \
./include/ffmpeg/libswresample/audioconvert.o \
./include/ffmpeg/libswresample/dither.o \
./include/ffmpeg/libswresample/dither_template.o \
./include/ffmpeg/libswresample/log2_tab.o \
./include/ffmpeg/libswresample/noise_shaping_data.o \
./include/ffmpeg/libswresample/options.o \
./include/ffmpeg/libswresample/rematrix.o \
./include/ffmpeg/libswresample/rematrix_template.o \
./include/ffmpeg/libswresample/resample.o \
./include/ffmpeg/libswresample/resample_dsp.o \
./include/ffmpeg/libswresample/resample_template.o \
./include/ffmpeg/libswresample/soxr_resample.o \
./include/ffmpeg/libswresample/swresample-test.o \
./include/ffmpeg/libswresample/swresample.o 

C_DEPS += \
./include/ffmpeg/libswresample/audioconvert.d \
./include/ffmpeg/libswresample/dither.d \
./include/ffmpeg/libswresample/dither_template.d \
./include/ffmpeg/libswresample/log2_tab.d \
./include/ffmpeg/libswresample/noise_shaping_data.d \
./include/ffmpeg/libswresample/options.d \
./include/ffmpeg/libswresample/rematrix.d \
./include/ffmpeg/libswresample/rematrix_template.d \
./include/ffmpeg/libswresample/resample.d \
./include/ffmpeg/libswresample/resample_dsp.d \
./include/ffmpeg/libswresample/resample_template.d \
./include/ffmpeg/libswresample/soxr_resample.d \
./include/ffmpeg/libswresample/swresample-test.d \
./include/ffmpeg/libswresample/swresample.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/libswresample/%.o: ../include/ffmpeg/libswresample/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


