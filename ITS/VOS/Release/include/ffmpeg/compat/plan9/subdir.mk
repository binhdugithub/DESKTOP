################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/compat/plan9/main.c 

OBJS += \
./include/ffmpeg/compat/plan9/main.o 

C_DEPS += \
./include/ffmpeg/compat/plan9/main.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/compat/plan9/%.o: ../include/ffmpeg/compat/plan9/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


