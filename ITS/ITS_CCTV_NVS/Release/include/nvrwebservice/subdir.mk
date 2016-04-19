################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../include/nvrwebservice/soapC.cpp \
../include/nvrwebservice/soapnvrProxy.cpp \
../include/nvrwebservice/soapnvrService.cpp 

OBJS += \
./include/nvrwebservice/soapC.o \
./include/nvrwebservice/soapnvrProxy.o \
./include/nvrwebservice/soapnvrService.o 

CPP_DEPS += \
./include/nvrwebservice/soapC.d \
./include/nvrwebservice/soapnvrProxy.d \
./include/nvrwebservice/soapnvrService.d 


# Each subdirectory must supply rules for building sources it contributes
include/nvrwebservice/%.o: ../include/nvrwebservice/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTIXML_USE_TICPP -DWITH_NONAMESPACES -D__STDC_CONSTANT_MACROS -I"/home/binhdu/workspace/ITS_CCTV_NVR_STREAMING/include/mysqlcpp" -I"/home/binhdu/workspace/ITS_CCTV_NVR_STREAMING/include/ffmpeg" -I"/home/binhdu/workspace/ITS_CCTV_NVR_STREAMING/include/mpeg4ip/include" -I"/home/binhdu/workspace/ITS_CCTV_NVR_STREAMING/include/liveMedia" -I"/home/binhdu/workspace/ITS_CCTV_NVR_STREAMING/include/liveMedia/include" -I"/home/binhdu/workspace/ITS_CCTV_NVR_STREAMING/include/gsoap" -I"/home/binhdu/workspace/ITS_CCTV_NVR_STREAMING/include" -I"/home/binhdu/workspace/ITS_CCTV_NVR_STREAMING/include/nvrwebservice" -I"/home/binhdu/workspace/ITS_CCTV_NVR_STREAMING/include/BasicUsageEnvironment" -I"/home/binhdu/workspace/ITS_CCTV_NVR_STREAMING/include/Groupsock" -I"/home/binhdu/workspace/ITS_CCTV_NVR_STREAMING/include/UsageEnvironment" -I"/home/binhdu/workspace/ITS_CCTV_NVR_STREAMING/include/tinyxml" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


