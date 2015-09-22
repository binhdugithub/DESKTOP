################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../RTSPClient/RTSPClient/include/WindowsAudioInputDevice/WindowsAudioInputDevice_common.cpp \
../RTSPClient/RTSPClient/include/WindowsAudioInputDevice/WindowsAudioInputDevice_mixer.cpp \
../RTSPClient/RTSPClient/include/WindowsAudioInputDevice/WindowsAudioInputDevice_noMixer.cpp \
../RTSPClient/RTSPClient/include/WindowsAudioInputDevice/showAudioInputPorts.cpp 

OBJS += \
./RTSPClient/RTSPClient/include/WindowsAudioInputDevice/WindowsAudioInputDevice_common.o \
./RTSPClient/RTSPClient/include/WindowsAudioInputDevice/WindowsAudioInputDevice_mixer.o \
./RTSPClient/RTSPClient/include/WindowsAudioInputDevice/WindowsAudioInputDevice_noMixer.o \
./RTSPClient/RTSPClient/include/WindowsAudioInputDevice/showAudioInputPorts.o 

CPP_DEPS += \
./RTSPClient/RTSPClient/include/WindowsAudioInputDevice/WindowsAudioInputDevice_common.d \
./RTSPClient/RTSPClient/include/WindowsAudioInputDevice/WindowsAudioInputDevice_mixer.d \
./RTSPClient/RTSPClient/include/WindowsAudioInputDevice/WindowsAudioInputDevice_noMixer.d \
./RTSPClient/RTSPClient/include/WindowsAudioInputDevice/showAudioInputPorts.d 


# Each subdirectory must supply rules for building sources it contributes
RTSPClient/RTSPClient/include/WindowsAudioInputDevice/%.o: ../RTSPClient/RTSPClient/include/WindowsAudioInputDevice/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/xyz/workspace/ITS/ITS_2.0_ELC/04.Construction/CCTV/src/CCTV_VOS/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


