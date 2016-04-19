################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/libpostproc/postprocess.c \
../include/ffmpeg/libpostproc/postprocess_altivec_template.c \
../include/ffmpeg/libpostproc/postprocess_template.c 

OBJS += \
./include/ffmpeg/libpostproc/postprocess.o \
./include/ffmpeg/libpostproc/postprocess_altivec_template.o \
./include/ffmpeg/libpostproc/postprocess_template.o 

C_DEPS += \
./include/ffmpeg/libpostproc/postprocess.d \
./include/ffmpeg/libpostproc/postprocess_altivec_template.d \
./include/ffmpeg/libpostproc/postprocess_template.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/libpostproc/%.o: ../include/ffmpeg/libpostproc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


