#include <unity.h>
#include "config.h"

#include <Wire.h>
#include <nrf24.hpp>

#include "MyHelpers.h"

#include "settingsStructs.h"



void setUp(void)
{
    Wire.setSCL(WIRE1_SCL);
    Wire.setSDA(WIRE1_SCL);
    Wire.begin();
    Wire.setClock(100000);
}

void tearDown(void)
{
    Wire.end();
}

void I2C_enc_detected(void)
{
    TEST_ASSERT(I2CDeviceConnected(&Wire, ENCODER_ADDR));
}

void I2C_MCP_Detected(void)
{
    TEST_ASSERT(I2CDeviceConnected(&Wire, 0x20 + IOEXPANDER1_ADDR));
    TEST_ASSERT(I2CDeviceConnected(&Wire, 0x20 + IOEXPANDER2_ADDR));
    TEST_ASSERT(I2CDeviceConnected(&Wire, 0x20 + CALEXPENDER_ADDR));
}

void I2C_EEPROM_Detected(void)
{
    TEST_ASSERT(I2CDeviceConnected(&Wire, 0x50));
}

#ifdef ARDUINO_ARCH_STM32
SPI_HandleTypeDef nRF_hspi;
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (hspi->Instance == SPI3)
    {
        /* USER CODE BEGIN SPI3_MspInit 0 */

        /* USER CODE END SPI3_MspInit 0 */
        /* Peripheral clock enable */
        __HAL_RCC_SPI3_CLK_ENABLE();

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**SPI3 GPIO Configuration
        PB3     ------> SPI3_SCK
        PB4     ------> SPI3_MISO
        PB5     ------> SPI3_MOSI
        */
        GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* USER CODE BEGIN SPI3_MspInit 1 */

        /* USER CODE END SPI3_MspInit 1 */
    }
}

void initSPI()
{
    nRF_hspi.Instance = SPI3;
    nRF_hspi.Init.Mode = SPI_MODE_MASTER;
    nRF_hspi.Init.Direction = SPI_DIRECTION_2LINES;
    nRF_hspi.Init.DataSize = SPI_DATASIZE_8BIT;
    nRF_hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
    nRF_hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
    nRF_hspi.Init.NSS = SPI_NSS_SOFT;
    nRF_hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
    nRF_hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    nRF_hspi.Init.TIMode = SPI_TIMODE_DISABLE;
    nRF_hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    nRF_hspi.Init.CRCPolynomial = 10;
    if (HAL_SPI_Init(&nRF_hspi) != HAL_OK)
    {
        Error_Handler();
    }
    __HAL_SPI_ENABLE(&nRF_hspi);
}
#else
void initSPI() {}
#endif

void NRF_Detected(void)
{
    initSPI();
    nRF24_CE_L();
    delay(5);
    TEST_ASSERT(nRF24_Check());
}

int runUnityTests(void)
{
    UNITY_BEGIN();

    RUN_TEST(I2C_enc_detected);
    RUN_TEST(I2C_MCP_Detected);
    RUN_TEST(I2C_EEPROM_Detected);
    RUN_TEST(NRF_Detected);
    return UNITY_END();
}

/**
  * For Arduino framework
  */
void setup()
{
    // Wait ~2 seconds before the Unity test runner
    // establishes connection with a board Serial interface
    delay(2000);

    runUnityTests();
}
void loop() {}
