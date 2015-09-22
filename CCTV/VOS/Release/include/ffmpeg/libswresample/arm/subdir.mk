################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/libswresample/arm/audio_convert_init.c \
../include/ffmpeg/libswresample/arm/neontest.c 

S_UPPER_SRCS += \
../include/ffmpeg/libswresample/arm/audio_convert_neon.S 

OBJS += \
./include/ffmpeg/libswresample/arm/audio_convert_init.o \
./include/ffmpeg/libswresample/arm/audio_convert_neon.o \
./include/ffmpeg/libswresample/arm/neontest.o 

C_DEPS += \
./include/ffmpeg/libswresample/arm/audio_convert_init.d \
./include/ffmpeg/libswresample/arm/neontest.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/libswresample/arm/%.o: ../include/ffmpeg/libswresample/arm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/ffmpeg/libswresample/arm/%.o: ../include/ffmpeg/libswresample/arm/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


