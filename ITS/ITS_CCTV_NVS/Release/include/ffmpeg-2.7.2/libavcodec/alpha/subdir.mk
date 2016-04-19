################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg-2.7.2/libavcodec/alpha/blockdsp_alpha.c \
../include/ffmpeg-2.7.2/libavcodec/alpha/hpeldsp_alpha.c \
../include/ffmpeg-2.7.2/libavcodec/alpha/idctdsp_alpha.c \
../include/ffmpeg-2.7.2/libavcodec/alpha/me_cmp_alpha.c \
../include/ffmpeg-2.7.2/libavcodec/alpha/mpegvideo_alpha.c \
../include/ffmpeg-2.7.2/libavcodec/alpha/pixblockdsp_alpha.c \
../include/ffmpeg-2.7.2/libavcodec/alpha/simple_idct_alpha.c 

S_UPPER_SRCS += \
../include/ffmpeg-2.7.2/libavcodec/alpha/hpeldsp_alpha_asm.S \
../include/ffmpeg-2.7.2/libavcodec/alpha/idctdsp_alpha_asm.S \
../include/ffmpeg-2.7.2/libavcodec/alpha/me_cmp_mvi_asm.S 

OBJS += \
./include/ffmpeg-2.7.2/libavcodec/alpha/blockdsp_alpha.o \
./include/ffmpeg-2.7.2/libavcodec/alpha/hpeldsp_alpha.o \
./include/ffmpeg-2.7.2/libavcodec/alpha/hpeldsp_alpha_asm.o \
./include/ffmpeg-2.7.2/libavcodec/alpha/idctdsp_alpha.o \
./include/ffmpeg-2.7.2/libavcodec/alpha/idctdsp_alpha_asm.o \
./include/ffmpeg-2.7.2/libavcodec/alpha/me_cmp_alpha.o \
./include/ffmpeg-2.7.2/libavcodec/alpha/me_cmp_mvi_asm.o \
./include/ffmpeg-2.7.2/libavcodec/alpha/mpegvideo_alpha.o \
./include/ffmpeg-2.7.2/libavcodec/alpha/pixblockdsp_alpha.o \
./include/ffmpeg-2.7.2/libavcodec/alpha/simple_idct_alpha.o 

C_DEPS += \
./include/ffmpeg-2.7.2/libavcodec/alpha/blockdsp_alpha.d \
./include/ffmpeg-2.7.2/libavcodec/alpha/hpeldsp_alpha.d \
./include/ffmpeg-2.7.2/libavcodec/alpha/idctdsp_alpha.d \
./include/ffmpeg-2.7.2/libavcodec/alpha/me_cmp_alpha.d \
./include/ffmpeg-2.7.2/libavcodec/alpha/mpegvideo_alpha.d \
./include/ffmpeg-2.7.2/libavcodec/alpha/pixblockdsp_alpha.d \
./include/ffmpeg-2.7.2/libavcodec/alpha/simple_idct_alpha.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg-2.7.2/libavcodec/alpha/%.o: ../include/ffmpeg-2.7.2/libavcodec/alpha/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/ffmpeg-2.7.2/libavcodec/alpha/%.o: ../include/ffmpeg-2.7.2/libavcodec/alpha/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


