################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/libavresample/aarch64/audio_convert_init.c \
../include/ffmpeg/libavresample/aarch64/neontest.c \
../include/ffmpeg/libavresample/aarch64/resample_init.c 

S_UPPER_SRCS += \
../include/ffmpeg/libavresample/aarch64/audio_convert_neon.S \
../include/ffmpeg/libavresample/aarch64/resample_neon.S 

OBJS += \
./include/ffmpeg/libavresample/aarch64/audio_convert_init.o \
./include/ffmpeg/libavresample/aarch64/audio_convert_neon.o \
./include/ffmpeg/libavresample/aarch64/neontest.o \
./include/ffmpeg/libavresample/aarch64/resample_init.o \
./include/ffmpeg/libavresample/aarch64/resample_neon.o 

C_DEPS += \
./include/ffmpeg/libavresample/aarch64/audio_convert_init.d \
./include/ffmpeg/libavresample/aarch64/neontest.d \
./include/ffmpeg/libavresample/aarch64/resample_init.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/libavresample/aarch64/%.o: ../include/ffmpeg/libavresample/aarch64/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/ffmpeg/libavresample/aarch64/%.o: ../include/ffmpeg/libavresample/aarch64/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


