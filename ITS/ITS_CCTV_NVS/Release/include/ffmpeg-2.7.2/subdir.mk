################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../include/ffmpeg-2.7.2/cmdutils.o \
../include/ffmpeg-2.7.2/ffmpeg.o \
../include/ffmpeg-2.7.2/ffmpeg_filter.o \
../include/ffmpeg-2.7.2/ffmpeg_opt.o \
../include/ffmpeg-2.7.2/ffprobe.o \
../include/ffmpeg-2.7.2/ffserver.o \
../include/ffmpeg-2.7.2/ffserver_config.o 

C_SRCS += \
../include/ffmpeg-2.7.2/cmdutils.c \
../include/ffmpeg-2.7.2/ffmpeg.c \
../include/ffmpeg-2.7.2/ffmpeg_dxva2.c \
../include/ffmpeg-2.7.2/ffmpeg_filter.c \
../include/ffmpeg-2.7.2/ffmpeg_opt.c \
../include/ffmpeg-2.7.2/ffmpeg_vda.c \
../include/ffmpeg-2.7.2/ffmpeg_vdpau.c \
../include/ffmpeg-2.7.2/ffplay.c \
../include/ffmpeg-2.7.2/ffprobe.c \
../include/ffmpeg-2.7.2/ffserver.c \
../include/ffmpeg-2.7.2/ffserver_config.c 

OBJS += \
./include/ffmpeg-2.7.2/cmdutils.o \
./include/ffmpeg-2.7.2/ffmpeg.o \
./include/ffmpeg-2.7.2/ffmpeg_dxva2.o \
./include/ffmpeg-2.7.2/ffmpeg_filter.o \
./include/ffmpeg-2.7.2/ffmpeg_opt.o \
./include/ffmpeg-2.7.2/ffmpeg_vda.o \
./include/ffmpeg-2.7.2/ffmpeg_vdpau.o \
./include/ffmpeg-2.7.2/ffplay.o \
./include/ffmpeg-2.7.2/ffprobe.o \
./include/ffmpeg-2.7.2/ffserver.o \
./include/ffmpeg-2.7.2/ffserver_config.o 

C_DEPS += \
./include/ffmpeg-2.7.2/cmdutils.d \
./include/ffmpeg-2.7.2/ffmpeg.d \
./include/ffmpeg-2.7.2/ffmpeg_dxva2.d \
./include/ffmpeg-2.7.2/ffmpeg_filter.d \
./include/ffmpeg-2.7.2/ffmpeg_opt.d \
./include/ffmpeg-2.7.2/ffmpeg_vda.d \
./include/ffmpeg-2.7.2/ffmpeg_vdpau.d \
./include/ffmpeg-2.7.2/ffplay.d \
./include/ffmpeg-2.7.2/ffprobe.d \
./include/ffmpeg-2.7.2/ffserver.d \
./include/ffmpeg-2.7.2/ffserver_config.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg-2.7.2/%.o: ../include/ffmpeg-2.7.2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


