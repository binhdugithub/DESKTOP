################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../include/tinyxml/ticpp.cpp \
../include/tinyxml/tinystr.cpp \
../include/tinyxml/tinyxml.cpp \
../include/tinyxml/tinyxmlerror.cpp \
../include/tinyxml/tinyxmlparser.cpp \
../include/tinyxml/yo_xml.cpp 

OBJS += \
./include/tinyxml/ticpp.o \
./include/tinyxml/tinystr.o \
./include/tinyxml/tinyxml.o \
./include/tinyxml/tinyxmlerror.o \
./include/tinyxml/tinyxmlparser.o \
./include/tinyxml/yo_xml.o 

CPP_DEPS += \
./include/tinyxml/ticpp.d \
./include/tinyxml/tinystr.d \
./include/tinyxml/tinyxml.d \
./include/tinyxml/tinyxmlerror.d \
./include/tinyxml/tinyxmlparser.d \
./include/tinyxml/yo_xml.d 


# Each subdirectory must supply rules for building sources it contributes
include/tinyxml/%.o: ../include/tinyxml/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTIXML_USE_TICPP -DWITH_NONAMESPACES -D__STDC_CONSTANT_MACROS -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVS/include/mysqlcpp" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVS/include/mpeg4ip/include" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVS/include/liveMedia" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVS/include" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVS/include/nvrwebservice" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVS/include/BasicUsageEnvironment" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVS/include/Groupsock" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVS/include/UsageEnvironment" -I"/run/media/binhdu/DATA/WORKSPACE/ITS_CCTV_NVS/include/tinyxml" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


