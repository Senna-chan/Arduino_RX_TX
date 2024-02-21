################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Senna/STM32Cube/Repository/Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Class/DFU/Src/usbd_dfu.c \
C:/Users/Senna/STM32Cube/Repository/Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/App/usbd_dfu_if.c 

C_DEPS += \
./Middlewares/Composite/USB/COMPOSITE/DFU/usbd_dfu.d \
./Middlewares/Composite/USB/COMPOSITE/DFU/usbd_dfu_if.d 

OBJS += \
./Middlewares/Composite/USB/COMPOSITE/DFU/usbd_dfu.o \
./Middlewares/Composite/USB/COMPOSITE/DFU/usbd_dfu_if.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Composite/USB/COMPOSITE/DFU/usbd_dfu.o: C:/Users/Senna/STM32Cube/Repository/Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Class/DFU/Src/usbd_dfu.c Middlewares/Composite/USB/COMPOSITE/DFU/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/nrf24l01" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/w25qxx" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/SharedCode" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/ArduinoBackport" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/SBUS" -I../Composite -IC:/Users/Senna/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/Senna/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/Senna/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/Senna/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Include -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Class/MSC/Inc -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/App -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Class/COMPOSITE/Inc -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Class/HID_CUSTOM/Inc -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Core/Inc -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Target -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Class/DFU/Inc -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Class/CDC_ACM/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Composite/USB/COMPOSITE/DFU/usbd_dfu_if.o: C:/Users/Senna/STM32Cube/Repository/Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/App/usbd_dfu_if.c Middlewares/Composite/USB/COMPOSITE/DFU/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/nrf24l01" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/w25qxx" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/SharedCode" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/ArduinoBackport" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/SBUS" -I../Composite -IC:/Users/Senna/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/Senna/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/Senna/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/Senna/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Include -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Class/MSC/Inc -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/App -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Class/COMPOSITE/Inc -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Class/HID_CUSTOM/Inc -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Core/Inc -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Target -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Class/DFU/Inc -IC:/Users/Senna/STM32Cube/Repository//Packs/AL94/I-CUBE-USBD-COMPOSITE/1.0.3/Middlewares/Third_Party/COMPOSITE/Class/CDC_ACM/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Composite-2f-USB-2f-COMPOSITE-2f-DFU

clean-Middlewares-2f-Composite-2f-USB-2f-COMPOSITE-2f-DFU:
	-$(RM) ./Middlewares/Composite/USB/COMPOSITE/DFU/usbd_dfu.d ./Middlewares/Composite/USB/COMPOSITE/DFU/usbd_dfu.o ./Middlewares/Composite/USB/COMPOSITE/DFU/usbd_dfu.su ./Middlewares/Composite/USB/COMPOSITE/DFU/usbd_dfu_if.d ./Middlewares/Composite/USB/COMPOSITE/DFU/usbd_dfu_if.o ./Middlewares/Composite/USB/COMPOSITE/DFU/usbd_dfu_if.su

.PHONY: clean-Middlewares-2f-Composite-2f-USB-2f-COMPOSITE-2f-DFU

