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
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++11 -fPIC -D__STDC_CONSTANT_MACROS -DWITH_NONAMESPACES -D_TURN_OFF_PLATFORM_STRING -DTIXML_USE_TICPP -I"/home/binhdu/workspace/CCTV_VOS/include" -I"/home/binhdu/workspace/CCTV_VOS/include/casablanca" -I"/home/binhdu/workspace/CCTV_VOS/include/BasicUsageEnvironment" -I"/home/binhdu/workspace/CCTV_VOS/include/UsageEnvironment" -I/opt/Qt5.7.0/5.7/gcc_64/include -I"/home/binhdu/workspace/CCTV_VOS/include/x264" -I"/home/binhdu/workspace/CCTV_VOS/include/tinyxml" -I"/home/binhdu/workspace/CCTV_VOS/include/mysqlcpp" -I"/home/binhdu/workspace/CCTV_VOS/include/Groupsock" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


