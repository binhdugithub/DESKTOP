################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/doc/print_options.c 

OBJS += \
./include/ffmpeg/doc/print_options.o 

C_DEPS += \
./include/ffmpeg/doc/print_options.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/doc/%.o: ../include/ffmpeg/doc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


