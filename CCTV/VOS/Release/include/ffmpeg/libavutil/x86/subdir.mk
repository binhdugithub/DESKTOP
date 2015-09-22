################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/libavutil/x86/cpu.c \
../include/ffmpeg/libavutil/x86/float_dsp_init.c \
../include/ffmpeg/libavutil/x86/lls_init.c 

ASM_SRCS += \
../include/ffmpeg/libavutil/x86/cpuid.asm \
../include/ffmpeg/libavutil/x86/emms.asm \
../include/ffmpeg/libavutil/x86/float_dsp.asm \
../include/ffmpeg/libavutil/x86/lls.asm \
../include/ffmpeg/libavutil/x86/x86inc.asm \
../include/ffmpeg/libavutil/x86/x86util.asm 

OBJS += \
./include/ffmpeg/libavutil/x86/cpu.o \
./include/ffmpeg/libavutil/x86/cpuid.o \
./include/ffmpeg/libavutil/x86/emms.o \
./include/ffmpeg/libavutil/x86/float_dsp.o \
./include/ffmpeg/libavutil/x86/float_dsp_init.o \
./include/ffmpeg/libavutil/x86/lls.o \
./include/ffmpeg/libavutil/x86/lls_init.o \
./include/ffmpeg/libavutil/x86/x86inc.o \
./include/ffmpeg/libavutil/x86/x86util.o 

C_DEPS += \
./include/ffmpeg/libavutil/x86/cpu.d \
./include/ffmpeg/libavutil/x86/float_dsp_init.d \
./include/ffmpeg/libavutil/x86/lls_init.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/libavutil/x86/%.o: ../include/ffmpeg/libavutil/x86/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/ffmpeg/libavutil/x86/%.o: ../include/ffmpeg/libavutil/x86/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


