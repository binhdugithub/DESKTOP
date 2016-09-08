################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../dp/yo_pattern.cpp \
../dp/yo_singleton.cpp 

OBJS += \
./dp/yo_pattern.o \
./dp/yo_singleton.o 

CPP_DEPS += \
./dp/yo_pattern.d \
./dp/yo_singleton.d 


# Each subdirectory must supply rules for building sources it contributes
dp/%.o: ../dp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++11 -D__STDC_CONSTANT_MACROS -DWITH_NONAMESPACES -D_TURN_OFF_PLATFORM_STRING -DTIXML_USE_TICPP -I"/home/binhdu/workspace/CCTV_VOS/include" -I"/home/binhdu/workspace/CCTV_VOS/include/casablanca" -I"/home/binhdu/workspace/CCTV_VOS/include/BasicUsageEnvironment" -I"/home/binhdu/workspace/CCTV_VOS/include/UsageEnvironment" -I/opt/Qt5.7.0/5.7/gcc_64/include -I"/home/binhdu/workspace/CCTV_VOS/include/x264" -I"/home/binhdu/workspace/CCTV_VOS/include/tinyxml" -I"/home/binhdu/workspace/CCTV_VOS/include/mysqlcpp" -I"/home/binhdu/workspace/CCTV_VOS/include/Groupsock" -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


