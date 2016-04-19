################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg-2.7.2/libavresample/aarch64/audio_convert_init.c \
../include/ffmpeg-2.7.2/libavresample/aarch64/neontest.c \
../include/ffmpeg-2.7.2/libavresample/aarch64/resample_init.c 

S_UPPER_SRCS += \
../include/ffmpeg-2.7.2/libavresample/aarch64/audio_convert_neon.S \
../include/ffmpeg-2.7.2/libavresample/aarch64/resample_neon.S 

OBJS += \
./include/ffmpeg-2.7.2/libavresample/aarch64/audio_convert_init.o \
./include/ffmpeg-2.7.2/libavresample/aarch64/audio_convert_neon.o \
./include/ffmpeg-2.7.2/libavresample/aarch64/neontest.o \
./include/ffmpeg-2.7.2/libavresample/aarch64/resample_init.o \
./include/ffmpeg-2.7.2/libavresample/aarch64/resample_neon.o 

C_DEPS += \
./include/ffmpeg-2.7.2/libavresample/aarch64/audio_convert_init.d \
./include/ffmpeg-2.7.2/libavresample/aarch64/neontest.d \
./include/ffmpeg-2.7.2/libavresample/aarch64/resample_init.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg-2.7.2/libavresample/aarch64/%.o: ../include/ffmpeg-2.7.2/libavresample/aarch64/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/ffmpeg-2.7.2/libavresample/aarch64/%.o: ../include/ffmpeg-2.7.2/libavresample/aarch64/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


