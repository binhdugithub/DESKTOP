################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/libswscale/x86/rgb2rgb.c \
../include/ffmpeg/libswscale/x86/rgb2rgb_template.c \
../include/ffmpeg/libswscale/x86/swscale.c \
../include/ffmpeg/libswscale/x86/swscale_template.c \
../include/ffmpeg/libswscale/x86/w64xmmtest.c \
../include/ffmpeg/libswscale/x86/yuv2rgb.c \
../include/ffmpeg/libswscale/x86/yuv2rgb_template.c 

ASM_SRCS += \
../include/ffmpeg/libswscale/x86/input.asm \
../include/ffmpeg/libswscale/x86/output.asm \
../include/ffmpeg/libswscale/x86/scale.asm 

OBJS += \
./include/ffmpeg/libswscale/x86/input.o \
./include/ffmpeg/libswscale/x86/output.o \
./include/ffmpeg/libswscale/x86/rgb2rgb.o \
./include/ffmpeg/libswscale/x86/rgb2rgb_template.o \
./include/ffmpeg/libswscale/x86/scale.o \
./include/ffmpeg/libswscale/x86/swscale.o \
./include/ffmpeg/libswscale/x86/swscale_template.o \
./include/ffmpeg/libswscale/x86/w64xmmtest.o \
./include/ffmpeg/libswscale/x86/yuv2rgb.o \
./include/ffmpeg/libswscale/x86/yuv2rgb_template.o 

C_DEPS += \
./include/ffmpeg/libswscale/x86/rgb2rgb.d \
./include/ffmpeg/libswscale/x86/rgb2rgb_template.d \
./include/ffmpeg/libswscale/x86/swscale.d \
./include/ffmpeg/libswscale/x86/swscale_template.d \
./include/ffmpeg/libswscale/x86/w64xmmtest.d \
./include/ffmpeg/libswscale/x86/yuv2rgb.d \
./include/ffmpeg/libswscale/x86/yuv2rgb_template.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/libswscale/x86/%.o: ../include/ffmpeg/libswscale/x86/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/ffmpeg/libswscale/x86/%.o: ../include/ffmpeg/libswscale/x86/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


