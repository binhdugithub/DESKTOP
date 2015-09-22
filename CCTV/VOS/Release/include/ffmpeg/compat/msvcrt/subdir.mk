################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/compat/msvcrt/snprintf.c 

OBJS += \
./include/ffmpeg/compat/msvcrt/snprintf.o 

C_DEPS += \
./include/ffmpeg/compat/msvcrt/snprintf.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/compat/msvcrt/%.o: ../include/ffmpeg/compat/msvcrt/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


