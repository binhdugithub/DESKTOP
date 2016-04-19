################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/libswresample/x86/audio_convert_init.c \
../include/ffmpeg/libswresample/x86/rematrix_init.c \
../include/ffmpeg/libswresample/x86/resample_init.c \
../include/ffmpeg/libswresample/x86/w64xmmtest.c 

ASM_SRCS += \
../include/ffmpeg/libswresample/x86/audio_convert.asm \
../include/ffmpeg/libswresample/x86/rematrix.asm \
../include/ffmpeg/libswresample/x86/resample.asm 

OBJS += \
./include/ffmpeg/libswresample/x86/audio_convert.o \
./include/ffmpeg/libswresample/x86/audio_convert_init.o \
./include/ffmpeg/libswresample/x86/rematrix.o \
./include/ffmpeg/libswresample/x86/rematrix_init.o \
./include/ffmpeg/libswresample/x86/resample.o \
./include/ffmpeg/libswresample/x86/resample_init.o \
./include/ffmpeg/libswresample/x86/w64xmmtest.o 

C_DEPS += \
./include/ffmpeg/libswresample/x86/audio_convert_init.d \
./include/ffmpeg/libswresample/x86/rematrix_init.d \
./include/ffmpeg/libswresample/x86/resample_init.d \
./include/ffmpeg/libswresample/x86/w64xmmtest.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/libswresample/x86/%.o: ../include/ffmpeg/libswresample/x86/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/ffmpeg/libswresample/x86/%.o: ../include/ffmpeg/libswresample/x86/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


