################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/tools/aviocat.c \
../include/ffmpeg/tools/crypto_bench.c \
../include/ffmpeg/tools/cws2fws.c \
../include/ffmpeg/tools/enum_options.c \
../include/ffmpeg/tools/ffescape.c \
../include/ffmpeg/tools/ffeval.c \
../include/ffmpeg/tools/ffhash.c \
../include/ffmpeg/tools/fourcc2pixfmt.c \
../include/ffmpeg/tools/graph2dot.c \
../include/ffmpeg/tools/ismindex.c \
../include/ffmpeg/tools/pktdumper.c \
../include/ffmpeg/tools/probetest.c \
../include/ffmpeg/tools/qt-faststart.c \
../include/ffmpeg/tools/seek_print.c \
../include/ffmpeg/tools/trasher.c \
../include/ffmpeg/tools/uncoded_frame.c \
../include/ffmpeg/tools/yuvcmp.c \
../include/ffmpeg/tools/zmqsend.c 

OBJS += \
./include/ffmpeg/tools/aviocat.o \
./include/ffmpeg/tools/crypto_bench.o \
./include/ffmpeg/tools/cws2fws.o \
./include/ffmpeg/tools/enum_options.o \
./include/ffmpeg/tools/ffescape.o \
./include/ffmpeg/tools/ffeval.o \
./include/ffmpeg/tools/ffhash.o \
./include/ffmpeg/tools/fourcc2pixfmt.o \
./include/ffmpeg/tools/graph2dot.o \
./include/ffmpeg/tools/ismindex.o \
./include/ffmpeg/tools/pktdumper.o \
./include/ffmpeg/tools/probetest.o \
./include/ffmpeg/tools/qt-faststart.o \
./include/ffmpeg/tools/seek_print.o \
./include/ffmpeg/tools/trasher.o \
./include/ffmpeg/tools/uncoded_frame.o \
./include/ffmpeg/tools/yuvcmp.o \
./include/ffmpeg/tools/zmqsend.o 

C_DEPS += \
./include/ffmpeg/tools/aviocat.d \
./include/ffmpeg/tools/crypto_bench.d \
./include/ffmpeg/tools/cws2fws.d \
./include/ffmpeg/tools/enum_options.d \
./include/ffmpeg/tools/ffescape.d \
./include/ffmpeg/tools/ffeval.d \
./include/ffmpeg/tools/ffhash.d \
./include/ffmpeg/tools/fourcc2pixfmt.d \
./include/ffmpeg/tools/graph2dot.d \
./include/ffmpeg/tools/ismindex.d \
./include/ffmpeg/tools/pktdumper.d \
./include/ffmpeg/tools/probetest.d \
./include/ffmpeg/tools/qt-faststart.d \
./include/ffmpeg/tools/seek_print.d \
./include/ffmpeg/tools/trasher.d \
./include/ffmpeg/tools/uncoded_frame.d \
./include/ffmpeg/tools/yuvcmp.d \
./include/ffmpeg/tools/zmqsend.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/tools/%.o: ../include/ffmpeg/tools/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


