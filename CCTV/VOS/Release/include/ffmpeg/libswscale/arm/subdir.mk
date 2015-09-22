################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/libswscale/arm/swscale_unscaled.c 

S_UPPER_SRCS += \
../include/ffmpeg/libswscale/arm/rgb2yuv_neon_16.S \
../include/ffmpeg/libswscale/arm/rgb2yuv_neon_32.S \
../include/ffmpeg/libswscale/arm/rgb2yuv_neon_common.S 

OBJS += \
./include/ffmpeg/libswscale/arm/rgb2yuv_neon_16.o \
./include/ffmpeg/libswscale/arm/rgb2yuv_neon_32.o \
./include/ffmpeg/libswscale/arm/rgb2yuv_neon_common.o \
./include/ffmpeg/libswscale/arm/swscale_unscaled.o 

C_DEPS += \
./include/ffmpeg/libswscale/arm/swscale_unscaled.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/libswscale/arm/%.o: ../include/ffmpeg/libswscale/arm/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/ffmpeg/libswscale/arm/%.o: ../include/ffmpeg/libswscale/arm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


