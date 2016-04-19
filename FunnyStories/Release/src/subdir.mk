################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/App.cpp \
../src/Configuration.cpp \
../src/DBInterface.cpp \
../src/DataAccess.cpp \
../src/FSProcessing.cpp \
../src/Main.cpp \
../src/MyLogger.cpp \
../src/RESTHandler.cpp \
../src/RESTServer.cpp \
../src/Story.cpp 

OBJS += \
./src/App.o \
./src/Configuration.o \
./src/DBInterface.o \
./src/DataAccess.o \
./src/FSProcessing.o \
./src/Main.o \
./src/MyLogger.o \
./src/RESTHandler.o \
./src/RESTServer.o \
./src/Story.o 

CPP_DEPS += \
./src/App.d \
./src/Configuration.d \
./src/DBInterface.d \
./src/DataAccess.d \
./src/FSProcessing.d \
./src/Main.d \
./src/MyLogger.d \
./src/RESTHandler.d \
./src/RESTServer.d \
./src/Story.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/run/media/binhdu/DATA/WORKSPACE/FunnyStories/include/casablanca" -I"/run/media/binhdu/DATA/WORKSPACE/FunnyStories/include/mysqlcpp" -I"/run/media/binhdu/DATA/WORKSPACE/FunnyStories/include/log4cplus" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


