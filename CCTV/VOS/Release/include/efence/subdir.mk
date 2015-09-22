################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/efence/efence.c \
../include/efence/page.c \
../include/efence/print.c 

OBJS += \
./include/efence/efence.o \
./include/efence/page.o \
./include/efence/print.o 

C_DEPS += \
./include/efence/efence.d \
./include/efence/page.d \
./include/efence/print.d 


# Each subdirectory must supply rules for building sources it contributes
include/efence/%.o: ../include/efence/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


