################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg-2.7.2/libswscale/ppc/swscale_altivec.c \
../include/ffmpeg-2.7.2/libswscale/ppc/yuv2rgb_altivec.c \
../include/ffmpeg-2.7.2/libswscale/ppc/yuv2yuv_altivec.c 

OBJS += \
./include/ffmpeg-2.7.2/libswscale/ppc/swscale_altivec.o \
./include/ffmpeg-2.7.2/libswscale/ppc/yuv2rgb_altivec.o \
./include/ffmpeg-2.7.2/libswscale/ppc/yuv2yuv_altivec.o 

C_DEPS += \
./include/ffmpeg-2.7.2/libswscale/ppc/swscale_altivec.d \
./include/ffmpeg-2.7.2/libswscale/ppc/yuv2rgb_altivec.d \
./include/ffmpeg-2.7.2/libswscale/ppc/yuv2yuv_altivec.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg-2.7.2/libswscale/ppc/%.o: ../include/ffmpeg-2.7.2/libswscale/ppc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


