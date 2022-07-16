################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Queue/src/queue.c 

OBJS += \
./Queue/src/queue.o 

C_DEPS += \
./Queue/src/queue.d 


# Each subdirectory must supply rules for building sources it contributes
Queue/src/%.o Queue/src/%.su: ../Queue/src/%.c Queue/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"C:/Users/maith/Desktop/htn/SPI_Send/SPI_407_Receive/LCD_Lib/Inc" -I"C:/Users/maith/Desktop/htn/SPI_Send/SPI_407_Receive/string_handling/inc" -I"C:/Users/maith/Desktop/htn/SPI_Send/SPI_407_Receive/Queue/inc" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Queue-2f-src

clean-Queue-2f-src:
	-$(RM) ./Queue/src/queue.d ./Queue/src/queue.o ./Queue/src/queue.su

.PHONY: clean-Queue-2f-src

