//
// Created by senyaa on 4/20/25.
//

#include "../../Core/Inc/main.h"
#include "../../Core/Inc/usart.h"
#include "../include/Arduino_TX_HAL.h"
#include <../../../lib/HardwareSerial/HardwareSerial.h>
#include <unity.h>

void setUp(void)
{
    MX_USART1_UART_Init();
    Serial1.create(&huart1);
    Serial1.init();
}

void tearDown(void)
{

}

void test_print_string(void){
    Serial1.println("Hello World!");
}

int main()
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay
    TEST_PRINTF("Starting test");
    UNITY_BEGIN();
    RUN_TEST(test_print_string);

    UNITY_END(); // stop unit testing

    while (1)
    {
    }
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}