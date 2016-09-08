################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/libavcodec/alpha/blockdsp_alpha.c \
../include/ffmpeg/libavcodec/alpha/dsputil_alpha.c \
../include/ffmpeg/libavcodec/alpha/hpeldsp_alpha.c \
../include/ffmpeg/libavcodec/alpha/idctdsp_alpha.c \
../include/ffmpeg/libavcodec/alpha/motion_est_alpha.c \
../include/ffmpeg/libavcodec/alpha/mpegvideo_alpha.c \
../include/ffmpeg/libavcodec/alpha/pixblockdsp_alpha.c \
../include/ffmpeg/libavcodec/alpha/simple_idct_alpha.c 

S_UPPER_SRCS += \
../include/ffmpeg/libavcodec/alpha/hpeldsp_alpha_asm.S \
../include/ffmpeg/libavcodec/alpha/idctdsp_alpha_asm.S \
../include/ffmpeg/libavcodec/alpha/motion_est_mvi_asm.S 

OBJS += \
./include/ffmpeg/libavcodec/alpha/blockdsp_alpha.o \
./include/ffmpeg/libavcodec/alpha/dsputil_alpha.o \
./include/ffmpeg/libavcodec/alpha/hpeldsp_alpha.o \
./include/ffmpeg/libavcodec/alpha/hpeldsp_alpha_asm.o \
./include/ffmpeg/libavcodec/alpha/idctdsp_alpha.o \
./include/ffmpeg/libavcodec/alpha/idctdsp_alpha_asm.o \
./include/ffmpeg/libavcodec/alpha/motion_est_alpha.o \
./include/ffmpeg/libavcodec/alpha/motion_est_mvi_asm.o \
./include/ffmpeg/libavcodec/alpha/mpegvideo_alpha.o \
./include/ffmpeg/libavcodec/alpha/pixblockdsp_alpha.o \
./include/ffmpeg/libavcodec/alpha/simple_idct_alpha.o 

C_DEPS += \
./include/ffmpeg/libavcodec/alpha/blockdsp_alpha.d \
./include/ffmpeg/libavcodec/alpha/dsputil_alpha.d \
./include/ffmpeg/libavcodec/alpha/hpeldsp_alpha.d \
./include/ffmpeg/libavcodec/alpha/idctdsp_alpha.d \
./include/ffmpeg/libavcodec/alpha/motion_est_alpha.d \
./include/ffmpeg/libavcodec/alpha/mpegvideo_alpha.d \
./include/ffmpeg/libavcodec/alpha/pixblockdsp_alpha.d \
./include/ffmpeg/libavcodec/alpha/simple_idct_alpha.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/libavcodec/alpha/%.o: ../include/ffmpeg/libavcodec/alpha/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/ffmpeg/libavcodec/alpha/%.o: ../include/ffmpeg/libavcodec/alpha/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


