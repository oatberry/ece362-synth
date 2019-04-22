################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/input.c \
../src/main.c \
../src/synth.c \
../src/syscalls.c \
../src/system_stm32f0xx.c \
../src/wave.c 

OBJS += \
./src/input.o \
./src/main.o \
./src/synth.o \
./src/syscalls.o \
./src/system_stm32f0xx.o \
./src/wave.o 

C_DEPS += \
./src/input.d \
./src/main.d \
./src/synth.d \
./src/syscalls.d \
./src/system_stm32f0xx.d \
./src/wave.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F0 -DSTM32F051R8Tx -DSTM32F0DISCOVERY -DDEBUG -DSTM32F051 -DUSE_STDPERIPH_DRIVER -I"/home/oats/school/ece362/sw4stm32/project/Utilities" -I"/home/oats/school/ece362/sw4stm32/project/StdPeriph_Driver/inc" -I"/home/oats/school/ece362/sw4stm32/project/inc" -I"/home/oats/school/ece362/sw4stm32/project/CMSIS/device" -I"/home/oats/school/ece362/sw4stm32/project/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


