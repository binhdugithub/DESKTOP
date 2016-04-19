################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../include/ffmpeg-2.7.2/libswscale/x86/hscale_fast_bilinear_simd.o \
../include/ffmpeg-2.7.2/libswscale/x86/rgb2rgb.o \
../include/ffmpeg-2.7.2/libswscale/x86/swscale.o \
../include/ffmpeg-2.7.2/libswscale/x86/yuv2rgb.o 

C_SRCS += \
../include/ffmpeg-2.7.2/libswscale/x86/hscale_fast_bilinear_simd.c \
../include/ffmpeg-2.7.2/libswscale/x86/rgb2rgb.c \
../include/ffmpeg-2.7.2/libswscale/x86/rgb2rgb_template.c \
../include/ffmpeg-2.7.2/libswscale/x86/swscale.c \
../include/ffmpeg-2.7.2/libswscale/x86/swscale_template.c \
../include/ffmpeg-2.7.2/libswscale/x86/w64xmmtest.c \
../include/ffmpeg-2.7.2/libswscale/x86/yuv2rgb.c \
../include/ffmpeg-2.7.2/libswscale/x86/yuv2rgb_template.c 

ASM_SRCS += \
../include/ffmpeg-2.7.2/libswscale/x86/input.asm \
../include/ffmpeg-2.7.2/libswscale/x86/output.asm \
../include/ffmpeg-2.7.2/libswscale/x86/scale.asm 

OBJS += \
./include/ffmpeg-2.7.2/libswscale/x86/hscale_fast_bilinear_simd.o \
./include/ffmpeg-2.7.2/libswscale/x86/input.o \
./include/ffmpeg-2.7.2/libswscale/x86/output.o \
./include/ffmpeg-2.7.2/libswscale/x86/rgb2rgb.o \
./include/ffmpeg-2.7.2/libswscale/x86/rgb2rgb_template.o \
./include/ffmpeg-2.7.2/libswscale/x86/scale.o \
./include/ffmpeg-2.7.2/libswscale/x86/swscale.o \
./include/ffmpeg-2.7.2/libswscale/x86/swscale_template.o \
./include/ffmpeg-2.7.2/libswscale/x86/w64xmmtest.o \
./include/ffmpeg-2.7.2/libswscale/x86/yuv2rgb.o \
./include/ffmpeg-2.7.2/libswscale/x86/yuv2rgb_template.o 

C_DEPS += \
./include/ffmpeg-2.7.2/libswscale/x86/hscale_fast_bilinear_simd.d \
./include/ffmpeg-2.7.2/libswscale/x86/rgb2rgb.d \
./include/ffmpeg-2.7.2/libswscale/x86/rgb2rgb_template.d \
./include/ffmpeg-2.7.2/libswscale/x86/swscale.d \
./include/ffmpeg-2.7.2/libswscale/x86/swscale_template.d \
./include/ffmpeg-2.7.2/libswscale/x86/w64xmmtest.d \
./include/ffmpeg-2.7.2/libswscale/x86/yuv2rgb.d \
./include/ffmpeg-2.7.2/libswscale/x86/yuv2rgb_template.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg-2.7.2/libswscale/x86/%.o: ../include/ffmpeg-2.7.2/libswscale/x86/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/ffmpeg-2.7.2/libswscale/x86/%.o: ../include/ffmpeg-2.7.2/libswscale/x86/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


