################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/compat/getopt.c \
../include/ffmpeg/compat/strtod.c 

OBJS += \
./include/ffmpeg/compat/getopt.o \
./include/ffmpeg/compat/strtod.o 

C_DEPS += \
./include/ffmpeg/compat/getopt.d \
./include/ffmpeg/compat/strtod.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/compat/%.o: ../include/ffmpeg/compat/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


