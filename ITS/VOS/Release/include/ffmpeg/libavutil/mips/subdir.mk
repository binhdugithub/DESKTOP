################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/libavutil/mips/float_dsp_mips.c 

OBJS += \
./include/ffmpeg/libavutil/mips/float_dsp_mips.o 

C_DEPS += \
./include/ffmpeg/libavutil/mips/float_dsp_mips.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/libavutil/mips/%.o: ../include/ffmpeg/libavutil/mips/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


