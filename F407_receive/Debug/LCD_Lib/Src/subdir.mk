################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LCD_Lib/Src/i2c_lcd.c 

OBJS += \
./LCD_Lib/Src/i2c_lcd.o 

C_DEPS += \
./LCD_Lib/Src/i2c_lcd.d 


# Each subdirectory must supply rules for building sources it contributes
LCD_Lib/Src/%.o LCD_Lib/Src/%.su: ../LCD_Lib/Src/%.c LCD_Lib/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"C:/Users/maith/Desktop/htn/SPI_Send/F407_receive/LCD_Lib/Inc" -I"C:/Users/maith/Desktop/htn/SPI_Send/F407_receive/Queue/inc" -I"C:/Users/maith/Desktop/htn/SPI_Send/F407_receive/string_handling/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-LCD_Lib-2f-Src

clean-LCD_Lib-2f-Src:
	-$(RM) ./LCD_Lib/Src/i2c_lcd.d ./LCD_Lib/Src/i2c_lcd.o ./LCD_Lib/Src/i2c_lcd.su

.PHONY: clean-LCD_Lib-2f-Src

