/*
 Name:		ADCDMATestHAL.ino
 Created:	12/30/2021 3:20:27 PM
 Author:	Senna
*/

#include "ADCDMAFunctions.h"
#include <ArduinoTimer.h>
ArduinoTimer printADCDataTimer;
//
//ADC_HandleTypeDef hadc1;
//DMA_HandleTypeDef hdma_adc1;
//
//
//void MX_ADC1_Init(void)
//{
//    hadc1.Instance = ADC1;
//    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
//    hadc1.Init.Resolution = ADC_RESOLUTION_10B;
//    hadc1.Init.ScanConvMode = ENABLE;
//    hadc1.Init.ContinuousConvMode = ENABLE;
//    hadc1.Init.DiscontinuousConvMode = DISABLE;
//    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
//    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
//    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
//    hadc1.Init.NbrOfConversion = 15;
//    hadc1.Init.DMAContinuousRequests = ENABLE;
//    hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
//
//    if (HAL_ADC_Init(&hadc1) != HAL_OK)
//    {
//        Error_Handler();
//    }
//
//    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
//    //if (hadc->Instance == ADC1)
//    //{
//        /* USER CODE BEGIN ADC1_MspInit 0 */
//
//        /* USER CODE END ADC1_MspInit 0 */
//          /* Peripheral clock enable */
//        __HAL_RCC_ADC1_CLK_ENABLE();
//
//        __HAL_RCC_GPIOC_CLK_ENABLE();
//        __HAL_RCC_GPIOA_CLK_ENABLE();
//        __HAL_RCC_GPIOB_CLK_ENABLE();
//        /**ADC1 GPIO Configuration
//        PC0     ------> ADC1_IN10
//        PC1     ------> ADC1_IN11
//        PC2     ------> ADC1_IN12
//        PC3     ------> ADC1_IN13
//        PA1     ------> ADC1_IN1
//        PA2     ------> ADC1_IN2
//        PA3     ------> ADC1_IN3
//        PA4     ------> ADC1_IN4
//        PA5     ------> ADC1_IN5
//        PA6     ------> ADC1_IN6
//        PA7     ------> ADC1_IN7
//        PC4     ------> ADC1_IN14
//        PC5     ------> ADC1_IN15
//        PB0     ------> ADC1_IN8
//        PB1     ------> ADC1_IN9
//        */
//        GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3
//            | GPIO_PIN_4 | GPIO_PIN_5;
//        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//        GPIO_InitStruct.Pull = GPIO_NOPULL;
//        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
//
//        GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4
//            | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
//        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//        GPIO_InitStruct.Pull = GPIO_NOPULL;
//        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//        GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
//        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//        GPIO_InitStruct.Pull = GPIO_NOPULL;
//        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//
//        /* ADC1 DMA Init */
//        /* ADC1 Init */
//        hdma_adc1.Instance = DMA2_Stream0;
//        hdma_adc1.Init.Channel = DMA_CHANNEL_0;
//        hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
//        hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
//        hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
//        hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
//        hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
//        hdma_adc1.Init.Mode = DMA_CIRCULAR;
//        hdma_adc1.Init.Priority = DMA_PRIORITY_LOW;
//        hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
//        if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
//        {
//            Error_Handler();
//        }
//
//        __HAL_LINKDMA(&hadc1, DMA_Handle, hdma_adc1);
//
//        /* ADC1 interrupt Init */
//        HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
//        HAL_NVIC_EnableIRQ(ADC_IRQn);
//        /* USER CODE BEGIN ADC1_MspInit 1 */
//
//        /* USER CODE END ADC1_MspInit 1 */
//    //}
//
//    ADC_ChannelConfTypeDef sConfig = { 0 };
//
//    sConfig.Channel = ADC_CHANNEL_1;
//    sConfig.Rank = 1;
//    sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;
//    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//    {
//        Error_Handler();
//    }
//
//    sConfig.Channel = ADC_CHANNEL_2;
//    sConfig.Rank = 2;
//    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//    {
//        Error_Handler();
//    }
//
//    sConfig.Channel = ADC_CHANNEL_3;
//    sConfig.Rank = 3;
//    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//    {
//        Error_Handler();
//    }
//
//    sConfig.Channel = ADC_CHANNEL_4;
//    sConfig.Rank = 4;
//    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//    {
//        Error_Handler();
//    }
//
//    sConfig.Channel = ADC_CHANNEL_5;
//    sConfig.Rank = 5;
//    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//    {
//        Error_Handler();
//    }
//
//    sConfig.Channel = ADC_CHANNEL_6;
//    sConfig.Rank = 6;
//    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//    {
//        Error_Handler();
//    }
//
//    sConfig.Channel = ADC_CHANNEL_10;
//    sConfig.Rank = 7;
//    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//    {
//        Error_Handler();
//    }
//
//    sConfig.Channel = ADC_CHANNEL_11;
//    sConfig.Rank = 8;
//    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//    {
//        Error_Handler();
//    }
//
//    sConfig.Channel = ADC_CHANNEL_12;
//    sConfig.Rank = 9;
//    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//    {
//        Error_Handler();
//    }
//
//    sConfig.Channel = ADC_CHANNEL_13;
//    sConfig.Rank = 10;
//    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//    {
//        Error_Handler();
//    }
//
//    sConfig.Channel = ADC_CHANNEL_7;
//    sConfig.Rank = 11;
//    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//    {
//        Error_Handler();
//    }
//
//    sConfig.Channel = ADC_CHANNEL_14;
//    sConfig.Rank = 12;
//    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//    {
//        Error_Handler();
//    }
//
//    sConfig.Channel = ADC_CHANNEL_15;
//    sConfig.Rank = 13;
//    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//    {
//        Error_Handler();
//    }
//
//    sConfig.Channel = ADC_CHANNEL_8;
//    sConfig.Rank = 14;
//    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//    {
//        Error_Handler();
//    }
//
//    sConfig.Channel = ADC_CHANNEL_9;
//    sConfig.Rank = 15;
//    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//    {
//        Error_Handler();
//    }
//
//}
//
//void MX_DMA_Init(void)
//{
//
//    /* DMA controller clock enable */
//    __HAL_RCC_DMA2_CLK_ENABLE();
//
//    /* DMA interrupt init */
//    /* DMA2_Stream0_IRQn interrupt configuration */
//    HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
//    HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
//
//
//
//}
//
//uint16_t dmaBuffer[15];
//
//void start_adc() {
//    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)dmaBuffer, 15);
//}

extern "C" void _Error_Handler(const char* file, int line) {
    Serial.printf("Error in file '%s' at line '%d'\n", file, line);
    delay(100);
    HAL_NVIC_SystemReset();
}

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(115200);
    delay(100);
    Serial.println("Starting ADCDMAHal Test");
    ADCInit();
    ADCStart();
    delay(100);
    Serial.println("Started ADCDMAHal Test");
}
//
//extern "C" void ADC_IRQHandler(void)
//{
//    HAL_ADC_IRQHandler(&hadc1);
//}
//
//extern "C" void DMA2_Stream0_IRQHandler(void)
//{
//    HAL_DMA_IRQHandler(&hdma_adc1);
//}

// the loop function runs over and over again until power down or reset=
void loop() {
  if(Serial.available()){
      char c = Serial.read();
      if (c == '*') {
          NVIC_SystemReset();
      }
  }
  if (printADCDataTimer.TimePassed_Milliseconds(500)) {
      Serial.print("ADCData: ");
      for (const auto val : ADCDMABuffer) {
          Serial.printf("%04d ", val);
      }
      Serial.println();
  }
}
