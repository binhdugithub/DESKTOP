################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../test.pb.cc 

C_SRCS += \
../h264parser.c 

CPP_SRCS += \
../DataAccess.cpp \
../DummySink.cpp \
../ElcRTSPClient.cpp \
../Encoder.cpp \
../FFMpegVideoDecoder.cpp \
../LogFile.cpp \
../MyRESTServer.cpp \
../config.cpp \
../dbcontrol.cpp \
../elcrtspserver.cpp \
../ffmpegvideoencoder.cpp \
../imageoverlaytext.cpp \
../main.cpp \
../mpeg4encoder.cpp \
../mpeg4liveservermediasubsession.cpp \
../mpeg4livesource.cpp \
../soapC.cpp \
../soapvideooverlayProxy.cpp \
../soapvideooverlayService.cpp \
../sourcemanager.cpp \
../stdsoap2.cpp \
../videoeffect.cpp 

CC_DEPS += \
./test.pb.d 

OBJS += \
./DataAccess.o \
./DummySink.o \
./ElcRTSPClient.o \
./Encoder.o \
./FFMpegVideoDecoder.o \
./LogFile.o \
./MyRESTServer.o \
./config.o \
./dbcontrol.o \
./elcrtspserver.o \
./ffmpegvideoencoder.o \
./h264parser.o \
./imageoverlaytext.o \
./main.o \
./mpeg4encoder.o \
./mpeg4liveservermediasubsession.o \
./mpeg4livesource.o \
./soapC.o \
./soapvideooverlayProxy.o \
./soapvideooverlayService.o \
./sourcemanager.o \
./stdsoap2.o \
./test.pb.o \
./videoeffect.o 

C_DEPS += \
./h264parser.d 

CPP_DEPS += \
./DataAccess.d \
./DummySink.d \
./ElcRTSPClient.d \
./Encoder.d \
./FFMpegVideoDecoder.d \
./LogFile.d \
./MyRESTServer.d \
./config.d \
./dbcontrol.d \
./elcrtspserver.d \
./ffmpegvideoencoder.d \
./imageoverlaytext.d \
./main.d \
./mpeg4encoder.d \
./mpeg4liveservermediasubsession.d \
./mpeg4livesource.d \
./soapC.d \
./soapvideooverlayProxy.d \
./soapvideooverlayService.d \
./sourcemanager.d \
./stdsoap2.d \
./videoeffect.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++11 -D__STDC_CONSTANT_MACROS -DWITH_NONAMESPACES -D_TURN_OFF_PLATFORM_STRING -DTIXML_USE_TICPP -I"/home/binhdu/workspace/CCTV_VOS/include" -I"/home/binhdu/workspace/CCTV_VOS/include/casablanca" -I"/home/binhdu/workspace/CCTV_VOS/include/BasicUsageEnvironment" -I"/home/binhdu/workspace/CCTV_VOS/include/UsageEnvironment" -I/opt/Qt5.7.0/5.7/gcc_64/include -I"/home/binhdu/workspace/CCTV_VOS/include/x264" -I"/home/binhdu/workspace/CCTV_VOS/include/tinyxml" -I"/home/binhdu/workspace/CCTV_VOS/include/mysqlcpp" -I"/home/binhdu/workspace/CCTV_VOS/include/Groupsock" -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++11 -D__STDC_CONSTANT_MACROS -DWITH_NONAMESPACES -D_TURN_OFF_PLATFORM_STRING -DTIXML_USE_TICPP -I"/home/binhdu/workspace/CCTV_VOS/include" -I"/home/binhdu/workspace/CCTV_VOS/include/casablanca" -I"/home/binhdu/workspace/CCTV_VOS/include/BasicUsageEnvironment" -I"/home/binhdu/workspace/CCTV_VOS/include/UsageEnvironment" -I/opt/Qt5.7.0/5.7/gcc_64/include -I"/home/binhdu/workspace/CCTV_VOS/include/x264" -I"/home/binhdu/workspace/CCTV_VOS/include/tinyxml" -I"/home/binhdu/workspace/CCTV_VOS/include/mysqlcpp" -I"/home/binhdu/workspace/CCTV_VOS/include/Groupsock" -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


