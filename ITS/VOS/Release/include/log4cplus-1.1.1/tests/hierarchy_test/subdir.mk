################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CXX_SRCS += \
../include/log4cplus-1.1.1/tests/hierarchy_test/main.cxx 

OBJS += \
./include/log4cplus-1.1.1/tests/hierarchy_test/main.o 

CXX_DEPS += \
./include/log4cplus-1.1.1/tests/hierarchy_test/main.d 


# Each subdirectory must supply rules for building sources it contributes
include/log4cplus-1.1.1/tests/hierarchy_test/%.o: ../include/log4cplus-1.1.1/tests/hierarchy_test/%.cxx
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


