################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/libswscale/ppc/swscale_altivec.c \
../include/ffmpeg/libswscale/ppc/yuv2rgb_altivec.c \
../include/ffmpeg/libswscale/ppc/yuv2yuv_altivec.c 

OBJS += \
./include/ffmpeg/libswscale/ppc/swscale_altivec.o \
./include/ffmpeg/libswscale/ppc/yuv2rgb_altivec.o \
./include/ffmpeg/libswscale/ppc/yuv2yuv_altivec.o 

C_DEPS += \
./include/ffmpeg/libswscale/ppc/swscale_altivec.d \
./include/ffmpeg/libswscale/ppc/yuv2rgb_altivec.d \
./include/ffmpeg/libswscale/ppc/yuv2yuv_altivec.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/libswscale/ppc/%.o: ../include/ffmpeg/libswscale/ppc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


