################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/DFU/Src/usbd_dfu.c 

C_DEPS += \
./Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/DFU/Src/usbd_dfu.d 

OBJS += \
./Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/DFU/Src/usbd_dfu.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/DFU/Src/%.o Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/DFU/Src/%.su: ../Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/DFU/Src/%.c Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/DFU/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/nrf24l01" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/w25qxx" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/SharedCode" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/ArduinoBackport" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/SBUS" -I../Composite -IC:/Users/Senna/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/Senna/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/Senna/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/Senna/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Include -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Class/MSC/Inc -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/App -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Class/COMPOSITE/Inc -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Class/HID_CUSTOM/Inc -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Core/Inc -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Target -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Class/DFU/Inc -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Class/CDC_ACM/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-AL94_USB_Composite-2f-COMPOSITE-2f-Class-2f-DFU-2f-Src

clean-Middlewares-2f-Third_Party-2f-AL94_USB_Composite-2f-COMPOSITE-2f-Class-2f-DFU-2f-Src:
	-$(RM) ./Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/DFU/Src/usbd_dfu.d ./Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/DFU/Src/usbd_dfu.o ./Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/DFU/Src/usbd_dfu.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-AL94_USB_Composite-2f-COMPOSITE-2f-Class-2f-DFU-2f-Src

