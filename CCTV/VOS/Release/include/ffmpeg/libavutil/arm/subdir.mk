################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/libavutil/arm/cpu.c \
../include/ffmpeg/libavutil/arm/float_dsp_init_arm.c \
../include/ffmpeg/libavutil/arm/float_dsp_init_neon.c \
../include/ffmpeg/libavutil/arm/float_dsp_init_vfp.c 

S_UPPER_SRCS += \
../include/ffmpeg/libavutil/arm/asm.S \
../include/ffmpeg/libavutil/arm/float_dsp_neon.S \
../include/ffmpeg/libavutil/arm/float_dsp_vfp.S 

OBJS += \
./include/ffmpeg/libavutil/arm/asm.o \
./include/ffmpeg/libavutil/arm/cpu.o \
./include/ffmpeg/libavutil/arm/float_dsp_init_arm.o \
./include/ffmpeg/libavutil/arm/float_dsp_init_neon.o \
./include/ffmpeg/libavutil/arm/float_dsp_init_vfp.o \
./include/ffmpeg/libavutil/arm/float_dsp_neon.o \
./include/ffmpeg/libavutil/arm/float_dsp_vfp.o 

C_DEPS += \
./include/ffmpeg/libavutil/arm/cpu.d \
./include/ffmpeg/libavutil/arm/float_dsp_init_arm.d \
./include/ffmpeg/libavutil/arm/float_dsp_init_neon.d \
./include/ffmpeg/libavutil/arm/float_dsp_init_vfp.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/libavutil/arm/%.o: ../include/ffmpeg/libavutil/arm/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/ffmpeg/libavutil/arm/%.o: ../include/ffmpeg/libavutil/arm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


