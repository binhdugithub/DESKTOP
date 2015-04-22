################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/designparttern/ElcDesignPattern.cpp \
../src/designparttern/ElcSingleton.cpp 

OBJS += \
./src/designparttern/ElcDesignPattern.o \
./src/designparttern/ElcSingleton.o 

CPP_DEPS += \
./src/designparttern/ElcDesignPattern.d \
./src/designparttern/ElcSingleton.d 


# Each subdirectory must supply rules for building sources it contributes
src/designparttern/%.o: ../src/designparttern/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


