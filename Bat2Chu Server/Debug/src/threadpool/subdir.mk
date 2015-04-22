################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/threadpool/HandleThreadPoolEvent.cpp \
../src/threadpool/ThreadJob.cpp \
../src/threadpool/ThreadManager.cpp \
../src/threadpool/ThreadObject.cpp 

OBJS += \
./src/threadpool/HandleThreadPoolEvent.o \
./src/threadpool/ThreadJob.o \
./src/threadpool/ThreadManager.o \
./src/threadpool/ThreadObject.o 

CPP_DEPS += \
./src/threadpool/HandleThreadPoolEvent.d \
./src/threadpool/ThreadJob.d \
./src/threadpool/ThreadManager.d \
./src/threadpool/ThreadObject.d 


# Each subdirectory must supply rules for building sources it contributes
src/threadpool/%.o: ../src/threadpool/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


