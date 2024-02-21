################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drivers/nrf24l01/src/nrf24.cpp 

OBJS += \
./Drivers/nrf24l01/src/nrf24.o 

CPP_DEPS += \
./Drivers/nrf24l01/src/nrf24.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/nrf24l01/src/%.o Drivers/nrf24l01/src/%.su Drivers/nrf24l01/src/%.cyclo: ../Drivers/nrf24l01/src/%.cpp Drivers/nrf24l01/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/nrf24l01" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/w25qxx" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/SharedCode" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/ArduinoBackport" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/SBUS" -I"L:/Projects/ArduinoProjects/Arduino_RX_TX/STM32IDEWorkSpace/RC_RX_F4/Drivers/nrf24l01/src" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-nrf24l01-2f-src

clean-Drivers-2f-nrf24l01-2f-src:
	-$(RM) ./Drivers/nrf24l01/src/nrf24.cyclo ./Drivers/nrf24l01/src/nrf24.d ./Drivers/nrf24l01/src/nrf24.o ./Drivers/nrf24l01/src/nrf24.su

.PHONY: clean-Drivers-2f-nrf24l01-2f-src

