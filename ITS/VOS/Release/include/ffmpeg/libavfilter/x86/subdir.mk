################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/ffmpeg/libavfilter/x86/af_volume_init.c \
../include/ffmpeg/libavfilter/x86/vf_gradfun_init.c \
../include/ffmpeg/libavfilter/x86/vf_hqdn3d_init.c \
../include/ffmpeg/libavfilter/x86/vf_pullup_init.c \
../include/ffmpeg/libavfilter/x86/vf_spp.c \
../include/ffmpeg/libavfilter/x86/vf_yadif_init.c 

ASM_SRCS += \
../include/ffmpeg/libavfilter/x86/af_volume.asm \
../include/ffmpeg/libavfilter/x86/vf_gradfun.asm \
../include/ffmpeg/libavfilter/x86/vf_hqdn3d.asm \
../include/ffmpeg/libavfilter/x86/vf_pullup.asm \
../include/ffmpeg/libavfilter/x86/vf_yadif.asm \
../include/ffmpeg/libavfilter/x86/yadif-10.asm \
../include/ffmpeg/libavfilter/x86/yadif-16.asm 

OBJS += \
./include/ffmpeg/libavfilter/x86/af_volume.o \
./include/ffmpeg/libavfilter/x86/af_volume_init.o \
./include/ffmpeg/libavfilter/x86/vf_gradfun.o \
./include/ffmpeg/libavfilter/x86/vf_gradfun_init.o \
./include/ffmpeg/libavfilter/x86/vf_hqdn3d.o \
./include/ffmpeg/libavfilter/x86/vf_hqdn3d_init.o \
./include/ffmpeg/libavfilter/x86/vf_pullup.o \
./include/ffmpeg/libavfilter/x86/vf_pullup_init.o \
./include/ffmpeg/libavfilter/x86/vf_spp.o \
./include/ffmpeg/libavfilter/x86/vf_yadif.o \
./include/ffmpeg/libavfilter/x86/vf_yadif_init.o \
./include/ffmpeg/libavfilter/x86/yadif-10.o \
./include/ffmpeg/libavfilter/x86/yadif-16.o 

C_DEPS += \
./include/ffmpeg/libavfilter/x86/af_volume_init.d \
./include/ffmpeg/libavfilter/x86/vf_gradfun_init.d \
./include/ffmpeg/libavfilter/x86/vf_hqdn3d_init.d \
./include/ffmpeg/libavfilter/x86/vf_pullup_init.d \
./include/ffmpeg/libavfilter/x86/vf_spp.d \
./include/ffmpeg/libavfilter/x86/vf_yadif_init.d 


# Each subdirectory must supply rules for building sources it contributes
include/ffmpeg/libavfilter/x86/%.o: ../include/ffmpeg/libavfilter/x86/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/ffmpeg/libavfilter/x86/%.o: ../include/ffmpeg/libavfilter/x86/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I./include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


