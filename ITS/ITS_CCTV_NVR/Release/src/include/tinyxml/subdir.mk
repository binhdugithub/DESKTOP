################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/include/tinyxml/ticpp.cpp \
../src/include/tinyxml/tinystr.cpp \
../src/include/tinyxml/tinyxml.cpp \
../src/include/tinyxml/tinyxmlerror.cpp \
../src/include/tinyxml/tinyxmlparser.cpp \
../src/include/tinyxml/yo_xml.cpp 

OBJS += \
./src/include/tinyxml/ticpp.o \
./src/include/tinyxml/tinystr.o \
./src/include/tinyxml/tinyxml.o \
./src/include/tinyxml/tinyxmlerror.o \
./src/include/tinyxml/tinyxmlparser.o \
./src/include/tinyxml/yo_xml.o 

CPP_DEPS += \
./src/include/tinyxml/ticpp.d \
./src/include/tinyxml/tinystr.d \
./src/include/tinyxml/tinyxml.d \
./src/include/tinyxml/tinyxmlerror.d \
./src/include/tinyxml/tinyxmlparser.d \
./src/include/tinyxml/yo_xml.d 


# Each subdirectory must supply rules for building sources it contributes
src/include/tinyxml/%.o: ../src/include/tinyxml/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DWITH_NONAMESPACES -DTIXML_USE_TICPP -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/BasicUsageEnvironment" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/Groupsock" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/gsoap" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/liveMedia" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/log4cplus" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/mpeg4ip" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/mysqlcpp" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/nvrwebservice" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/tinyxml" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVR/src/include/UsageEnvironment" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


