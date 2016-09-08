################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/libavresample/arm/audio_convert_init.c \
../include/ffmpeg/libavresample/arm/neontest.c 

S_UPPER_SRCS += \
../include/ffmpeg/libavresample/arm/audio_convert_neon.S 

OBJS += \
./include/ffmpeg/libavresample/arm/audio_convert_init.o \
./include/ffmpeg/libavresample/arm/audio_convert_neon.o \
./include/ffmpeg/libavresample/arm/neontest.o 

C_DEPS += \
./include/ffmpeg/libavresample/arm/audio_convert_init.d \
./include/ffmpeg/libavresample/arm/neontest.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/libavresample/arm/%.o: ../include/ffmpeg/libavresample/arm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/ffmpeg/libavresample/arm/%.o: ../include/ffmpeg/libavresample/arm/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


