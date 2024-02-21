################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/nrf24l01/nrf24.c 

C_DEPS += \
./Drivers/nrf24l01/nrf24.d 

OBJS += \
./Drivers/nrf24l01/nrf24.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/nrf24l01/%.o Drivers/nrf24l01/%.su: ../Drivers/nrf24l01/%.c Drivers/nrf24l01/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/nrf24l01" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/w25qxx" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/SharedCode" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/ArduinoBackport" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/SBUS" -I../Composite -I../Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/MSC/Inc -I../Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/App -I../Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/COMPOSITE/Inc -I../Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/HID_CUSTOM/Inc -I../Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Core/Inc -I../Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Target -I../Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/DFU/Inc -I../Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/CDC_ACM/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-nrf24l01

clean-Drivers-2f-nrf24l01:
	-$(RM) ./Drivers/nrf24l01/nrf24.d ./Drivers/nrf24l01/nrf24.o ./Drivers/nrf24l01/nrf24.su

.PHONY: clean-Drivers-2f-nrf24l01

