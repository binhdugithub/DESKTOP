################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/libswscale/bayer_template.c \
../include/ffmpeg/libswscale/colorspace-test.c \
../include/ffmpeg/libswscale/input.c \
../include/ffmpeg/libswscale/options.c \
../include/ffmpeg/libswscale/output.c \
../include/ffmpeg/libswscale/rgb2rgb.c \
../include/ffmpeg/libswscale/rgb2rgb_template.c \
../include/ffmpeg/libswscale/swscale-test.c \
../include/ffmpeg/libswscale/swscale.c \
../include/ffmpeg/libswscale/swscale_unscaled.c \
../include/ffmpeg/libswscale/utils.c \
../include/ffmpeg/libswscale/yuv2rgb.c 

OBJS += \
./include/ffmpeg/libswscale/bayer_template.o \
./include/ffmpeg/libswscale/colorspace-test.o \
./include/ffmpeg/libswscale/input.o \
./include/ffmpeg/libswscale/options.o \
./include/ffmpeg/libswscale/output.o \
./include/ffmpeg/libswscale/rgb2rgb.o \
./include/ffmpeg/libswscale/rgb2rgb_template.o \
./include/ffmpeg/libswscale/swscale-test.o \
./include/ffmpeg/libswscale/swscale.o \
./include/ffmpeg/libswscale/swscale_unscaled.o \
./include/ffmpeg/libswscale/utils.o \
./include/ffmpeg/libswscale/yuv2rgb.o 

C_DEPS += \
./include/ffmpeg/libswscale/bayer_template.d \
./include/ffmpeg/libswscale/colorspace-test.d \
./include/ffmpeg/libswscale/input.d \
./include/ffmpeg/libswscale/options.d \
./include/ffmpeg/libswscale/output.d \
./include/ffmpeg/libswscale/rgb2rgb.d \
./include/ffmpeg/libswscale/rgb2rgb_template.d \
./include/ffmpeg/libswscale/swscale-test.d \
./include/ffmpeg/libswscale/swscale.d \
./include/ffmpeg/libswscale/swscale_unscaled.d \
./include/ffmpeg/libswscale/utils.d \
./include/ffmpeg/libswscale/yuv2rgb.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/libswscale/%.o: ../include/ffmpeg/libswscale/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


