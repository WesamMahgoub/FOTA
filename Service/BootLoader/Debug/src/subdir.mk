################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BL.c \
../src/Dma.c \
../src/Gpio.c \
../src/NVIC.c \
../src/Rcc.c \
../src/Uart.c \
../src/UsartHal.c \
../src/UsartHal_cfg.c \
../src/main.c 

OBJS += \
./src/BL.o \
./src/Dma.o \
./src/Gpio.o \
./src/NVIC.o \
./src/Rcc.o \
./src/Uart.o \
./src/UsartHal.o \
./src/UsartHal_cfg.o \
./src/main.o 

C_DEPS += \
./src/BL.d \
./src/Dma.d \
./src/Gpio.d \
./src/NVIC.d \
./src/Rcc.d \
./src/Uart.d \
./src/UsartHal.d \
./src/UsartHal_cfg.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F401xC -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -Wmissing-prototypes -Wstrict-prototypes -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


