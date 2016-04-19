################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/include/gsoap/stdsoap2.cpp 

OBJS += \
./src/include/gsoap/stdsoap2.o 

CPP_DEPS += \
./src/include/gsoap/stdsoap2.d 


# Each subdirectory must supply rules for building sources it contributes
src/include/gsoap/%.o: ../src/include/gsoap/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DWITH_NONAMESPACES -DTIXML_USE_TICPP -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/BasicUsageEnvironment" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/Groupsock" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/gsoap" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/liveMedia" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/log4cplus" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/mpeg4ip" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/mysqlcpp" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/nvrwebservice" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/tinyxml" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/UsageEnvironment" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


