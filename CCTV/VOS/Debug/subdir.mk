################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DummySink.cpp \
../ElcRTSPClient.cpp \
../Encoder.cpp \
../FFMpegVideoDecoder.cpp \
../LogFile.cpp \
../Mp4Encode.cpp \
../config.cpp \
../dbcontrol.cpp \
../elcrtspserver.cpp \
../ffmpegvideoencoder.cpp \
../imageoverlaytext.cpp \
../main.cpp \
../mpeg4encoder.cpp \
../mpeg4liveservermediasubsession.cpp \
../mpeg4livesource.cpp \
../multicastprocessing.cpp \
../soapC.cpp \
../soapvideooverlayProxy.cpp \
../soapvideooverlayService.cpp \
../sourcemanager.cpp \
../stdsoap2.cpp \
../videoeffect.cpp 

C_SRCS += \
../h264parser.c 

CC_SRCS += \
../TollMessage.pb.cc \
../test.pb.cc 

OBJS += \
./DummySink.o \
./ElcRTSPClient.o \
./Encoder.o \
./FFMpegVideoDecoder.o \
./LogFile.o \
./Mp4Encode.o \
./TollMessage.pb.o \
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
./multicastprocessing.o \
./soapC.o \
./soapvideooverlayProxy.o \
./soapvideooverlayService.o \
./sourcemanager.o \
./stdsoap2.o \
./test.pb.o \
./videoeffect.o 

C_DEPS += \
./h264parser.d 

CC_DEPS += \
./TollMessage.pb.d \
./test.pb.d 

CPP_DEPS += \
./DummySink.d \
./ElcRTSPClient.d \
./Encoder.d \
./FFMpegVideoDecoder.d \
./LogFile.d \
./Mp4Encode.d \
./config.d \
./dbcontrol.d \
./elcrtspserver.d \
./ffmpegvideoencoder.d \
./imageoverlaytext.d \
./main.d \
./mpeg4encoder.d \
./mpeg4liveservermediasubsession.d \
./mpeg4livesource.d \
./multicastprocessing.d \
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
	g++ -std=c++11 -D__STDC_CONSTANT_MACROS -DWITH_NONAMESPACES -DTIXML_USE_TICPP -I"/home/binhdu/workspace/CCTV_VOS/include" -I"/home/binhdu/workspace/CCTV_VOS/include/x264" -I/home/binhdu/Qt5.4.1/5.4/gcc/include/ -I"/home/binhdu/workspace/CCTV_VOS/include/tinyxml" -I"/home/binhdu/workspace/CCTV_VOS/include/mysql" -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++11 -D__STDC_CONSTANT_MACROS -DWITH_NONAMESPACES -DTIXML_USE_TICPP -I"/home/binhdu/workspace/CCTV_VOS/include" -I"/home/binhdu/workspace/CCTV_VOS/include/x264" -I/home/binhdu/Qt5.4.1/5.4/gcc/include/ -I"/home/binhdu/workspace/CCTV_VOS/include/tinyxml" -I"/home/binhdu/workspace/CCTV_VOS/include/mysql" -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -D__STDC_CONSTANT_MACROS -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


