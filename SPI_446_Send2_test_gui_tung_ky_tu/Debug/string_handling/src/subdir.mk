################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../string_handling/src/string_handling.c 

OBJS += \
./string_handling/src/string_handling.o 

C_DEPS += \
./string_handling/src/string_handling.d 


# Each subdirectory must supply rules for building sources it contributes
string_handling/src/%.o string_handling/src/%.su: ../string_handling/src/%.c string_handling/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"C:/Users/maith/Desktop/htn/SPI_Send/SPI_446_Send2_test_gui_tung_ky_tu/string_handling/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-string_handling-2f-src

clean-string_handling-2f-src:
	-$(RM) ./string_handling/src/string_handling.d ./string_handling/src/string_handling.o ./string_handling/src/string_handling.su

.PHONY: clean-string_handling-2f-src

