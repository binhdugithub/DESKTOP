################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/core/BcDataManager.cpp \
../src/core/BcMsg.cpp \
../src/core/BcNetworkInterfaceJob.cpp \
../src/core/BcProcessMsgJob.cpp \
../src/core/BcThreadObject.cpp 

OBJS += \
./src/core/BcDataManager.o \
./src/core/BcMsg.o \
./src/core/BcNetworkInterfaceJob.o \
./src/core/BcProcessMsgJob.o \
./src/core/BcThreadObject.o 

CPP_DEPS += \
./src/core/BcDataManager.d \
./src/core/BcMsg.d \
./src/core/BcNetworkInterfaceJob.d \
./src/core/BcProcessMsgJob.d \
./src/core/BcThreadObject.d 


# Each subdirectory must supply rules for building sources it contributes
src/core/%.o: ../src/core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


