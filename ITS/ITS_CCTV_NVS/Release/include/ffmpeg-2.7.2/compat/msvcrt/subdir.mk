################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg-2.7.2/compat/msvcrt/snprintf.c 

OBJS += \
./include/ffmpeg-2.7.2/compat/msvcrt/snprintf.o 

C_DEPS += \
./include/ffmpeg-2.7.2/compat/msvcrt/snprintf.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg-2.7.2/compat/msvcrt/%.o: ../include/ffmpeg-2.7.2/compat/msvcrt/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


