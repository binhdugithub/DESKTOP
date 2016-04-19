################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/tests/audiogen.c \
../include/ffmpeg/tests/base64.c \
../include/ffmpeg/tests/rotozoom.c \
../include/ffmpeg/tests/tiny_psnr.c \
../include/ffmpeg/tests/tiny_ssim.c \
../include/ffmpeg/tests/utils.c \
../include/ffmpeg/tests/videogen.c 

OBJS += \
./include/ffmpeg/tests/audiogen.o \
./include/ffmpeg/tests/base64.o \
./include/ffmpeg/tests/rotozoom.o \
./include/ffmpeg/tests/tiny_psnr.o \
./include/ffmpeg/tests/tiny_ssim.o \
./include/ffmpeg/tests/utils.o \
./include/ffmpeg/tests/videogen.o 

C_DEPS += \
./include/ffmpeg/tests/audiogen.d \
./include/ffmpeg/tests/base64.d \
./include/ffmpeg/tests/rotozoom.d \
./include/ffmpeg/tests/tiny_psnr.d \
./include/ffmpeg/tests/tiny_ssim.d \
./include/ffmpeg/tests/utils.d \
./include/ffmpeg/tests/videogen.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/tests/%.o: ../include/ffmpeg/tests/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


