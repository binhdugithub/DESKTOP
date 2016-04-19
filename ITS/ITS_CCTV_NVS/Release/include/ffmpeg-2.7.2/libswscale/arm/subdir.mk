################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg-2.7.2/libswscale/arm/swscale_unscaled.c 

S_UPPER_SRCS += \
../include/ffmpeg-2.7.2/libswscale/arm/rgb2yuv_neon_16.S \
../include/ffmpeg-2.7.2/libswscale/arm/rgb2yuv_neon_32.S \
../include/ffmpeg-2.7.2/libswscale/arm/rgb2yuv_neon_common.S 

OBJS += \
./include/ffmpeg-2.7.2/libswscale/arm/rgb2yuv_neon_16.o \
./include/ffmpeg-2.7.2/libswscale/arm/rgb2yuv_neon_32.o \
./include/ffmpeg-2.7.2/libswscale/arm/rgb2yuv_neon_common.o \
./include/ffmpeg-2.7.2/libswscale/arm/swscale_unscaled.o 

C_DEPS += \
./include/ffmpeg-2.7.2/libswscale/arm/swscale_unscaled.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg-2.7.2/libswscale/arm/%.o: ../include/ffmpeg-2.7.2/libswscale/arm/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/ffmpeg-2.7.2/libswscale/arm/%.o: ../include/ffmpeg-2.7.2/libswscale/arm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


