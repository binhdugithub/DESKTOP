################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../RTSPClient/RTSPClient/DummySink.cpp \
../RTSPClient/RTSPClient/ManageMyRTSPClient.cpp \
../RTSPClient/RTSPClient/MyRTSPClient.cpp \
../RTSPClient/RTSPClient/OurRTSPClient.cpp \
../RTSPClient/RTSPClient/RTSPClient.cpp \
../RTSPClient/RTSPClient/StreamClientState.cpp \
../RTSPClient/RTSPClient/stdafx.cpp \
../RTSPClient/RTSPClient/testRTSPClient.cpp 

OBJS += \
./RTSPClient/RTSPClient/DummySink.o \
./RTSPClient/RTSPClient/ManageMyRTSPClient.o \
./RTSPClient/RTSPClient/MyRTSPClient.o \
./RTSPClient/RTSPClient/OurRTSPClient.o \
./RTSPClient/RTSPClient/RTSPClient.o \
./RTSPClient/RTSPClient/StreamClientState.o \
./RTSPClient/RTSPClient/stdafx.o \
./RTSPClient/RTSPClient/testRTSPClient.o 

CPP_DEPS += \
./RTSPClient/RTSPClient/DummySink.d \
./RTSPClient/RTSPClient/ManageMyRTSPClient.d \
./RTSPClient/RTSPClient/MyRTSPClient.d \
./RTSPClient/RTSPClient/OurRTSPClient.d \
./RTSPClient/RTSPClient/RTSPClient.d \
./RTSPClient/RTSPClient/StreamClientState.d \
./RTSPClient/RTSPClient/stdafx.d \
./RTSPClient/RTSPClient/testRTSPClient.d 


# Each subdirectory must supply rules for building sources it contributes
RTSPClient/RTSPClient/%.o: ../RTSPClient/RTSPClient/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/xyz/workspace/ITS/ITS_2.0_ELC/04.Construction/CCTV/src/CCTV_VOS/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


