################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/libavresample/x86/audio_convert_init.c \
../include/ffmpeg/libavresample/x86/audio_mix_init.c \
../include/ffmpeg/libavresample/x86/dither_init.c \
../include/ffmpeg/libavresample/x86/w64xmmtest.c 

ASM_SRCS += \
../include/ffmpeg/libavresample/x86/audio_convert.asm \
../include/ffmpeg/libavresample/x86/audio_mix.asm \
../include/ffmpeg/libavresample/x86/dither.asm \
../include/ffmpeg/libavresample/x86/util.asm 

OBJS += \
./include/ffmpeg/libavresample/x86/audio_convert.o \
./include/ffmpeg/libavresample/x86/audio_convert_init.o \
./include/ffmpeg/libavresample/x86/audio_mix.o \
./include/ffmpeg/libavresample/x86/audio_mix_init.o \
./include/ffmpeg/libavresample/x86/dither.o \
./include/ffmpeg/libavresample/x86/dither_init.o \
./include/ffmpeg/libavresample/x86/util.o \
./include/ffmpeg/libavresample/x86/w64xmmtest.o 

C_DEPS += \
./include/ffmpeg/libavresample/x86/audio_convert_init.d \
./include/ffmpeg/libavresample/x86/audio_mix_init.d \
./include/ffmpeg/libavresample/x86/dither_init.d \
./include/ffmpeg/libavresample/x86/w64xmmtest.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/libavresample/x86/%.o: ../include/ffmpeg/libavresample/x86/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/ffmpeg/libavresample/x86/%.o: ../include/ffmpeg/libavresample/x86/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


