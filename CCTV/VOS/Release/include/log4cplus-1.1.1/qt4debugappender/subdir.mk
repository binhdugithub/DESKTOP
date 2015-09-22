################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CXX_SRCS += \
../include/log4cplus-1.1.1/qt4debugappender/qt4debugappender.cxx 

OBJS += \
./include/log4cplus-1.1.1/qt4debugappender/qt4debugappender.o 

CXX_DEPS += \
./include/log4cplus-1.1.1/qt4debugappender/qt4debugappender.d 


# Each subdirectory must supply rules for building sources it contributes
include/log4cplus-1.1.1/qt4debugappender/%.o: ../include/log4cplus-1.1.1/qt4debugappender/%.cxx
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


