################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/database/BLL/Images.cpp \
../src/database/BLL/Table.cpp \
../src/database/BLL/Users.cpp 

OBJS += \
./src/database/BLL/Images.o \
./src/database/BLL/Table.o \
./src/database/BLL/Users.o 

CPP_DEPS += \
./src/database/BLL/Images.d \
./src/database/BLL/Table.d \
./src/database/BLL/Users.d 


# Each subdirectory must supply rules for building sources it contributes
src/database/BLL/%.o: ../src/database/BLL/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


