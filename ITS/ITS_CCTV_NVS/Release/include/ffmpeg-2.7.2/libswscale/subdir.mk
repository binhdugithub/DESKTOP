################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../include/ffmpeg-2.7.2/libswscale/hscale_fast_bilinear.o \
../include/ffmpeg-2.7.2/libswscale/input.o \
../include/ffmpeg-2.7.2/libswscale/options.o \
../include/ffmpeg-2.7.2/libswscale/output.o \
../include/ffmpeg-2.7.2/libswscale/rgb2rgb.o \
../include/ffmpeg-2.7.2/libswscale/swscale.o \
../include/ffmpeg-2.7.2/libswscale/swscale_unscaled.o \
../include/ffmpeg-2.7.2/libswscale/utils.o \
../include/ffmpeg-2.7.2/libswscale/yuv2rgb.o 

C_SRCS += \
../include/ffmpeg-2.7.2/libswscale/bayer_template.c \
../include/ffmpeg-2.7.2/libswscale/colorspace-test.c \
../include/ffmpeg-2.7.2/libswscale/hscale_fast_bilinear.c \
../include/ffmpeg-2.7.2/libswscale/input.c \
../include/ffmpeg-2.7.2/libswscale/log2_tab.c \
../include/ffmpeg-2.7.2/libswscale/options.c \
../include/ffmpeg-2.7.2/libswscale/output.c \
../include/ffmpeg-2.7.2/libswscale/rgb2rgb.c \
../include/ffmpeg-2.7.2/libswscale/rgb2rgb_template.c \
../include/ffmpeg-2.7.2/libswscale/swscale-test.c \
../include/ffmpeg-2.7.2/libswscale/swscale.c \
../include/ffmpeg-2.7.2/libswscale/swscale_unscaled.c \
../include/ffmpeg-2.7.2/libswscale/utils.c \
../include/ffmpeg-2.7.2/libswscale/yuv2rgb.c 

OBJS += \
./include/ffmpeg-2.7.2/libswscale/bayer_template.o \
./include/ffmpeg-2.7.2/libswscale/colorspace-test.o \
./include/ffmpeg-2.7.2/libswscale/hscale_fast_bilinear.o \
./include/ffmpeg-2.7.2/libswscale/input.o \
./include/ffmpeg-2.7.2/libswscale/log2_tab.o \
./include/ffmpeg-2.7.2/libswscale/options.o \
./include/ffmpeg-2.7.2/libswscale/output.o \
./include/ffmpeg-2.7.2/libswscale/rgb2rgb.o \
./include/ffmpeg-2.7.2/libswscale/rgb2rgb_template.o \
./include/ffmpeg-2.7.2/libswscale/swscale-test.o \
./include/ffmpeg-2.7.2/libswscale/swscale.o \
./include/ffmpeg-2.7.2/libswscale/swscale_unscaled.o \
./include/ffmpeg-2.7.2/libswscale/utils.o \
./include/ffmpeg-2.7.2/libswscale/yuv2rgb.o 

C_DEPS += \
./include/ffmpeg-2.7.2/libswscale/bayer_template.d \
./include/ffmpeg-2.7.2/libswscale/colorspace-test.d \
./include/ffmpeg-2.7.2/libswscale/hscale_fast_bilinear.d \
./include/ffmpeg-2.7.2/libswscale/input.d \
./include/ffmpeg-2.7.2/libswscale/log2_tab.d \
./include/ffmpeg-2.7.2/libswscale/options.d \
./include/ffmpeg-2.7.2/libswscale/output.d \
./include/ffmpeg-2.7.2/libswscale/rgb2rgb.d \
./include/ffmpeg-2.7.2/libswscale/rgb2rgb_template.d \
./include/ffmpeg-2.7.2/libswscale/swscale-test.d \
./include/ffmpeg-2.7.2/libswscale/swscale.d \
./include/ffmpeg-2.7.2/libswscale/swscale_unscaled.d \
./include/ffmpeg-2.7.2/libswscale/utils.d \
./include/ffmpeg-2.7.2/libswscale/yuv2rgb.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg-2.7.2/libswscale/%.o: ../include/ffmpeg-2.7.2/libswscale/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


