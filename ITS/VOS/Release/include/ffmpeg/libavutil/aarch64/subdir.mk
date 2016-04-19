################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/libavutil/aarch64/cpu.c \
../include/ffmpeg/libavutil/aarch64/float_dsp_init.c 

S_UPPER_SRCS += \
../include/ffmpeg/libavutil/aarch64/asm.S \
../include/ffmpeg/libavutil/aarch64/float_dsp_neon.S 

OBJS += \
./include/ffmpeg/libavutil/aarch64/asm.o \
./include/ffmpeg/libavutil/aarch64/cpu.o \
./include/ffmpeg/libavutil/aarch64/float_dsp_init.o \
./include/ffmpeg/libavutil/aarch64/float_dsp_neon.o 

C_DEPS += \
./include/ffmpeg/libavutil/aarch64/cpu.d \
./include/ffmpeg/libavutil/aarch64/float_dsp_init.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/libavutil/aarch64/%.o: ../include/ffmpeg/libavutil/aarch64/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/ffmpeg/libavutil/aarch64/%.o: ../include/ffmpeg/libavutil/aarch64/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


