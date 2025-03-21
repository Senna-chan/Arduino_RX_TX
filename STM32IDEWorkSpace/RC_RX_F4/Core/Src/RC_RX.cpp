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
#include <RC_RX.hpp>
#include <queue>
#include <stdio.h>
#include <stdlib.h>

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

std::queue<char*> serialTXBuffer;

channelOutputConfig channelsOutputConfig[25];
uint8_t nrfAddress[] = { 0x33, 0x22, 0x11 };
uint8_t nRFDataReady = 0;
uint8_t gotData = 0;
uint32_t txfailratio[2];

bool chPacketReceived = false;

uint16_t channelValues[24];

transmitTypes transmitterData;
receiveTypes receiverData;
Settings settings = { 0 };
Model activeSettings;

Settings *receivedSettings = (Settings*)malloc(sizeof(Settings));

uint8_t readingSettings = 0; ///< Used to show that we are going to read the settings from the transmitter
uint16_t readingSettingsPacketAmount = 0; ///< This is how much settingsdata packets we are going to get
uint8_t readingSettingsPacketAmountRest = 0; ///< This is how much bytes are left after settingsdata packets

uint8_t saveSettingsToStorage = 0;
uint32_t calculatedCRC = 0;
uint32_t settingsCRC = 0;
uint32_t lastCHPrint = HAL_GetTick();
uint32_t lastDataReceived = HAL_GetTick();

//SbusRx sbusRx(SBUSUART);
bfs::SbusTx sbusTx(&SBUSUART);
uint32_t lastSBUSSend = HAL_GetTick();

/* Private function prototypes -----------------------------------------------*/


/* Private user code ---------------------------------------------------------*/


void setStatusLed(uint8_t R, uint8_t G, uint8_t B) {
	HAL_GPIO_WritePin(SLEDR_GPIO_Port, SLEDR_Pin,(R ? GPIO_PIN_SET : GPIO_PIN_RESET));
	HAL_GPIO_WritePin(SLEDG_GPIO_Port, SLEDG_Pin,(G ? GPIO_PIN_SET : GPIO_PIN_RESET));
	HAL_GPIO_WritePin(SLEDB_GPIO_Port, SLEDB_Pin,(B ? GPIO_PIN_SET : GPIO_PIN_RESET));
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
	} else {
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
	} else {
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
	HAL_UART_Transmit(&huart1, (uint8_t*) &b, 1, 200);
}

void UART_SendStr(char *string) {
	HAL_UART_Transmit(&huart1, (uint8_t*) string, (uint16_t) strlen(string), 200);
}

void setOutput(uint8_t index, uint16_t outputValue) {
	channelOutputConfig choc = channelsOutputConfig[index];
	uint32_t channelValue = outputValue;
	channelValue += 1000;
	channelValues[index - 1] = channelValue;
	if (channelValue == 2023) {
		channelValues[index - 1] = 0;
		return;
	}

	channelConfigs* channelConfig = &settings.model[settings.activeModel].channel_settings[index - 1];

	if (choc.currentOutputMode == OUTPUTMODE_RC) {
		if (choc.timOutput == 0) return;

		*choc.timOutput = channelValues[index - 1];
	} else if (choc.currentOutputMode == OUTPUTMODE_IO) {
		if (choc.timOutput == 0)
			return;
		if (channelValue > 1500) {
			*choc.timOutput = 7000; // Max output
		} else {
			*choc.timOutput = 0;
		}
	}
	else if (choc.currentOutputMode == OUTPUTMODE_DAC) {
		if (choc.miscOutput != 0) *choc.miscOutput = map(channelValue, 1000, 2000, 0,4095);
	}
	else if(choc.currentOutputMode == OUTPUTMODE_STEP){
		uint32_t frequency = 0;
		if(channelConfig->stepperConfig.centerIs0){
			if(channelValue > 1500) frequency = map(channelValue, 1500, 2000, channelConfig->stepperConfig.minFrequency, channelConfig->stepperConfig.maxFrequency);
			if(channelValue < 1500) frequency = map(channelValue, 1500, 1000, channelConfig->stepperConfig.minFrequency, channelConfig->stepperConfig.maxFrequency);
		} else{
			map(channelValue, 1000, 2000, channelConfig->stepperConfig.minFrequency, channelConfig->stepperConfig.maxFrequency);
		}
		TIM_setOverflow(choc.miscTimConf, frequency, TimerFormat_t::HERTZ_FORMAT);
		uint32_t dutyCycle = 50;
		if(channelConfig->stepperConfig.centerIs0 && channelValue == 1500) dutyCycle = 0;
		if(channelValue == 1000) dutyCycle = 0;
		TIM_setCaptureCompare(choc.miscTimConf,choc.miscTimCH, dutyCycle, TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
	} else if(choc.currentOutputMode == OUTPUTMODE_PWM){
		uint32_t duty = 0;

		if(channelConfig->pwmConfig.centerIs0){
			if(channelValue > 1500) duty = map(channelValue, 1500, 2000, 0, 1023);
			if(channelValue < 1500) duty = map(channelValue, 1500, 1000, 0, 1023);
		} else{
			duty = map(channelValue, 1000, 2000, 0, 1023);
		}
		TIM_setCaptureCompare(choc.miscTimConf,choc.miscTimCH, duty, TimerCompareFormat_t::RESOLUTION_10B_COMPARE_FORMAT);
	}
}


uint16_t receivedSettingsPacket;
void parseRFPacket(uint8_t *buf, uint8_t length, nRF24_RXResult pipeLine) {
	if (pipeLine == nRF24_RX_EMPTY) {
		printf("Pipeline is empty");
		return;
	}
	if (length == 6) {
		for (int i = 0; i < length; i++) {
			printf(" %02d ", buf[i]);
		}
		UART_SendChar('\n');
	} else {
		memmove(transmitterData.bytesUnion.u8, buf, 32);
		uint8_t packetId = transmitterData.bytesUnion.u8[0] & 0b1111;
		switch (packetId) {
		case CHANNELDATAID: {
			HAL_GPIO_TogglePin(IO_DBG_1_GPIO_Port, IO_DBG_1_Pin);
			setOutput(1, transmitterData.ch_data.channel1);
			setOutput(2, transmitterData.ch_data.channel2);
			setOutput(3, transmitterData.ch_data.channel3);
			setOutput(4, transmitterData.ch_data.channel4);
			setOutput(5, transmitterData.ch_data.channel5);
			setOutput(6, transmitterData.ch_data.channel6);
			setOutput(7, transmitterData.ch_data.channel7);
			setOutput(8, transmitterData.ch_data.channel8);
			setOutput(9, transmitterData.ch_data.channel9);
			setOutput(10, transmitterData.ch_data.channel10);
			setOutput(11, transmitterData.ch_data.channel11);
			setOutput(12, transmitterData.ch_data.channel12);
			setOutput(13, transmitterData.ch_data.channel13);
			setOutput(14, transmitterData.ch_data.channel14);
			setOutput(15, transmitterData.ch_data.channel15);
			setOutput(16, transmitterData.ch_data.channel16);
			setOutput(17, transmitterData.ch_data.channel17);
			setOutput(18, transmitterData.ch_data.channel18);
			setOutput(19, transmitterData.ch_data.channel19);
			setOutput(20, transmitterData.ch_data.channel20);
			setOutput(21, transmitterData.ch_data.channel21);
			setOutput(22, transmitterData.ch_data.channel22);
			setOutput(23, transmitterData.ch_data.channel23);
			setOutput(24, transmitterData.ch_data.channel24);

			uint32_t now = HAL_GetTick();
			uint8_t txBuf[6];
			txBuf[0] = 0;
			txBuf[1] = 0;
			txBuf[2] = now >> 24 & 0xFF;
			txBuf[3] = now >> 16 & 0xFF;
			txBuf[4] = now >> 8 & 0xFF;
			txBuf[5] = now >> 0 & 0xFF;
			nRF24_WriteAckPayload(pipeLine, txBuf, 6);
			sbusTx.set_ch(1, transmitterData.ch_data.channel1);
			sbusTx.set_ch(2, transmitterData.ch_data.channel2);
			sbusTx.set_ch(3, transmitterData.ch_data.channel3);
			sbusTx.set_ch(4, transmitterData.ch_data.channel4);
			sbusTx.set_ch(5, transmitterData.ch_data.channel5);
			sbusTx.set_ch(6, transmitterData.ch_data.channel6);
			sbusTx.set_ch(7, transmitterData.ch_data.channel7);
			sbusTx.set_ch(8, transmitterData.ch_data.channel8);
			sbusTx.set_ch(9, transmitterData.ch_data.channel9);
			sbusTx.set_ch(10, transmitterData.ch_data.channel10);
			sbusTx.set_ch(11, transmitterData.ch_data.channel11);
			sbusTx.set_ch(12, transmitterData.ch_data.channel12);
			sbusTx.set_ch(13, transmitterData.ch_data.channel13);
			sbusTx.set_ch(14, transmitterData.ch_data.channel14);
			sbusTx.set_ch(15, transmitterData.ch_data.channel15);
			sbusTx.set_ch(16, transmitterData.ch_data.channel16);
			sbusTx.failsafe(false);
			sbusTx.lost_frame(false);
			chPacketReceived = true;
//					receiverData.bytesUnion.u8[0] = SETTINGSDATAID;
//					nRF24_WriteAckPayload(pipeLine, receiverData.bytesUnion.u8, 6);
//					memset(&receivedSettings, 0, sizeof(Settings));
			break;
		}
		case SETTINGSDATASETUPID: {
			uint16_t crc = gencrc(transmitterData.bytesUnion.u8, RFPACKETLENGTH - 2);
			uint16_t recCRC = transmitterData.settingsData.crc;
			if(crc != recCRC){
				printf("MODULO CRC Incorrect. Calc 0x%02X. Received 0x%02X\r\n", recCRC,crc);
				printf("packet_%d: ", receivedSettingsPacket);
				for (int b = 0; b < 32; b++) printf("0x%02X ", transmitterData.bytesUnion.u8[b]);
				printf("\r\n");
				receiverData.settingsDataAck.settingsPacket = 0; // Invalid packet
			} else{
				HAL_GPIO_TogglePin(IO_DBG_2_GPIO_Port, IO_DBG_2_Pin);
				readingSettings = 1;
				readingSettingsPacketAmount = (transmitterData.bytesUnion.u8[1] << 8) | transmitterData.bytesUnion.u8[2];
				readingSettingsPacketAmountRest = transmitterData.bytesUnion.u8[3];
				receiverData.bytesUnion.u8[0] = SETTINGSDATAID;
				nRF24_WriteAckPayload(pipeLine, receiverData.bytesUnion.u8, 1);
				memset(receivedSettings, 0, sizeof(Settings));
				printf("PS %d MOD %d\r\n", readingSettingsPacketAmount,	readingSettingsPacketAmountRest);
			}
			break;
		}
		case SETTINGSDATAID: {
			memset(receiverData.bytesUnion.u8, 0, 32);
			receiverData.bytesUnion.u8[0] = SETTINGSDATAID;
			HAL_GPIO_TogglePin(IO_DBG_2_GPIO_Port, IO_DBG_2_Pin);
			if (readingSettings == 0) {
				printf("SETTINGS SETUP NOT DONE");
			} else {
				receivedSettingsPacket = transmitterData.settingsData.packetNumber;
//				printf("packet_%d: ", receivedSettingsPacket);
//				for (int b = 0; b < 32; b++) printf("0x%02X ", transmitterData.bytesUnion.u8[b]);
//				printf("\r\n");
				receiverData.settingsDataAck.settingsPacket = receivedSettingsPacket;
				uint8_t *receivedSettingsPtr = (uint8_t*)receivedSettings;
				uint8_t *tdPtr = (uint8_t*)transmitterData.settingsData.data;
				if (receivedSettingsPacket == readingSettingsPacketAmount) { // If settings packet received is the last packet
					if (readingSettingsPacketAmountRest != 0) { // If there is rest data
						printf("CONFMOD\r\n");
//						receivedSettingsPtr += ((receivedSettingsPacket - 1) * SETTINGSDATASIZE) + readingSettingsPacketAmountRest;
						receivedSettingsPtr += ((receivedSettingsPacket) * SETTINGSDATASIZE);

						uint16_t crc = gencrc(transmitterData.bytesUnion.u8, RFPACKETLENGTH - 2);
						uint16_t recCRC = transmitterData.settingsData.crc;

						if(crc != recCRC){
							printf("MODULO CRC Incorrect. Calc 0x%02X. Received 0x%02X\r\n", crc, recCRC);
							printf("packet_%d: ", receivedSettingsPacket);
							for (int b = 0; b < 32; b++) printf("0x%02X ", transmitterData.bytesUnion.u8[b]);
							printf("\r\n");
							receiverData.settingsDataAck.settingsPacket = 0; // Invalid packet
						} else{
							memcpy(receivedSettingsPtr, tdPtr,readingSettingsPacketAmountRest);
						}

					}
				} else if (receivedSettingsPacket == (readingSettingsPacketAmount + 1)) {
					// If settings packet received is 1 higher than settings packet amount
					// So the end packet
					uint16_t crc = gencrc(transmitterData.bytesUnion.u8, RFPACKETLENGTH - 2);
					uint16_t recCRC = transmitterData.settingsData.crc;

					if(crc != recCRC){
						printf("FINAL CRC Incorrect. Calc 0x%02X. Received 0x%02X\r\n", crc, recCRC);
						printf("packet_%d: ", receivedSettingsPacket);
						for (int b = 0; b < 32; b++) printf("0x%02X ", transmitterData.bytesUnion.u8[b]);
						printf("\r\n");
						receiverData.settingsDataAck.settingsPacket = 0; // Invalid packet
					} else{
						printf("CONFRECEIVED\r\n");
	//					memset(&settings, 0, sizeof(Settings));
						memcpy(&settings, receivedSettings, sizeof(Settings));
						calculatedCRC = HAL_CRC_Calculate(&hcrc, (uint32_t*)&settings, sizeof(Settings) / 4);
						readingSettings = 0;
						settingsCRC = transmitterData.bytesUnion.u32[1];
						saveSettingsToStorage = 1;
					}

				} else if (receivedSettingsPacket < readingSettingsPacketAmount) {
					receivedSettingsPtr += (receivedSettingsPacket * SETTINGSDATASIZE);
					if((uint32_t*)receivedSettingsPtr > ((uint32_t*) receivedSettings) + sizeof(Settings)){
						printf("SETTINGSPTR OUT OF RANGE\r\n");
						Error_Handler();
					}
					uint16_t crc = gencrc(transmitterData.bytesUnion.u8, RFPACKETLENGTH - 2);
					uint16_t recCRC = transmitterData.settingsData.crc;
					if(crc != recCRC){
						printf("DATA CRC Incorrect. Calc 0x%02X. Received 0x%02X\r\n",crc, recCRC);
						receiverData.settingsDataAck.settingsPacket = 0; // Invalid packet
					} else{
						memcpy(receivedSettingsPtr, tdPtr, SETTINGSDATASIZE);
					}
				} else {
					Error_Handler();
				}
			}
			nRF24_WriteAckPayload(pipeLine, receiverData.bytesUnion.u8, 5);
			break;
		}
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
	CHANNELS, STREAM_CHANNELS
};

uint8_t calculateCRC(uint8_t *data, uint8_t length) {
	uint8_t crc = 0xff;
	size_t i, j;
	for (i = 0; i < length; i++) {
		crc ^= data[i];
		for (j = 0; j < 8; j++) {
			if ((crc & 0x80) != 0)
				crc = (uint8_t) ((crc << 1) ^ 0x31);
			else
				crc <<= 1;
		}
	}
	return crc;
}

void sendChannelData() {
	lastChannelStreamTime = HAL_GetTick();
	uint8_t idx = 0;
	uint8_t dataSize = 24 * 2;
	customUartTXBuffer[idx++] = customHeaderByte;
	customUartTXBuffer[idx++] = CHANNELS;
	customUartTXBuffer[idx++] = dataSize;
	memcpy(customUartTXBuffer + idx, channelValues, dataSize);
	idx += dataSize;
	customUartTXBuffer[idx++] = calculateCRC(customUartTXBuffer + 3, dataSize);
	customUartTXBuffer[idx++] = customFooterByte;
	if (HAL_UART_Transmit_IT(&customUart, customUartTXBuffer, idx) != HAL_OK) {
		printf("UARTBUSY\r\n");
	}
}

extern "C" void customUartDataTransmitted(struct __UART_HandleTypeDef *huart) {
//	printf("CUSTOMTX\r\n");
}

extern "C" void customUartReceived(struct __UART_HandleTypeDef *huart) {
//	printf("CUSTOMRX\r\n");
	uint8_t dataSize = customUartRXBuffer[2];
	uint8_t crc = customUartRXBuffer[2 + dataSize + 1];
	uint8_t footerByte = customUartRXBuffer[2 + dataSize + 2];
	if (footerByte != customFooterByte) {
		HAL_UART_Receive_IT(&customUart, customUartRXBuffer + customHeaderSize,
				dataSize + customFooterSize);
		return;
	}
	switch (customUartRXBuffer[1]) {
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
	HAL_UART_Receive_IT(&customUart, customUartRXBuffer, customHeaderSize);
}
void customUartError(struct __UART_HandleTypeDef *huart) {
	if ((customUart.ErrorCode & HAL_UART_ERROR_ORE) != 0) {
		printf("UART OVERRUN\r\n");
	}
	HAL_UART_Receive_IT(&customUart, customUartRXBuffer, customHeaderSize);
}
#pragma endregion

void setDefault(uint8_t channelNumber){
	if(channelNumber == 0){
		for(int ch = 1; ch <= 24; ch++){
			setDefault(ch);
		}
	} else{
		setOutput(channelNumber, settings.model[settings.activeModel].channel_settings[channelNumber - 1].chDefaults);
	}
}

void setupChannelOutputConfign(uint8_t channelNumber){
	setupChannelOutputConfigtt(channelNumber, nullptr,0, nullptr, nullptr, 0, nullptr, 0);
}

void setupChannelOutputConfigt(uint8_t channelNumber, TIM_HandleTypeDef* mainTimer, uint8_t mainTimerChannel){
	setupChannelOutputConfigtt(channelNumber, mainTimer,mainTimerChannel, nullptr, nullptr, 0, nullptr, 0);
}

void setupChannelOutputConfigtm(uint8_t channelNumber, TIM_HandleTypeDef* mainTimer, uint8_t mainTimerChannel, __IO uint32_t* miscOutput, GPIO_TypeDef* muxGPIO, uint32_t muxPin){
	setupChannelOutputConfigtt(channelNumber, mainTimer,mainTimerChannel, miscOutput, nullptr, 0, muxGPIO, muxPin);
}

void setupChannelOutputConfigtt(uint8_t channelNumber, TIM_HandleTypeDef* mainTimer, uint8_t mainTimerChannel, __IO uint32_t* miscOutput, TIM_HandleTypeDef* miscTimConf, uint8_t miscTIMCH, GPIO_TypeDef* muxGPIO, uint32_t muxPin){

	// Assigning everything to the output
	__IO uint32_t* mainTimerOutput;
	switch(mainTimerChannel){
	case TIM_CHANNEL_1:
		mainTimerOutput = &mainTimer->Instance->CCR1;
		break;
	case TIM_CHANNEL_2:
		mainTimerOutput = &mainTimer->Instance->CCR2;
		break;
	case TIM_CHANNEL_3:
		mainTimerOutput = &mainTimer->Instance->CCR3;
		break;
	case TIM_CHANNEL_4:
		mainTimerOutput = &mainTimer->Instance->CCR4;
		break;
	default:
		Error_Handler(); // We should not come here
	}

	channelOutputConfig *chOuputConf = &channelsOutputConfig[channelNumber];

	chOuputConf->timOutput 			= mainTimerOutput;
	chOuputConf->mainTimer 			= mainTimer;
	chOuputConf->mainTimerCH 		= mainTimerChannel;
	chOuputConf->miscOutput 		= miscOutput;

	chOuputConf->miscTimConf 		= miscTimConf;
	if(miscTimConf != nullptr){
		chOuputConf->miscTimCH 		= miscTIMCH;
	}

	if(muxGPIO != nullptr){
		chOuputConf->muxGPIO 		= muxGPIO;
		chOuputConf->muxPIN 		= muxPin;
	}

	// Configuring the correct output mode from settings
	channelConfigs* channelConfig = &settings.model[settings.activeModel].channel_settings[channelNumber - 1];
	switch(channelConfig->outputMode){
	case OUTPUTMODE_RC:
	case OUTPUTMODE_IO:
		// Nothing needed in these modes. THis is default mode
		break;
	case OUTPUTMODE_PWM:
		TIM_setOverflow(chOuputConf->miscTimConf, channelConfig->pwmConfig.frequency, TimerFormat_t::HERTZ_FORMAT);
	case OUTPUTMODE_DAC:
		HAL_GPIO_WritePin(chOuputConf->muxGPIO, chOuputConf->muxPIN, GPIO_PinState::GPIO_PIN_SET);
		break;
	case OUTPUTMODE_STEP:
		HAL_GPIO_WritePin(chOuputConf->muxGPIO, chOuputConf->muxPIN, GPIO_PinState::GPIO_PIN_SET);
		TIM_setOverflow(chOuputConf->miscTimConf, channelConfig->stepperConfig.minFrequency, TimerFormat_t::HERTZ_FORMAT);
		TIM_setCaptureCompare(chOuputConf->miscTimConf,chOuputConf->miscTimCH, 0, TimerCompareFormat_t::TICK_COMPARE_FORMAT); // Default to off
		break;
	}

	chOuputConf->currentOutputMode = channelConfig->outputMode;
}

void configureChannels(){

	setupChannelOutputConfigt(1,&htim2, TIM_CHANNEL_1);
	setupChannelOutputConfigt(2,&htim2, TIM_CHANNEL_2);
	setupChannelOutputConfigt(3,&htim2, TIM_CHANNEL_3);
	setupChannelOutputConfigt(4,&htim2, TIM_CHANNEL_4);

	setupChannelOutputConfigtm(5,&htim3, TIM_CHANNEL_4, &hdac.Instance->DHR12R1, CHSEL_DAC1_CH5_GPIO_Port, CHSEL_DAC1_CH5_Pin);
	setupChannelOutputConfigtm(6,&htim1, TIM_CHANNEL_1, &hdac.Instance->DHR12R2, CHSEL_DAC2_CH6_GPIO_Port, CHSEL_DAC2_CH6_Pin);

	setupChannelOutputConfigt(7,&htim1, TIM_CHANNEL_2);

	setupChannelOutputConfigtt(8, &htim1, TIM_CHANNEL_3, &htim13.Instance->CCR1, &htim13, TIM_CHANNEL_1, CHSEL_STEP3_FF5_CH8_GPIO_Port, CHSEL_STEP3_FF5_CH8_Pin);
	setupChannelOutputConfigtt(9, &htim1, TIM_CHANNEL_4, &htim14.Instance->CCR1, &htim14, TIM_CHANNEL_1, CHSEL_STEP4_FF6_CH9_GPIO_Port, CHSEL_STEP4_FF6_CH9_Pin);

	setupChannelOutputConfigtt(10, &htim4, TIM_CHANNEL_1, &htim12.Instance->CCR1, &htim12, TIM_CHANNEL_1, CHSEL_FF1_1_CH10_GPIO_Port, CHSEL_FF1_1_CH10_Pin);
	setupChannelOutputConfigtt(11, &htim4, TIM_CHANNEL_2, &htim12.Instance->CCR2, &htim12, TIM_CHANNEL_2, CHSEL_FF1_2_CH11_GPIO_Port, CHSEL_FF1_2_CH11_Pin);

	setupChannelOutputConfigt(12,&htim4, TIM_CHANNEL_3);
	setupChannelOutputConfigt(13,&htim4, TIM_CHANNEL_4);

	setupChannelOutputConfigt(14,&htim8, TIM_CHANNEL_1);
	setupChannelOutputConfigt(15,&htim8, TIM_CHANNEL_2);
	setupChannelOutputConfigtt(16,&htim8, TIM_CHANNEL_3, &htim10.Instance->CCR1, &htim10, TIM_CHANNEL_1, CHSEL_STEP1_FF3_CH16_GPIO_Port, CHSEL_STEP1_FF3_CH16_Pin);
	setupChannelOutputConfigtt(17,&htim8, TIM_CHANNEL_4, &htim11.Instance->CCR1, &htim11, TIM_CHANNEL_1, CHSEL_STEP2_FF4_CH17_GPIO_Port, CHSEL_STEP2_FF4_CH17_Pin);

	// The rest is not backed by a timer and the defaults are "nullptr" so we are safe to not define them
}

void setup(void) {

	HAL_UART_RegisterCallback(&huart1, HAL_UART_TX_COMPLETE_CB_ID, UART1TXDone);
	HAL_UART_RegisterCallback(&huart1, HAL_UART_ERROR_CB_ID, UART1Error);

	txfailratio[0] = 0;
	txfailratio[1] = 0;
	memset(receiverData.bytesUnion.u8, 0, 32);
	memset(transmitterData.bytesUnion.u8, 0, 32);
	__HAL_RCC_CCMDATARAMEN_CLK_ENABLE();

	//MX_USB_DEVICE_Init();
	setStatusLed(0, 0, 1);

	HAL_Delay(100);
	printf("Starting RC Receiver\r\n");
	W25qxx_Init();

	printf("Loading settings");
	uint32_t start = HAL_GetTick();
	W25qxx_ReadBlock((uint8_t*)&settings, 1, 0, sizeof(Settings));
	printf("Loading took %d millis\r\n", HAL_GetTick() - start);
	huart5.RxCpltCallback = &customUartReceived;
	huart5.TxCpltCallback = &customUartDataTransmitted;
	huart5.ErrorCallback = &customUartError;
	HAL_UART_Receive_IT(&customUart, customUartRXBuffer, customHeaderSize);
	common_nRFInit();

	// Check if connection is active. If not then do not do anything
	//  nRF24_RXResult pipeLine = nRF24_ReadPayloadDpl(buf, &length);
	//  while(!gotData){
	//	  HAL_GPIO_TogglePin(SLEDB_GPIO_Port, SLEDB_Pin);
	//	  HAL_Delay(250);
	//  }

	// Check if the settings are the same by asking the TX for the CRC

	//  setOkLed(1);
	//  HAL_Delay(500);
	//  setOkLed(0);

	setStatusLed(0, 0, 0);

	configureChannels();
	setDefault(0); // Set everything to default?
	for(int i = 0; i <= 24; i++){
		if(channelsOutputConfig[i].mainTimer != nullptr){
			if (HAL_TIM_PWM_Start(channelsOutputConfig[i].mainTimer, channelsOutputConfig[i].mainTimerCH) != HAL_OK){
				printf("Failed to init the main timer for channel %d\r\n", i);
				Error_Handler();
			}
		}
		if(channelsOutputConfig[i].miscTimConf != nullptr){
			if (HAL_TIM_PWM_Start(channelsOutputConfig[i].miscTimConf, channelsOutputConfig[i].miscTimCH) != HAL_OK){
				printf("Failed to init the misc timer for channel %d\r\n", i);
				Error_Handler();
			}
		}
	}

//	if (HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1) != HAL_OK)		Error_Handler();
//	if (HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2) != HAL_OK)		Error_Handler();
//	if (HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3) != HAL_OK)		Error_Handler();
//	if (HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4) != HAL_OK)		Error_Handler();
//
//	if (HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1) != HAL_OK)		Error_Handler();
//	if (HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2) != HAL_OK)		Error_Handler();
//	if (HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3) != HAL_OK)		Error_Handler();
//	if (HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4) != HAL_OK)		Error_Handler();
//
////	if (HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1) != HAL_OK)		Error_Handler();
////	if (HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2) != HAL_OK)		Error_Handler();
//	if (HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3) != HAL_OK)		Error_Handler();
//	if (HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4) != HAL_OK)		Error_Handler();
//
//	if (HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1) != HAL_OK)		Error_Handler();
//	if (HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2) != HAL_OK)		Error_Handler();
//	if (HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3) != HAL_OK)		Error_Handler();
//	if (HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4) != HAL_OK)		Error_Handler();
//
//	if (HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1) != HAL_OK)		Error_Handler();
//	if (HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2) != HAL_OK)		Error_Handler();
//	if (HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3) != HAL_OK)		Error_Handler();
//    if (HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4) != HAL_OK)		Error_Handler();
//
//
//    if (HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1) != HAL_OK)		Error_Handler();
//    if (HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2) != HAL_OK)		Error_Handler();
//
//    if (HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1) != HAL_OK)	Error_Handler();
//
//    if (HAL_TIM_PWM_Start(&htim11, TIM_CHANNEL_1) != HAL_OK)	Error_Handler();
//
//    if (HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1) != HAL_OK)	Error_Handler();
//    if (HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2) != HAL_OK)	Error_Handler();
//
//    if (HAL_TIM_PWM_Start(&htim13, TIM_CHANNEL_1) != HAL_OK)	Error_Handler();
//
//    if (HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1) != HAL_OK)	Error_Handler();

	uint32_t settingsSize = sizeof(Settings);
	printf("Size of settings %d\r\n", settingsSize);

	printf("Started RC Receiver\r\n");
}

void loop() {
	uint32_t now = HAL_GetTick();
	if (gotData) {
		lastDataReceived = now;
		setStatusLed(0, 1, 0);
		gotData = 0;
		uint8_t buf[32];
		uint8_t length = 0;

		nRF24_RXResult pipeLine = nRF24_ReadPayloadDpl(buf, &length);
		//printf("%s Message size '%d'. Data: ", isTransmitter ? "ACK" : "Message", length);
		parseRFPacket(buf, length, pipeLine);

	}
	now = HAL_GetTick();
	if (now - lastDataReceived > 1000) {
		if (now % 500 == 0)
			setStatusLed(1, 0, 0);
		else if (now % 250 == 0) {
			setStatusLed(0, 0, 0);
		}
//   		  	setStatusLed(1,0,0);
	} else if (now - lastDataReceived > 500) {
		setStatusLed(0, 0, 1);
		sbusTx.failsafe(true);
	} else if(now - lastDataReceived > 20){
		sbusTx.lost_frame(true);
	}
	if(now - lastSBUSSend >= 7){
		lastSBUSSend = now;
		sbusTx.Write();
	}

	if (huart1.RxXferCount != 0) {
		uint8_t uartData[1];
		HAL_UART_Receive(&huart1, uartData, 1, 1);
		switch (uartData[0]) {
		case '*':
			printf("RESET");
			NVIC_SystemReset();
			break;
		}
	}
	now = HAL_GetTick();
	if (now - lastCHPrint >= 1000) {
//	if (now % 1000 == 0) {
		lastCHPrint = now;
		char buf[512] = {0};
		char* bufPtr = buf;
		bufPtr += sprintf(bufPtr, "%7d ", now);
		for (int i = 0; i < 12; i++) {
			bufPtr += sprintf(bufPtr, " CH%02d: %04d", i + 1, channelValues[i]);
		}
		bufPtr += sprintf(bufPtr, " RX %7u ERR %7u(%5.2f)", txfailratio[0], txfailratio[1], (double) txfailratio[0] / (double) txfailratio[1]);
		bufPtr += sprintf(bufPtr, "\r\n");
		printf(buf);
	}

	if(saveSettingsToStorage == 1){
		uint32_t* settingsPtr = (uint32_t*)&settings;
		uint32_t crc = HAL_CRC_Calculate(&hcrc, settingsPtr, sizeof(Settings) / 4);

		if(crc == settingsCRC){
			printf("Settings successfully received. Saving to storage\r\n");
			uint32_t start = HAL_GetTick();
			W25qxx_EraseBlock(1); // Do I need to erase the block before writing
			W25qxx_WriteBlock((uint8_t*)&settings, 1, 0, sizeof(Settings));
			printf("Saving settings took %d millis\r\n", HAL_GetTick() - start);
			saveSettingsToStorage = 0;
		} else{
			printf("SettingsCRC failed\t");
			printf("Calculated CRC %u. Received CRC %u\r\n", crc, settingsCRC);
		}
	}

	if (customChannelStreaming) {
		if (now - lastChannelStreamTime > customUartChannelTickRate) {
			sendChannelData();
		}
	}
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == nRF_IRQ_Pin) {
		if (HAL_GPIO_ReadPin(nRF_CSN_GPIO_Port, nRF_CSN_Pin) != GPIO_PIN_SET) {
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
		tx = (status & nRF24_FLAG_TX_DS ) != 0;
		fail = (status & nRF24_FLAG_MAX_RT ) != 0;
		rx = (status & nRF24_FLAG_RX_DR ) != 0;
//		printf("T%dF%dR%d\r\n",tx,fail,rx);

		if (tx) {                           // Have we successfully transmitted?
			if (isTransmitter) {
				printf("Send:OK");
			}
			if (!isTransmitter) {
//				printf("AOK\n");
			}
		}

		if (fail) {                               // Have we failed to transmit?
			txfailratio[1]++;
			if (isTransmitter) {
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
void UART1Error(UART_HandleTypeDef *huart){
	setStatusLed(255, 0, 0);
	// ERror in main serial so what now?
}

char* stringToPrint;
void UART1TXDone(UART_HandleTypeDef *huart){
	uart1TXBusy = 0;
	if(stringToPrint != nullptr){
		free(stringToPrint);
		stringToPrint = nullptr;
	}
	if(!serialTXBuffer.empty()){
		stringToPrint = serialTXBuffer.front();
		SerialPrint(stringToPrint, strlen(stringToPrint)); // This should work?
		serialTXBuffer.pop();
	}
}

void SerialPrint(char* string, int length){
	if(uart1TXBusy == 1){
		char* strPtr = (char*)malloc(length + 1);
//		strcpy(strPtr, string);
		memcpy(strPtr, string, length);
		strPtr[length] = '\0';
		serialTXBuffer.push(strPtr);
	} else{
		uart1TXBusy = 1;
		HAL_UART_Transmit_IT(&huart1, (uint8_t*)string, length);
	}
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler_CPP(char *file, int line) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	setStatusLed(1, 0, 0);
	printf("Error in file %s on line %d\r\n", file, line);
	uint8_t printCount = 0;
	while (1) {
		HAL_Delay(100);
		printCount++;
		if (printCount % 5 == 0) {
			HAL_GPIO_TogglePin(SLEDR_GPIO_Port, SLEDR_Pin);
			printf("Error in file %s on line %d\r\n", file, line);
		}
		if (printCount == 20) {
			NVIC_SystemReset();
		}
	}
	/* USER CODE END Error_Handler_Debug */
}


