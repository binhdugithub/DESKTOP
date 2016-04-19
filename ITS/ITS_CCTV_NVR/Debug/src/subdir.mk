################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Camera.cpp \
../src/Configuration.cpp \
../src/DBWoker.cpp \
../src/LogFile.cpp \
../src/ManagerRecorder.cpp \
../src/ProcessNVR.cpp \
../src/Recorder.cpp \
../src/commondef.cpp \
../src/main.cpp 

OBJS += \
./src/Camera.o \
./src/Configuration.o \
./src/DBWoker.o \
./src/LogFile.o \
./src/ManagerRecorder.o \
./src/ProcessNVR.o \
./src/Recorder.o \
./src/commondef.o \
./src/main.o 

CPP_DEPS += \
./src/Camera.d \
./src/Configuration.d \
./src/DBWoker.d \
./src/LogFile.d \
./src/ManagerRecorder.d \
./src/ProcessNVR.d \
./src/Recorder.d \
./src/commondef.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DWITH_NONAMESPACES -DTIXML_USE_TICPP -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/BasicUsageEnvironment" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/Groupsock" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/gsoap" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/liveMedia" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/log4cplus" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/mpeg4ip" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/mysqlcpp" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/nvrwebservice" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/tinyxml" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/UsageEnvironment" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


