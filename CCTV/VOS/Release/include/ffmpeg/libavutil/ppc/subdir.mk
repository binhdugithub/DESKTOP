################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/libavutil/ppc/cpu.c \
../include/ffmpeg/libavutil/ppc/float_dsp_altivec.c \
../include/ffmpeg/libavutil/ppc/float_dsp_init.c 

OBJS += \
./include/ffmpeg/libavutil/ppc/cpu.o \
./include/ffmpeg/libavutil/ppc/float_dsp_altivec.o \
./include/ffmpeg/libavutil/ppc/float_dsp_init.o 

C_DEPS += \
./include/ffmpeg/libavutil/ppc/cpu.d \
./include/ffmpeg/libavutil/ppc/float_dsp_altivec.d \
./include/ffmpeg/libavutil/ppc/float_dsp_init.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/libavutil/ppc/%.o: ../include/ffmpeg/libavutil/ppc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


