/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dac.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "nrf24.h"
#include "w25qxx.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
channelOutputConfig channelsOutputConfig[25];
uint8_t nrfAddress[] = { 0x33, 0x22, 0x11 };
uint8_t nRFDataReady = 0;
uint8_t gotData = 0;
uint32_t txfailratio[2];

uint16_t channelValues[24];


transmitTypes transmitData;
receiveTypes receiveData;
Settings settings = {0};
Model activeSettings;

Settings receivedSettings = {0};

uint8_t readingSettings = 0; ///< Used to show that we are going to read the settings from the transmitter
uint8_t readingSettingsPacketAmount = 0; ///< This is how much 30 u8 packets we are going to get
uint8_t readingSettingsPacketAmountRest = 0; ///< This is how much bytes are left after 30 packets

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int _read(int file, char *ptr, int len) {
    HAL_StatusTypeDef hstatus;
    hstatus = HAL_UART_Receive(&huart1, (uint8_t*) ptr, 1, HAL_MAX_DELAY);
    if (hstatus == HAL_OK)
        return 1;
    else
        return 0;
}

int _write(int file, char *ptr, int len) {
    HAL_StatusTypeDef hstatus;
    hstatus = HAL_UART_Transmit(&huart1, (uint8_t*) ptr, len, HAL_MAX_DELAY);
    if (hstatus == HAL_OK)
        return len;
    else
        return 0;
}

void __io_putchar(uint8_t ch) {
	HAL_UART_Transmit(&huart1, &ch, 1, 1);
}

void setStatusLed(uint8_t R, uint8_t G, uint8_t B){
	HAL_GPIO_WritePin(SLEDR_GPIO_Port, SLEDR_Pin, (R ? GPIO_PIN_SET : GPIO_PIN_RESET));
	HAL_GPIO_WritePin(SLEDG_GPIO_Port, SLEDG_Pin, (G ? GPIO_PIN_SET : GPIO_PIN_RESET));
	HAL_GPIO_WritePin(SLEDB_GPIO_Port, SLEDB_Pin, (B ? GPIO_PIN_SET : GPIO_PIN_RESET));
}



void common_nRFInit() {
	nRF24_CE_L();
	delay(20);
	if (!nRF24_Check()) {
		UART_SendStr("NRF Module not found");
		Error_Handler();
	}

	nRF24_Init();

	// Set RF channel
	nRF24_SetRFChannel(40);

	// Set data rate
	nRF24_SetDataRate(nRF24_DR_1Mbps);

	// Set CRC scheme
	nRF24_SetCRCScheme(nRF24_CRC_2byte);

	// Set address width, its common for all pipes (RX and TX)
	nRF24_SetAddrWidth(3);

	// Configure RX PIPE
	if (!isTransmitter) {
		nRF24_SetAddr(nRF24_PIPE0, nrfAddress); 	// Set RX Pipe
	}
	else {
		nRF24_SetAddr(nRF24_PIPE0, nrfAddress); 	// Set RX Pipe
		nRF24_SetAddr(nRF24_PIPETX, nrfAddress);   // Set TX Pipe
		nRF24_SetAutoRetr(nRF24_ARD_250us, 10);
	}
	nRF24_SetRXPipe(nRF24_PIPE0, nRF24_AA_ON, 32); // Auto-ACK: enabled, payload length: 32 bytes

	// Set TX power
	nRF24_SetTXPower(nRF24_TXPWR_0dBm);

	// Enable DPL
	nRF24_SetDynamicPayloadLength(nRF24_DPL_ON);

	nRF24_SetPayloadWithAck(1);


	// Enable Auto-ACK for pipe#0 (for ACK packets)
	nRF24_EnableAA(nRF24_PIPE0);

	if (!isTransmitter) {
		// Set operational mode (PRX == receiver)
		nRF24_SetOperationalMode(nRF24_MODE_RX);
	}
	else {
		nRF24_SetAutoRetr(nRF24_ARD_250us, 3);

		nRF24_SetOperationalMode(nRF24_MODE_TX);
	}
	// Clear any pending IRQ flags
	nRF24_ClearIRQFlags();

	// Wake the transceiver
	nRF24_SetPowerMode(nRF24_PWR_UP);


	//nRF24_DumpConfig();
	if (!isTransmitter) {
		// Put the transceiver to the RX mode
		nRF24_CE_H();
	}
}

void UART_SendChar(char b) {
    HAL_UART_Transmit(&huart1, (uint8_t *) &b, 1, 200);
}

void UART_SendStr(char *string) {
    HAL_UART_Transmit(&huart1, (uint8_t *) string, (uint16_t) strlen(string), 200);
}

void setOutput(uint8_t index, uint16_t channelValue){
	channelOutputConfig choc = channelsOutputConfig[index];
	channelValue += 1000;
	channelValues[index-1] = channelValue;
	if(channelValue == 2001) {
		channelValues[index-1] = 0;
		return;
	}

	if(choc.outputMode == OUTPUTMODE_RC){
		if(choc.timOutput == 0)
			return;

		*choc.timOutput = channelValue;
	} else if(choc.outputMode == OUTPUTMODE_IO){
		if(channelValue > 1500){
			*choc.timOutput = 7000; // Max output
		} else{
			*choc.timOutput = 0;
		}
	}
}
uint32_t receivedSettingsPacket;
void parseRFPacket(uint8_t* buf, uint8_t length,nRF24_RXResult pipeLine){
	if(pipeLine == nRF24_RX_EMPTY){
		printf("Pipeline is empty");
		return;
	}
	if(length == 6){
		for (int i = 0; i < length; i++) {
			printf(" %02d ", buf[i]);
		}
		UART_SendChar('\n');
	} else {
		memmove(transmitData.bytesUnion.u8, buf, 32);
		uint8_t packetId = transmitData.bytesUnion.u8[0] & 0b1111;
		switch(packetId){
			case CHANNELDATAID:
				HAL_GPIO_TogglePin(IO_DBG_1_GPIO_Port, IO_DBG_1_Pin);
				setOutput(1 ,transmitData.ch_data.channel1 );
				setOutput(2 ,transmitData.ch_data.channel2 );
				setOutput(3 ,transmitData.ch_data.channel3 );
				setOutput(4 ,transmitData.ch_data.channel4 );
				setOutput(5 ,transmitData.ch_data.channel5 );
				setOutput(6 ,transmitData.ch_data.channel6 );
				setOutput(7 ,transmitData.ch_data.channel7 );
				setOutput(8 ,transmitData.ch_data.channel8 );
				setOutput(9 ,transmitData.ch_data.channel9 );
				setOutput(10,transmitData.ch_data.channel10);
				setOutput(11,transmitData.ch_data.channel11);
				setOutput(12,transmitData.ch_data.channel12);
				setOutput(13,transmitData.ch_data.channel13);
				setOutput(14,transmitData.ch_data.channel14);
				setOutput(15,transmitData.ch_data.channel15);
				setOutput(16,transmitData.ch_data.channel16);
				setOutput(17,transmitData.ch_data.channel17);
				setOutput(18,transmitData.ch_data.channel18);
				setOutput(19,transmitData.ch_data.channel19);
				setOutput(20,transmitData.ch_data.channel20);
				setOutput(21,transmitData.ch_data.channel21);
				setOutput(22,transmitData.ch_data.channel22);
				setOutput(23,transmitData.ch_data.channel23);
				setOutput(24,transmitData.ch_data.channel24);

		   		  uint32_t now = HAL_GetTick();
				  uint8_t txBuf[6];
				  txBuf[0] = 0;
				  txBuf[1] = 0;
				  txBuf[2] = now >> 24 & 0xFF;
				  txBuf[3] = now >> 16 & 0xFF;
				  txBuf[4] = now >> 8 & 0xFF;
				  txBuf[5] = now >> 0 & 0xFF;
				  nRF24_WriteAckPayload(pipeLine, txBuf,6);
				break;
			case SETTINGSDATASETUPID:
				HAL_GPIO_TogglePin(IO_DBG_2_GPIO_Port, IO_DBG_2_Pin);
				readingSettings = 1;
				readingSettingsPacketAmount = transmitData.bytesUnion.u8[1];
				readingSettingsPacketAmountRest = transmitData.bytesUnion.u8[2];
				memset(&receivedSettings, 0, sizeof(Settings));
				printf("PS %d MOD %d\r\n", readingSettingsPacketAmount, readingSettingsPacketAmountRest);
				memset(receiveData.bytesUnion.u8, 0xFF, 32);
				receiveData.bytesUnion.u8[0] = SETTINGSDATAID;
				nRF24_WriteAckPayload(pipeLine, receiveData.bytesUnion.u8, 32);
				break;
			case SETTINGSDATAID:
				HAL_GPIO_TogglePin(IO_DBG_2_GPIO_Port, IO_DBG_2_Pin);
				if(readingSettings == 0){
					printf("SETTINGS SETUP NOT DONE");
				} else {
					receivedSettingsPacket = transmitData.bytesUnion.u8[1];
					uint32_t receivedSettingsPtr = &receivedSettings;

					if(receivedSettingsPacket == readingSettingsPacketAmount){
						if(readingSettingsPacketAmountRest != 0){
							printf("SMOD");
							receivedSettingsPtr += ((receivedSettingsPacket - 1) * 30) + readingSettingsPacketAmountRest;

							memcpy(receivedSettingsPtr, &transmitData.bytesUnion.u8 + 2, readingSettingsPacketAmountRest);
						}
					}
					else if(receivedSettingsPacket == readingSettingsPacketAmount + 1){
						printf("TXSETCOMP");
						memcpy(&settings, &receivedSettings, sizeof(settings));
						readingSettings = 0;
						memset(receiveData.bytesUnion.u8, 0xFF, 32);
						return;
					} else if(receivedSettingsPacket < readingSettingsPacketAmount){
						printf("%04d ", receivedSettingsPacket);
						receivedSettingsPtr += (receivedSettingsPacket * 30);
						memmove(receivedSettingsPtr, &transmitData.bytesUnion.u8 + 2, 30);
					} else{
						Error_Handler();
					}
				}
				memset(receiveData.bytesUnion.u8, 0xFF, 32);
				receiveData.bytesUnion.u8[0] = SETTINGSDATAID;
				nRF24_WriteAckPayload(pipeLine, receiveData.bytesUnion.u8, 32);
				break;
		}

	}
}


#pragma region UART
uint8_t customHeaderByte = 0xFA;
uint8_t customHeaderSize = 3;
uint8_t customFooterByte = 0xFB;
uint8_t customFooterSize = 2;
uint8_t customUartRXBuffer[255];
uint8_t customUartTXBuffer[255];
uint32_t lastChannelStreamTime = 0;
uint8_t customChannelStreaming = 0;
uint32_t customUartChannelTickRate = 0;
uint8_t dataBeginIndex = 3;
enum commands {
	CHANNELS,
	STREAM_CHANNELS
};

uint8_t calculateCRC(uint8_t* data, uint8_t length)
{
    uint8_t crc = 0xff;
    size_t i, j;
    for (i = 0; i < length; i++) {
        crc ^= data[i];
        for (j = 0; j < 8; j++) {
            if ((crc & 0x80) != 0)
                crc = (uint8_t)((crc << 1) ^ 0x31);
            else
                crc <<= 1;
        }
    }
    return crc;
}

void sendChannelData(){
	lastChannelStreamTime = HAL_GetTick();
	uint8_t idx = 0;
	uint8_t dataSize = 24*2;
	customUartTXBuffer[idx++] = customHeaderByte;
	customUartTXBuffer[idx++] = CHANNELS;
	customUartTXBuffer[idx++] = dataSize;
	memcpy(customUartTXBuffer + idx, channelValues,dataSize);
	idx += dataSize;
	customUartTXBuffer[idx++] = calculateCRC(customUartTXBuffer+ 3, dataSize);
	customUartTXBuffer[idx++] = customFooterByte;
	if(HAL_UART_Transmit_IT(&customUart, customUartTXBuffer, idx) != HAL_OK){
		printf("UARTBUSY\r\n");
	}
}

void customUartDataTransmitted(){
//	printf("CUSTOMTX\r\n");
}

void customUartReceived(){
//	printf("CUSTOMRX\r\n");
	uint8_t dataSize = customUartRXBuffer[2];
	uint8_t crc = customUartRXBuffer[2 + dataSize + 1];
	uint8_t footerByte = customUartRXBuffer[2 + dataSize + 2];
	if(footerByte != customFooterByte){
		HAL_UART_Receive_IT(&customUart, customUartRXBuffer + customHeaderSize, dataSize + customFooterSize);
		return;
	}
	switch(customUartRXBuffer[1]){
	case CHANNELS:
		printf("CHANNELS\r\n");
		sendChannelData();
		break;
	case STREAM_CHANNELS:
		printf("STREAM\r\n");
		customChannelStreaming = 1;
		customUartChannelTickRate = customUartRXBuffer[dataBeginIndex] << 8 | customUartRXBuffer[dataBeginIndex + 1];
		sendChannelData();
		break;
	}
   HAL_UART_Receive_IT(&customUart, customUartRXBuffer,customHeaderSize);
}
void customUartError(){
	if((customUart.ErrorCode & HAL_UART_ERROR_ORE) != 0){
		printf("UART OVERRUN\r\n");
	}
	HAL_UART_Receive_IT(&customUart, customUartRXBuffer,customHeaderSize);
}
#pragma endregion

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
    txfailratio[0] = 0;
    txfailratio[1] = 0;
    memset(receiveData.bytesUnion.u8, 0, 32);
    memset(transmitData.bytesUnion.u8, 0, 32);
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  __HAL_RCC_CCMDATARAMEN_CLK_ENABLE();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DAC_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  MX_UART5_Init();
  MX_USART3_UART_Init();
  MX_SPI3_Init();
  MX_TIM8_Init();
  /* USER CODE BEGIN 2 */
  //MX_USB_DEVICE_Init();
  setStatusLed(0, 0, 1);

   HAL_Delay(100);
   printf("Starting RC Receiver\r\n");
   W25qxx_Init();



   huart5.RxCpltCallback = &customUartReceived;
   huart5.TxCpltCallback = &customUartDataTransmitted;
   huart5.ErrorCallback  = &customUartError;
   HAL_UART_Receive_IT(&customUart, customUartRXBuffer,customHeaderSize);
   common_nRFInit();

   setStatusLed(0, 0, 0);
   printf("Started RC Receiver\r\n");
   uint32_t lastDataReceived = HAL_GetTick();

   uint8_t buf[32];
   uint8_t length = 0;

   channelsOutputConfig[1 ].timOutput = &htim2.Instance->CCR1;
   channelsOutputConfig[2 ].timOutput = &htim2.Instance->CCR2;
   channelsOutputConfig[3 ].timOutput = &htim2.Instance->CCR3;
   channelsOutputConfig[4 ].timOutput = &htim2.Instance->CCR4;

   channelsOutputConfig[5 ].timOutput = &htim3.Instance->CCR1;
   channelsOutputConfig[6 ].timOutput = &htim3.Instance->CCR2;
//   channelsOutputConfig[7 ].timOutput = &htim3.Instance->CCR3;
   channelsOutputConfig[7 ].timOutput = &htim3.Instance->CCR4;

   channelsOutputConfig[8 ].timOutput = &htim1.Instance->CCR1;
   channelsOutputConfig[9 ].timOutput = &htim1.Instance->CCR2;
   channelsOutputConfig[10].timOutput = &htim1.Instance->CCR3;
   channelsOutputConfig[11].timOutput = &htim1.Instance->CCR4;

   channelsOutputConfig[12].timOutput = &htim4.Instance->CCR1;
   channelsOutputConfig[13].timOutput = &htim4.Instance->CCR2;
   channelsOutputConfig[14].timOutput = &htim4.Instance->CCR3;
   channelsOutputConfig[15].timOutput = &htim4.Instance->CCR4;

   channelsOutputConfig[16].timOutput = &htim8.Instance->CCR1;
   channelsOutputConfig[17].timOutput = &htim8.Instance->CCR2;
   channelsOutputConfig[18].timOutput = &htim8.Instance->CCR3;
//   channelsOutputConfig[20].timOutput = &htim8.Instance->CCR4;

   channelsOutputConfig[19].timOutput = 0;
   channelsOutputConfig[20].timOutput = 0;
   channelsOutputConfig[21].timOutput = 0;
   channelsOutputConfig[22].timOutput = 0;
   channelsOutputConfig[23].timOutput = 0;
   channelsOutputConfig[24].timOutput = 0;

 //  nRF24_RXResult pipeLine = nRF24_ReadPayloadDpl(buf, &length);
 //  while(!gotData){
 //	  HAL_GPIO_TogglePin(SLEDB_GPIO_Port, SLEDB_Pin);
 //	  HAL_Delay(250);
 //  }

   // Requesting config here and checking that

 //  setOkLed(1);
 //  HAL_Delay(500);
 //  setOkLed(0);

   if(HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1) != HAL_OK)Error_Handler();
   if(HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2) != HAL_OK)Error_Handler();
   if(HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3) != HAL_OK)Error_Handler();
   if(HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4) != HAL_OK)Error_Handler();

   if(HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1) != HAL_OK)Error_Handler();
   if(HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) != HAL_OK)Error_Handler();
   if(HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3) != HAL_OK)Error_Handler();
   if(HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4) != HAL_OK)Error_Handler();

   if(HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1) != HAL_OK)Error_Handler();
   if(HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2) != HAL_OK)Error_Handler();
//   if(HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3) != HAL_OK)Error_Handler();
   if(HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4) != HAL_OK)Error_Handler();

   if(HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1) != HAL_OK)Error_Handler();
   if(HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2) != HAL_OK)Error_Handler();
   if(HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3) != HAL_OK)Error_Handler();
   if(HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4) != HAL_OK)Error_Handler();

   if(HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1) != HAL_OK)Error_Handler();
   if(HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2) != HAL_OK)Error_Handler();
   if(HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3) != HAL_OK)Error_Handler();
//   if(HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4) != HAL_OK)Error_Handler();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
   uint32_t lastCHPrint = HAL_GetTick();
     while (1)
     {
   	  if (gotData) {
   		  lastDataReceived = HAL_GetTick();
   		  setStatusLed(0,1,0);
   		  gotData = 0;

   		  nRF24_RXResult pipeLine = nRF24_ReadPayloadDpl(buf, &length);
   		  //printf("%s Message size '%d'. Data: ", isTransmitter ? "ACK" : "Message", length);
   		  parseRFPacket(buf, length, pipeLine);

   	  }
   	  if(HAL_GetTick() - lastDataReceived > 1000){
   		if(HAL_GetTick() % 500 == 0)
   			setStatusLed(1,0,0);
   		else if(HAL_GetTick() % 250 == 0){
   			setStatusLed(0,0,0);
   		}
//   		  	setStatusLed(1,0,0);
   	  } else if(HAL_GetTick() - lastDataReceived > 500){
   		  	setStatusLed(0,0,1);
   	  }

   	  if(huart1.RxXferCount != 0){
   	   	  uint8_t uartData[1];
   		  HAL_UART_Receive(&huart1, uartData, 1, 1);
   		  switch(uartData[0]){
			  case '*':
				  printf("RESET");
				  NVIC_SystemReset();
				  break;
   		  }
   	  }

   	  if(HAL_GetTick() - lastCHPrint > 1000){
   		  lastCHPrint = HAL_GetTick();
   		  for(int i = 0;  i < 12; i++){
   			  printf("CH%02d: %04d ",i+1, channelValues[i]);
   		  }
   		  printf("RX %7u ERR %7u(%5.2f)", txfailratio[0], txfailratio[1], (double)txfailratio[0] / (double)txfailratio[1]);
   		  printf("\r\n");
   	  }

  	if(customChannelStreaming){
  		uint32_t tick =HAL_GetTick();
  		if(tick - lastChannelStreamTime > customUartChannelTickRate){
  			sendChannelData();
  		}
  	}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == nRF_IRQ_Pin){
		if(HAL_GPIO_ReadPin(nRF_CSN_GPIO_Port, nRF_CSN_Pin) != GPIO_PIN_SET){
			// An other transmission is already active. Just setting gotData
			printf("nRFBusy");
			gotData = 1;
			return;
		}
		uint8_t tx, fail, rx;
		uint8_t status = nRF24_GetIRQFlags();
//		uint8_t rxStat = nRF24_GetStatus_RXFIFO();
//		if(rxStat == nRF24_STATUS_RXFIFO_FULL){
////			printf("RXFIFO FULL");
//		}
		tx = (status & nRF24_FLAG_TX_DS) != 0;
		fail = (status & nRF24_FLAG_MAX_RT) != 0;
		rx = (status& nRF24_FLAG_RX_DR) != 0;
//		printf("T%dF%dR%d\r\n",tx,fail,rx);

		if (tx) {                                         // Have we successfully transmitted?
			if (isTransmitter)
			{
				printf("Send:OK");
			}
			if (!isTransmitter) {
//				printf("AOK\n");
			}
		}

		if (fail) {                                       // Have we failed to transmit?
			txfailratio[1]++;
			if (isTransmitter)
			{
				printf("Send:Failed");
			}
			if (!isTransmitter) {
//				printf("AFAIL\n");
			}
		}

		if (rx) {                      // Did we receive a message?
			txfailratio[0]++;
			gotData = 1;
		}
		nRF24_ClearIRQFlags();
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	setStatusLed(1,0,0);
	printf("Error in file %s on line %d\r\n", file, line);
	uint8_t printCount = 0;
	while(1){
		HAL_Delay(100);
		printCount++;
		if(printCount % 5 == 0){
			HAL_GPIO_TogglePin(SLEDR_GPIO_Port, SLEDR_Pin);
			printf("Error in file %s on line %d\r\n", file, line);
		}
		if(printCount == 20){
			NVIC_SystemReset();
		}
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
