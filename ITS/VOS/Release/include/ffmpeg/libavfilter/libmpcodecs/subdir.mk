################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/libavfilter/libmpcodecs/img_format.c \
../include/ffmpeg/libavfilter/libmpcodecs/mp_image.c \
../include/ffmpeg/libavfilter/libmpcodecs/vf_eq.c \
../include/ffmpeg/libavfilter/libmpcodecs/vf_eq2.c \
../include/ffmpeg/libavfilter/libmpcodecs/vf_fspp.c \
../include/ffmpeg/libavfilter/libmpcodecs/vf_ilpack.c \
../include/ffmpeg/libavfilter/libmpcodecs/vf_pp7.c \
../include/ffmpeg/libavfilter/libmpcodecs/vf_softpulldown.c \
../include/ffmpeg/libavfilter/libmpcodecs/vf_uspp.c 

OBJS += \
./include/ffmpeg/libavfilter/libmpcodecs/img_format.o \
./include/ffmpeg/libavfilter/libmpcodecs/mp_image.o \
./include/ffmpeg/libavfilter/libmpcodecs/vf_eq.o \
./include/ffmpeg/libavfilter/libmpcodecs/vf_eq2.o \
./include/ffmpeg/libavfilter/libmpcodecs/vf_fspp.o \
./include/ffmpeg/libavfilter/libmpcodecs/vf_ilpack.o \
./include/ffmpeg/libavfilter/libmpcodecs/vf_pp7.o \
./include/ffmpeg/libavfilter/libmpcodecs/vf_softpulldown.o \
./include/ffmpeg/libavfilter/libmpcodecs/vf_uspp.o 

C_DEPS += \
./include/ffmpeg/libavfilter/libmpcodecs/img_format.d \
./include/ffmpeg/libavfilter/libmpcodecs/mp_image.d \
./include/ffmpeg/libavfilter/libmpcodecs/vf_eq.d \
./include/ffmpeg/libavfilter/libmpcodecs/vf_eq2.d \
./include/ffmpeg/libavfilter/libmpcodecs/vf_fspp.d \
./include/ffmpeg/libavfilter/libmpcodecs/vf_ilpack.d \
./include/ffmpeg/libavfilter/libmpcodecs/vf_pp7.d \
./include/ffmpeg/libavfilter/libmpcodecs/vf_softpulldown.d \
./include/ffmpeg/libavfilter/libmpcodecs/vf_uspp.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/libavfilter/libmpcodecs/%.o: ../include/ffmpeg/libavfilter/libmpcodecs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


