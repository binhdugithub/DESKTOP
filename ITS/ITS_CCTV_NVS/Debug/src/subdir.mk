################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DBWoker.cpp \
../src/ITS_CCTV_NVR_STREAMING.cpp \
../src/LogFile.cpp \
../src/commondef.cpp \
../src/elcrtspserver.cpp \
../src/filehandler.cpp \
../src/filesource.cpp \
../src/h264filemediasubsession.cpp \
../src/h264filesource.cpp \
../src/mpeg4filemediasubsession.cpp \
../src/mpeg4filesource.cpp 

C_SRCS += \
../src/h264parser.c 

OBJS += \
./src/DBWoker.o \
./src/ITS_CCTV_NVR_STREAMING.o \
./src/LogFile.o \
./src/commondef.o \
./src/elcrtspserver.o \
./src/filehandler.o \
./src/filesource.o \
./src/h264filemediasubsession.o \
./src/h264filesource.o \
./src/h264parser.o \
./src/mpeg4filemediasubsession.o \
./src/mpeg4filesource.o 

CPP_DEPS += \
./src/DBWoker.d \
./src/ITS_CCTV_NVR_STREAMING.d \
./src/LogFile.d \
./src/commondef.d \
./src/elcrtspserver.d \
./src/filehandler.d \
./src/filesource.d \
./src/h264filemediasubsession.d \
./src/h264filesource.d \
./src/mpeg4filemediasubsession.d \
./src/mpeg4filesource.d 

C_DEPS += \
./src/h264parser.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


