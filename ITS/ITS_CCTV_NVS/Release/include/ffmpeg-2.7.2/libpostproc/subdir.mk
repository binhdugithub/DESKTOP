################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg-2.7.2/libpostproc/postprocess.c \
../include/ffmpeg-2.7.2/libpostproc/postprocess_altivec_template.c \
../include/ffmpeg-2.7.2/libpostproc/postprocess_template.c 

OBJS += \
./include/ffmpeg-2.7.2/libpostproc/postprocess.o \
./include/ffmpeg-2.7.2/libpostproc/postprocess_altivec_template.o \
./include/ffmpeg-2.7.2/libpostproc/postprocess_template.o 

C_DEPS += \
./include/ffmpeg-2.7.2/libpostproc/postprocess.d \
./include/ffmpeg-2.7.2/libpostproc/postprocess_altivec_template.d \
./include/ffmpeg-2.7.2/libpostproc/postprocess_template.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg-2.7.2/libpostproc/%.o: ../include/ffmpeg-2.7.2/libpostproc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


