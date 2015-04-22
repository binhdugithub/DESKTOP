################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/database/DAL/DataAccess.cpp 

OBJS += \
./src/database/DAL/DataAccess.o 

CPP_DEPS += \
./src/database/DAL/DataAccess.d 


# Each subdirectory must supply rules for building sources it contributes
src/database/DAL/%.o: ../src/database/DAL/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


