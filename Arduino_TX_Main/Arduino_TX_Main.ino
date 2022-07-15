#include <STM32FreeRTOS.h>
#include <PlotterLib.h>
#include <SerialControlLibrary.h>
#include <eepromi2c_Anything.h>
#include <BetterHardwareTimer.h>
#include <GUISlice_HMI_Lib.h>
#include <i2cEncoderLibV2.h>
#include <Adafruit_MCP23008.h>
#include "ChannelFunctions.h"
#include <SPI.h>
#include <MyHelpers.h>
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <TimedAction.h>
#include "Structs.h"
#include "Arduino_TX_Display_hmi.h"
#include "SharedVars.h"
#include <config.h>
#include "ADCDMAFunctions.h"
#include <ArduinoTimerV2.h>
#include "nrf24.h"
#include "stm32f4xx_hal_crc.h"
#include "SharedFunctions.h"

TaskHandle_t nRFData_taskHandle;			// nRF Receive task
TaskHandle_t cal_taskHandle;				// Task for handling calibration buttons(Super high prio but only run when needed, Gets data via queue)
TaskHandle_t io_taskHandle;					// Task for handling IO expanders
TaskHandle_t encoder_taskHandle;			// Task for handling encoder
TaskHandle_t plotter_taskHandle;			// Task for plotter stuff
TaskHandle_t hmi_taskHandle;				// Task for HMI Data transmission things
TaskHandle_t serialControl_taskHandle;		// Task for serial control library
TaskHandle_t nrfTransmitTest_taskHandle;	// Task for nrf transmission testing
TaskHandle_t nrfTransit_taskHandle;			// Task for nrf transmission
TaskHandle_t printNrfStats_taskHandle;		// Task for printing nrf communication stats

SemaphoreHandle_t hmi_mutex;		// Lock for HMI
SemaphoreHandle_t nrf_mutex;		// Lock for nRF
SemaphoreHandle_t i2c_mutex;		// Lock for everything I2C
SemaphoreHandle_t serial_mutex;		// Lock for everything I2C

CRC_HandleTypeDef hcrc;
SerialControlLibrary scl;

bool debugging = true;

Adafruit_MCP23017 IOExpander1, IOExpander2, calButtonExpender;
uint16_t lastCalButtons = 0;


TwoWire Wire2 = TwoWire(PB10, PB11);
i2cEncoderLibV2 encoder(&Wire, ENCODER_ADDR);
bool encoderSettingsIndex = 0;
long prevSendTime;
bool printChannelValues = false;
bool printDMAValues = false;
bool printADCChannels = false;

bool allowSettingsSend = true;
uint16_t settingsAckValue = 0;

uint16_t buttonValues, oldButtonValues;

byte sendChannel = 0;

bool detectingChannelsSet = false;
uint16_t detectingRawChannels[24];
uint16_t rawChannels[24];
uint16_t prevRawChannels[24];
uint16_t parsedChannels[24];
uint16_t mappedChannels[24];
uint16_t fixedChannelValue = 0;
uint32_t IOExpanderBits = 0;
uint32_t prevIOExpanderBits = 0;
uint16_t twoWay = 0;
uint8_t oneWay = 0;
bool transmitTest = false;
uint32_t lastMessageSend = 0;

bool tx, fail, rx;

struct {
	uint32_t send;
	uint32_t txack;
	uint32_t rx;
	uint32_t fail;
} radioStats;

#define BTN_K0 PE4
#define BTN_K1 PE3

HMI_Text* DispDispObjs[24]{
 &e_n0, &e_n1, &e_n2, &e_n3, &e_n4, &e_n5, &e_n6, &e_n7, &e_n8, &e_n9,
 &e_n10, &e_n11, &e_n12, &e_n13, &e_n14, &e_n15, &e_n16, &e_n17, &e_n18, &e_n19,
&e_n20, &e_n21, &e_n22, &e_n23
};

HMI_Text* rawDispObjs[12]{
	&e_nr0,
	&e_nr1,
	&e_nr2,
	&e_nr3,
	&e_nr4,
	&e_nr5,
	&e_nr6,
	&e_nr7,
	&e_nr8,
	&e_nr9,
	&e_dprevio,
	&e_dcurio
};

HMI_Text* calDispObjs[10][2]{
	{&e_d1,&e_c1},
	{&e_d2,&e_c2},
	{&e_d3,&e_c3},
	{&e_d4,&e_c4},
	{&e_d5,&e_c5},
	{&e_d6,&e_c6},
	{&e_d7,&e_c7},
	{&e_d8,&e_c8},
	{&e_d9,&e_c9},
	{&e_d10,&e_c10},
};

extern "C" void _Error_Handler(const char* file, int line) {
	vTaskSuspendAll(); // Error mode. So stop all tasks becauase there is an error
	int count = 0;
	TaskHandle_t currentTask = xTaskGetCurrentTaskHandle();
	TaskStatus_t taskStatus;
	vTaskGetInfo(currentTask, &taskStatus, pdTRUE, eInvalid);
	while (1) {
		if (++count % 10 == 0) {
			Serial.printf("Error in file '%s' Line %d, Task %s\n", file, line, taskStatus.pcTaskName);
		}
		if (count == 100) HAL_NVIC_SystemReset();
		digitalToggle(LED_BUILTIN);
		delay(250);
	}
}

void notifyThread(TaskHandle_t taskHandle) {

}

#pragma region SPIStuff
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
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

void initSPI() {
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

#pragma endregion

// The big function. Parse all the data and create a nRF Packet
void updateValues() {
	memcpy(rawChannels, ADCDMABuffer, ADCCHANNELNUMBERS * 2);
	for (int i = 0; i < ADCCHANNELNUMBERS; i++)
	{
		auto chSettings = settings.model[settings.activeModel].channel_settings[i];
		if (chSettings.chMid != 0) {
			if (between(rawChannels[i], chSettings.chMid - settings.model[0].deadzone, settings.model[settings.activeModel].channel_settings[i].chMid + settings.model[0].deadzone))
			{
				parsedChannels[i] = 1500;
			}
			else {
				if (rawChannels[i] < settings.model[settings.activeModel].channel_settings[i].chMid)
				{
					parsedChannels[i] = map(rawChannels[i], settings.model[settings.activeModel].channel_settings[i].chMin, settings.model[settings.activeModel].channel_settings[i].chMid - settings.model[0].deadzone, 1000, 1500);
				}
				else
				{
					parsedChannels[i] = map(rawChannels[i], settings.model[settings.activeModel].channel_settings[i].chMid + settings.model[0].deadzone, settings.model[settings.activeModel].channel_settings[i].chMax, 1500, 2000);
				}
			}
		}
		else {
			if (rawChannels[i] > settings.model[settings.activeModel].channel_settings[i].chMin + settings.model[0].deadzone) {
				parsedChannels[i] = map(rawChannels[i], settings.model[settings.activeModel].channel_settings[i].chMin, settings.model[settings.activeModel].channel_settings[i].chMax - settings.model[0].deadzone, 1000, 2000);
			}
		}
		parsedChannels[i] += settings.model[settings.activeModel].channel_settings[i].chOffset;
		parsedChannels[i] = constrain(parsedChannels[i], 1000, 2000);
	}
	for (int i = 0; i < 24; i++) {
		auto io1t = settings.model[settings.activeModel].channel_settings[i].channelMapping[0].type;
		auto io2t = settings.model[settings.activeModel].channel_settings[i].channelMapping[1].type;
		auto io1 = settings.model[settings.activeModel].channel_settings[i].channelMapping[0].index;
		auto io2 = settings.model[settings.activeModel].channel_settings[i].channelMapping[1].index;
		auto outputMode = settings.model[settings.activeModel].channel_settings[i].outputMode;
		if (io1t == CTYPE_NONE && io2t == CTYPE_NONE) {
			mappedChannels[i] = 0; // Make sure that RX will not parse this
			continue;
		}
		if (io1t != CTYPE_NONE && io2t == CTYPE_NONE) {
			if (io1t == CTYPE_ADC) {
				mappedChannels[i] = parsedChannels[io1];
			}
			else {
				mappedChannels[i] = bitRead(IOExpanderBits, io1) ? 2000 : 1000;
			}
		}
		else if (io1t == CTYPE_IO && io2t == CTYPE_IO) {
			bool b1 = bitRead(IOExpanderBits, io1);
			bool b2 = bitRead(IOExpanderBits, io2);
			if (!b1 && !b2) {
				mappedChannels[i] = 1500;
			}
			else if (b1 && !b2) {
				mappedChannels[i] = 2000;
			}
			else if (!b1 && b2) {
				mappedChannels[i] = 1000;
			}
			else {
				Serial.printf("CH%d invalid config. IO1 and IO2 both high");
			}
		}
		else {
			Serial.printf("CH Mapping for %d invalid. IOType1 %d Type2 %d\n", i, io1t, io2t); // Yes this is spammy
		}
		if (bitRead(settings.model[settings.activeModel].channelReversed, i)) {
			int16_t tempVal = (mappedChannels[i] - 3000) * -1;
			mappedChannels[i] = tempVal;
		}
		//mappedChannels[i] += outputMode;
	}

	//for (channelMixStruct channel_mixing : settings.model[settings.activeModel].channelMixing)
	//{
	//	if(channel_mixing.dest1 != 0 && channel_mixing.dest2 != 0 && channel_mixing.source1 != 0 && channel_mixing.source2 != 0)
	//	{
	//		mixChannels(mappedChannels[channel_mixing.source1], mappedChannels[channel_mixing.source2], &mappedChannels[channel_mixing.dest1], &mappedChannels[channel_mixing.dest2], MixTypes::AddSubtract);
	//	}
	//}


	if (between(fixedChannelValue, 1000, 2000)) {
		for (int i = 0; i < 24; i++) mappedChannels[i] = fixedChannelValue;
	}
	// We can only send the 24 channels if it are 10 bit values so we need to subtract 1000 to get a range from 0 to 1000
	transmitterData.ch_data.channel1 = mappedChannels[0] != 0 ? (mappedChannels[0] - 1000) : 1023;
	transmitterData.ch_data.channel2 = mappedChannels[1] != 0 ? (mappedChannels[1] - 1000) : 1023;
	transmitterData.ch_data.channel3 = mappedChannels[2] != 0 ? (mappedChannels[2] - 1000) : 1023;
	transmitterData.ch_data.channel4 = mappedChannels[3] != 0 ? (mappedChannels[3] - 1000) : 1023;
	transmitterData.ch_data.channel5 = mappedChannels[4] != 0 ? (mappedChannels[4] - 1000) : 1023;
	transmitterData.ch_data.channel6 = mappedChannels[5] != 0 ? (mappedChannels[5] - 1000) : 1023;
	transmitterData.ch_data.channel7 = mappedChannels[6] != 0 ? (mappedChannels[6] - 1000) : 1023;
	transmitterData.ch_data.channel8 = mappedChannels[7] != 0 ? (mappedChannels[7] - 1000) : 1023;
	transmitterData.ch_data.channel9 = mappedChannels[8] != 0 ? (mappedChannels[8] - 1000) : 1023;
	transmitterData.ch_data.channel10 = mappedChannels[9] != 0 ? (mappedChannels[9] - 1000) : 1023;
	transmitterData.ch_data.channel11 = mappedChannels[10] != 0 ? (mappedChannels[10] - 1000) : 1023;
	transmitterData.ch_data.channel12 = mappedChannels[11] != 0 ? (mappedChannels[11] - 1000) : 1023;
	transmitterData.ch_data.channel13 = mappedChannels[12] != 0 ? (mappedChannels[12] - 1000) : 1023;
	transmitterData.ch_data.channel14 = mappedChannels[13] != 0 ? (mappedChannels[13] - 1000) : 1023;
	transmitterData.ch_data.channel15 = mappedChannels[14] != 0 ? (mappedChannels[14] - 1000) : 1023;
	transmitterData.ch_data.channel16 = mappedChannels[15] != 0 ? (mappedChannels[15] - 1000) : 1023;
	transmitterData.ch_data.channel17 = mappedChannels[16] != 0 ? (mappedChannels[16] - 1000) : 1023;
	transmitterData.ch_data.channel18 = mappedChannels[17] != 0 ? (mappedChannels[17] - 1000) : 1023;
	transmitterData.ch_data.channel19 = mappedChannels[18] != 0 ? (mappedChannels[18] - 1000) : 1023;
	transmitterData.ch_data.channel20 = mappedChannels[19] != 0 ? (mappedChannels[19] - 1000) : 1023;
	transmitterData.ch_data.channel21 = mappedChannels[20] != 0 ? (mappedChannels[20] - 1000) : 1023;
	transmitterData.ch_data.channel22 = mappedChannels[21] != 0 ? (mappedChannels[21] - 1000) : 1023;
	transmitterData.ch_data.channel23 = mappedChannels[22] != 0 ? (mappedChannels[22] - 1000) : 1023;
	transmitterData.ch_data.channel24 = mappedChannels[23] != 0 ? (mappedChannels[23] - 1000) : 1023;
}

#pragma region IRQ functions

void setCalibrateIRQFlag()
{
	vTaskNotifyGiveFromISR(cal_taskHandle,NULL);
}

void setIOExpanderIRQFlas() {
	vTaskNotifyGiveFromISR(io_taskHandle, NULL);
}

void setEncoderIRQFlag()
{
	vTaskNotifyGiveFromISR(encoder_taskHandle, NULL);
}

void setNrfIRQFlag() {
	vTaskNotifyGiveFromISR(nRFData_taskHandle, NULL);
}

#pragma endregion

void SendData(uint8_t* data, uint8_t dataSize) {
	radioStats.send++;
	if (xSemaphoreTake(nrf_mutex, 7 / portTICK_RATE_MS) == pdFALSE) {
		Serial.println("SendData FATAL: Failed to take mutex");
	}
	else {
		uint8_t fifoStatus;
		uint32_t counter = 0;
		do {
			fifoStatus = nRF24_GetStatus_TXFIFO();
			if (fifoStatus != nRF24_STATUS_TXFIFO_EMPTY) {
				nRF24_CE_H(); // Buffer not empty yet trigger retransmit
				delayMicroseconds(15);
				nRF24_CE_L();
			}
			else if(fifoStatus == nRF24_STATUS_TXFIFO_FULL) {
				Serial.println("TXFULL. We do not want that");
				Error_Handler();
			}
			else {
				break;
			}
		} while (++counter < 5);
		//Serial.print("Sending");

		nRF24_CE_L();

		// Transfer a data from the specified buffer to the TX FIFO
		nRF24_WritePayload(data, dataSize);

		// Start a transmission by asserting CE pin (must be held at least 10us)
		nRF24_CE_H();

		delayMicroseconds(15);

		nRF24_CE_L(); // Pull it low

		prevSendTime = micros();
		xSemaphoreGive(nrf_mutex);
	}
}

void parseReceivednRFPacket() {
	while (true){
		uint8_t buf[32];
		uint8_t length = 0;
		nRF24_RXResult pipeLine = nRF24_ReadPayloadDpl(buf, &length);
		if (pipeLine == nRF24_RX_EMPTY) 
			return; // Nothing left in buffer.
		if (length == 6) {
			//Serial.printf("%s Message size '%d'. Data: ", isTransmitter ? "ACK" : "Message", length);
			//for (int i = 0; i < length; i++) {
			//	Serial.printf(" %02d ", buf[i]);
			//}
			//Serial.println();
		}
		else {
			//Serial.printf("nRF_SIZE %d\r\n", length);
			//if (length == 32) {
			memmove(receiverData.bytesUnion.u8, buf, length);
			uint8_t packetId = receiverData.packetId.id;
			switch (packetId) {
			case SETTINGSDATAID:
				//Serial.printf("SETTINGSACK");
				allowSettingsSend = true;
				settingsAckValue = receiverData.settingsDataAck.settingsPacket;
				break;
			}
		}
	} 
}

void loadSettings()
{
	Serial.print("Settings size is ");
	Serial.println(sizeof(settings));
	eeRead(0, settings);
	if (settings.version != SETTINGSVERSION)
	{
		Serial.printf("Settings are not correct. Current version %d, expected version %d\r\nDo you want to reset settings?\r\n", settings.version, SETTINGSVERSION);
		int count = 0;
		int oriTimeout = Serial.getTimeout();
		Serial.setTimeout(5000); // 5 seconds timeout
		String serialRead = Serial.readStringUntil('\n');
		Serial.setTimeout(oriTimeout);
		Serial.printf("Read '%s'\r\n", serialRead.c_str());
		if (!serialRead.startsWith("y")) return;
		Serial.println("Recreating default settings");
		for (int i = 0; i < ADCCHANNELNUMBERS; i++)
		{
			settings.model[0].channel_settings[i].chMin = 0;
			settings.model[0].channel_settings[i].chMid = 0;
			settings.model[0].channel_settings[i].chMax = 1023;
			settings.model[0].channel_settings[i].chOffset = 0;
			settings.model[0].channelMixing[i].source1 = 0;
			settings.model[0].channelMixing[i].source2 = 0;
			settings.model[0].channelMixing[i].dest1 = 0;
			settings.model[0].channelMixing[i].dest2 = 0;
		}
		for (int i = 0; i < 24; i++)
		{
			settings.model[0].channel_settings[i].channelMapping[0].type = 0;
			settings.model[0].channel_settings[i].channelMapping[1].type = 0;
			settings.model[0].channel_settings[i].channelMapping[0].index = 0;
			settings.model[0].channel_settings[i].channelMapping[1].index = 0;
		}
		settings.model[0].deadzone = 30;
		settings.model[0].encoderSettings[0].minValue = 0;
		settings.model[0].encoderSettings[0].maxValue = 10;
		settings.model[0].encoderSettings[0].curValue = 1;
		settings.model[0].encoderSettings[0].steps = 1;
		settings.model[0].encoderSettings[0].division = 1;
		settings.model[0].encoderSettings[1].minValue = -105;
		settings.model[0].encoderSettings[1].maxValue = 105;
		settings.model[0].encoderSettings[1].curValue = 5;
		settings.model[0].encoderSettings[1].steps = 1;
		settings.model[0].encoderSettings[1].division = 10;

		for (int i = 1; i < 8; i++)
		{
			settings.model[i] = settings.model[0];
		}
		settings.version = SETTINGSVERSION;
		settings.activeModel = 0;
		saveSettings();
	}
}

void PrintCalValues()
{
	//buttonValues = random(0, UINT16_MAX);
	Serial.println("ch\tmin\tmid\tmax\toffset\tdefault\tIO1\tIO2");
	for (int i = 0; i < 24; i++)
	{
		auto chSetting = settings.model[settings.activeModel].channel_settings[i];
		Serial.printf("ch%d\t%04d\t%04d\t%04d\t%04d\t%04d\t%s%02d\t%s%02d\r\n",
			i + 1, chSetting.chMin, chSetting.chMid, chSetting.chMax, chSetting.chOffset, chSetting.chDefaults,
			chSetting.channelMapping[0].type == 0 ? "NONE" : chSetting.channelMapping[0].type == 1 ? "IO" : "ADC", chSetting.channelMapping[0].index,
			chSetting.channelMapping[1].type == 0 ? "NONE" : chSetting.channelMapping[1].type == 1 ? "IO" : "ADC", chSetting.channelMapping[1].index
		);
	}
	Serial.println();
}

#pragma region setup hardware

void configureEncoder()
{
	if (!encoder.begin(i2cEncoderLibV2::INT_DATA | i2cEncoderLibV2::WRAP_DISABLE | i2cEncoderLibV2::DIRE_RIGHT | i2cEncoderLibV2::IPUP_DISABLE | i2cEncoderLibV2::RMOD_X1 | i2cEncoderLibV2::STD_ENCODER)) {
		Serial.println("Failed to init encoder");
	}
	encoder.writeCounter(settings.model[settings.activeModel].encoderSettings[encoderSettingsIndex].curValue); /* Reset the counter value */
	encoder.writeMax(settings.model[settings.activeModel].encoderSettings[encoderSettingsIndex].maxValue); /* Set the maximum threshold*/
	encoder.writeMin(settings.model[settings.activeModel].encoderSettings[encoderSettingsIndex].minValue); /* Set the minimum threshold */
	encoder.writeStep(settings.model[settings.activeModel].encoderSettings[encoderSettingsIndex].steps); /* Set the step to 1*/
	encoder.writeInterruptConfig(0xff); /* Enable all the interrupt */
	encoder.writeAntibouncingPeriod(20);  /* Set an anti-bouncing of 20ms */
	encoder.writeDoublePushPeriod(50);  /*Set a period for the double push of 500ms */
	pinMode(ENCODER_INT_PIN, INPUT_PULLUP);
	attachInterrupt(ENCODER_INT_PIN, setEncoderIRQFlag, FALLING);
}

void setupMCPChips() {

	pinMode(CALEXPENDER_INT_PIN, INPUT_PULLUP);				// Expender Interupt pin
	pinMode(IOEXPENDER_INT_PIN, INPUT_PULLUP);				// IO twoway/oneway IRQ pin

	Serial.printf("Twoway %s OneWay %s Calc %s\n", I2CDeviceConnected(&Wire, 0x20 + IOEXPANDER1_ADDR) ? "found" : "not found", I2CDeviceConnected(&Wire, 0x20 + IOEXPANDER2_ADDR) ? "found" : "not found", I2CDeviceConnected(&Wire, 0x20 + CALEXPENDER_ADDR) ? "found" : "not found");

	while (!I2CDeviceConnected(&Wire, 0x20 + IOEXPANDER1_ADDR)) {
		Serial.println("IOEXPANDER1 not found");
		digitalWrite(LED_BUILTIN, LOW);
		delay(500);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(500);
	}
	IOExpander1.begin(IOEXPANDER1_ADDR, &Wire);
	IOExpander1.writeRegister(MCP23017_IODIRA, 0xFF);   // IO TO INPUT.writeRegister(MCP23017_IODIRA, 0xFF);   // IO TO INPUT
	IOExpander1.writeRegister(MCP23017_IODIRB, 0xFF);
	IOExpander1.writeRegister(MCP23017_GPPUA, 0xFF);	// ENABLE PULLUP.writeRegister(MCP23017_GPPUA, 0xFF);	// ENABLE PULLUP
	IOExpander1.writeRegister(MCP23017_GPPUB, 0xFF);
	IOExpander1.writeRegister(MCP23017_IPOLA, 0xFF);  // ENABLE REVERSING OF IO. DOES THIS FIX A BUG?
	IOExpander1.writeRegister(MCP23017_IPOLB, 0xFF);
	IOExpander1.setupInterrupts(true, true, LOW);
	IOExpander1.writeRegister(MCP23017_GPINTENA, 0xFF);  // Enable IRQ
	IOExpander1.writeRegister(MCP23017_GPINTENB, 0xFF);

	while (!I2CDeviceConnected(&Wire, 0x20 + IOEXPANDER2_ADDR)) {
		Serial.println("IOExpander2 not found");
		digitalWrite(LED_BUILTIN, LOW);
		delay(500);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(500);
	}

	IOExpander2.begin(IOEXPANDER2_ADDR, &Wire);
	IOExpander2.writeRegister(MCP23017_IODIRA, 0xFF);   // IO TO INPUT.writeRegister(MCP23017_IODIRA, 0xFF);   // IO TO INPUT
	IOExpander2.writeRegister(MCP23017_IODIRB, 0xFF);
	IOExpander2.writeRegister(MCP23017_GPPUA, 0xFF);	// ENABLE PULLUP.writeRegister(MCP23017_GPPUA, 0xFF);	// ENABLE PULLUP
	IOExpander2.writeRegister(MCP23017_GPPUB, 0xFF);
	IOExpander2.writeRegister(MCP23017_IPOLA, 0xFF);  // ENABLE REVERSING OF IO. DOES THIS FIX A BUG?
	IOExpander2.writeRegister(MCP23017_IPOLB, 0xFF);
	IOExpander2.setupInterrupts(true, true, LOW);
	IOExpander2.writeRegister(MCP23017_GPINTENA, 0xFF);  // Enable IRQ
	IOExpander2.writeRegister(MCP23017_GPINTENB, 0xFF);

	calButtonExpender.begin(CALEXPENDER_ADDR, &Wire);
	while (!I2CDeviceConnected(&Wire, 0x20 + CALEXPENDER_ADDR))
	{
		Serial.println("Calibrate button expander not found");
		digitalWrite(LED_BUILTIN, LOW);
		delay(500);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(500);
	}
	calButtonExpender.setupInterrupts(true, true, LOW);
	calButtonExpender.writeRegister(MCP23017_IODIRA, 0xFF);   // IO TO INPUT.writeRegister(MCP23017_IODIRA, 0xFF);   // IO TO INPUT
	calButtonExpender.writeRegister(MCP23017_IODIRB, 0xFF);
	calButtonExpender.writeRegister(MCP23017_GPPUA, 0xFF);	// ENABLE PULLUP.writeRegister(MCP23017_GPPUA, 0xFF);	// ENABLE PULLUP
	calButtonExpender.writeRegister(MCP23017_GPPUB, 0xFF);
	calButtonExpender.writeRegister(MCP23017_IPOLA, 0xFF);  // ENABLE REVERSING OF IO. DOES THIS FIX A BUG?
	calButtonExpender.writeRegister(MCP23017_IPOLB, 0xFF);
	calButtonExpender.writeRegister(MCP23017_GPINTENA, 0xFF);  // Enable IRQ
	calButtonExpender.writeRegister(MCP23017_GPINTENB, 0xFF);
	calButtonExpender.readGPIOAB(); // Clearing any interrupts that may be active

	attachInterrupt(CALEXPENDER_INT_PIN, setCalibrateIRQFlag, FALLING);
	attachInterrupt(IOEXPENDER_INT_PIN, setIOExpanderIRQFlas, FALLING);
}

#pragma endregion

#pragma region SerialControl Functions

void transmitSettingsToRX() {
	vTaskSuspend(nrfTransit_taskHandle);
	//p_transmittingSettings.navigateTo();
	double settingsSizeAmountD = sizeof(Settings) / (double)SETTINGSDATASIZE;
	uint16_t settingsSizeAmount = (uint16_t)settingsSizeAmountD;
	uint8_t settingsModulo = sizeof(Settings) % SETTINGSDATASIZE;
	uint8_t* settingsPtr = (uint8_t*)&settings;

	Serial.printf("Transmitting settings to RX. Settings size %d. Settings packets %d(%5.2f) rest %d. Settings / 4 %f\n", sizeof(Settings), settingsSizeAmount, settingsSizeAmountD, settingsModulo, sizeof(Settings) / 4.0);
	int counter = 0;
	// Main CRC
	uint32_t settingscrc = HAL_CRC_Calculate(&hcrc, (uint32_t*)settingsPtr, sizeof(Settings) / 4);

	// start header packet
	memset(transmitterData.bytesUnion.u8, 0, 32);
	transmitterData.bytesUnion.u8[0] = SETTINGSDATASETUPID;
	transmitterData.bytesUnion.u8[1] = settingsSizeAmount >> 8;
	transmitterData.bytesUnion.u8[2] = settingsSizeAmount & 0xFF;
	transmitterData.bytesUnion.u8[3] = settingsModulo;
	uint16_t crc = gencrc(transmitterData.bytesUnion.u8, RFPACKETLENGTH - 2);
	transmitterData.settingsData.crc = crc;
	allowSettingsSend = false;
	counter = 0;
	int maxCounterVal = 200;
	int warningCounterVal = 10;


	//Serial.print("Header packet: ");
	//for (int b = 0; b < 32; b++) {
	//	Serial.printf("0x%02X ", transmitterData.bytesUnion.u8[b]);
	//}
	//Serial.println();
	do {
		SendData(transmitterData.bytesUnion.u8, 32);
		vTaskDelay(10);
	} while (!allowSettingsSend && ++counter < maxCounterVal);
	if (counter >= maxCounterVal) {
		Serial.println("Failed to transmit settingsheader");
		Error_Handler();
	}
	if (counter >= warningCounterVal) Serial.printf("SettingsTX To long. c %d\r\n", counter);
	// End header packet

	// Start data packets
	for (int i = 0; i < settingsSizeAmount; i++) {
		memset(transmitterData.bytesUnion.u8, 0, 32); // Clear mem
		transmitterData.settingsData.id = SETTINGSDATAID;
		transmitterData.settingsData.packetNumber = i;
		uint8_t* txsdPtr = (uint8_t*)&transmitterData.settingsData.data;
		memcpy(txsdPtr, settingsPtr, SETTINGSDATASIZE);
		crc = gencrc(transmitterData.bytesUnion.u8, RFPACKETLENGTH - 2);
		transmitterData.settingsData.crc = crc;
		settingsPtr += SETTINGSDATASIZE;
		allowSettingsSend = false;
		counter = 0;
		if (i % 40 == 0) {
			char buf[52];
			sprintf(buf, "Currently at packet %d of %d", i, settingsSizeAmount);
			e_settingstxtorxprogress.setValue(buf);
		}
		//Serial.printf("packet_%d: ", i);
		//for (int b = 0; b < 32; b++) {
		//	Serial.printf("0x%02X ", transmitterData.bytesUnion.u8[b]);
		//}
		//Serial.println();
		do {
			SendData(transmitterData.bytesUnion.u8, 32);
			vTaskDelay(10);
			if (allowSettingsSend) {
				if (settingsAckValue != i) {
					//Serial.printf("Wrong settings ack. Got %d want %d\r\n", settingsAckValue, i);
				}
				else if (settingsAckValue == i) {
					break;
				}
			}
		} while (++counter < maxCounterVal);
		if (counter >= maxCounterVal) {
			Serial.printf("Failed to transmit settings packet %d. %d packets remaining\r\n", i, settingsSizeAmount - i);
			Error_Handler();
		}
		if (counter >= warningCounterVal) Serial.printf("SettingsTX To long. c %d\r\n", counter);
	}
	// End data packets

	// Start modulo packet
	transmitterData.settingsData.id = SETTINGSDATAID;
	transmitterData.settingsData.packetNumber = settingsSizeAmount;

	uint8_t* txsdPtr = (uint8_t*)&transmitterData.settingsData.data;
	memset(txsdPtr, 0, SETTINGSDATASIZE);
	counter = 0;
	if (settingsModulo != 0) { // Transmit last packet
		memcpy(txsdPtr, settingsPtr, settingsModulo);
	}
	crc = gencrc(transmitterData.bytesUnion.u8, RFPACKETLENGTH - 2);
	transmitterData.settingsData.crc = crc;

	allowSettingsSend = false;

	//Serial.print("modulo packet: ");
	//for (int b = 0; b < 32; b++) {
	//	Serial.printf("0x%02X ", transmitterData.bytesUnion.u8[b]);
	//}
	//Serial.println();
	do {
		SendData(transmitterData.bytesUnion.u8, 32);
		if (allowSettingsSend) {
			if (settingsAckValue != transmitterData.settingsData.packetNumber) {
				//Serial.printf("Wrong settings ack. Got %d want %d\r\n", settingsAckValue, transmitterData.bytesUnion.u8[1]);
			}
			else if (settingsAckValue == transmitterData.settingsData.packetNumber) {
				break;
			}
		}
		vTaskDelay(10);
	} while (++counter < maxCounterVal);
	if (counter >= maxCounterVal) Error_Handler();
	if (counter >= warningCounterVal) Serial.printf("SettingsTX To long. c %d\r\n", counter);
	counter = 0;
	// End modulo packet
	
	// Start finish packet
	memset(&transmitterData.bytesUnion.u8, 0, 32);
	transmitterData.settingsData.id = SETTINGSDATAID;
	transmitterData.settingsData.packetNumber = settingsSizeAmount + 1;
	transmitterData.bytesUnion.u32[1] = settingscrc;
	crc = gencrc(transmitterData.bytesUnion.u8, RFPACKETLENGTH - 2);
	transmitterData.settingsData.crc = crc;
	//Serial.printf("SettingsCRC %u\r\n", crc);
	allowSettingsSend = false;

	//Serial.print("Final packet: ");
	//for (int b = 0; b < 32; b++) {
	//	Serial.printf("0x%02X ", transmitterData.bytesUnion.u8[b]);
	//}
	//Serial.println();
	do {
		SendData(transmitterData.bytesUnion.u8, 32);
		if (allowSettingsSend) {
			if (settingsAckValue != transmitterData.settingsData.packetNumber) {
				//Serial.printf("Wrong settings ack. Got %d want %d\r\n", settingsAckValue, transmitterData.bytesUnion.u8[1]);
			}
			else if (settingsAckValue == transmitterData.settingsData.packetNumber) {
				break;
			}
		}
		vTaskDelay(10);
	} while (++counter < maxCounterVal);
	if (counter >= maxCounterVal) Error_Handler();
	if (counter >= warningCounterVal) Serial.printf("SettingsTX To long. c %d\r\n", counter);
	// End finish packet

	Serial.println("Finished transmitting settings");
	//p_transmittingSettings.close();
	vTaskResume(nrfTransit_taskHandle);
}

void wipeEeprom() {
	memset(&settings, 0, sizeof(settings));
	saveSettings();
}

void resetMCU() {
	NVIC_SystemReset();
}

void setTransmitTest() {
	transmitTest = !transmitTest;
	if (transmitTest) {
		vTaskResume(nrfTransmitTest_taskHandle);
		vTaskSuspend(nrfTransit_taskHandle);
	}
	else {
		vTaskSuspend(nrfTransmitTest_taskHandle);
		vTaskResume(nrfTransit_taskHandle);
	}
}

#pragma endregion

#pragma region FreeRTOS tasks

void nrfTransmitChannels(void* parameter)
{
	while (true) {
		updateValues();
		transmitterData.ch_data.identifier = CHANNELDATAID;
		SendData(transmitterData.bytesUnion.u8, sizeof(transmitterData));
		vTaskDelay(7 / portTICK_RATE_MS);
	}
}

void nrfTransmitTest(void* parameter) {
	while (true) {
		uint32_t now = millis();
		lastMessageSend = now;
		uint8_t txBuf[32];
		txBuf[0] = 1;
		txBuf[1] = 0;
		txBuf[2] = now >> 24 & 0xFF;
		txBuf[3] = now >> 16 & 0xFF;
		txBuf[4] = now >> 8 & 0xFF;
		txBuf[5] = now >> 0 & 0xFF;
		Serial.printf("Sending message with time %d\n", now);

		nRF24_CE_L();

		// Transfer a data from the specified buffer to the TX FIFO
		nRF24_WritePayload(txBuf, 6);

		// Start a transmission by asserting CE pin (must be held at least 10us)
		nRF24_CE_H();

		delayMicroseconds(10);
		nRF24_CE_L();
		vTaskDelay(1000 / portTICK_RATE_MS);
	}
}

void check_radio(void* parameters)
{
	while (true) {
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		if (xSemaphoreTake(nrf_mutex, 7 / portTICK_RATE_MS) == pdFALSE) {
			Serial.println("CHECKRADIO: nRF_BUSY");
		}
		else {
			bool tx, fail, rx;
			uint8_t status = nRF24_GetIRQFlags();
			tx = (status & nRF24_FLAG_TX_DS) != 0;
			fail = (status & nRF24_FLAG_MAX_RT) != 0;
			rx = (status & nRF24_FLAG_RX_DR) != 0;
			uint8_t fifoStatus = nRF24_GetStatus_TXFIFO();
			if (fifoStatus == nRF24_STATUS_TXFIFO_EMPTY) {
				nRF24_CE_L(); // All packets transmitted
			}

			if (tx) {
				radioStats.txack++;
				//if(debugging) Serial.println("TXOK");
			}
			if (fail) { // TXFail
				radioStats.fail++;
				//if (debugging) Serial.println("TXFERR");
			}

			if (rx) {                      // Did we receive a message?
				radioStats.rx++;
				parseReceivednRFPacket();
			}
			nRF24_ClearIRQFlags();
			xSemaphoreGive(nrf_mutex);
		}
	}
}

void printNrfStats(void* parameter) {
	while (true) {
		Serial.printf("NRFStats: TX %7d ACK %7d RX %7d FAIL %7d\r\n", radioStats.send, radioStats.txack, radioStats.rx, radioStats.fail);
		vTaskDelay(1000 / portTICK_RATE_MS);
	}
}

uint32_t lastHMIRefresh = 0;
void updateHMITask(void* parameter) {
	while (true) {
		if (xSemaphoreTake(hmi_mutex, 10 / portTICK_RATE_MS) == pdFALSE) {
			Serial.println("updateHMITask failed to get mutex");
		}
		else {
			HMI.loop(hmiObjects);
			if (HMI.getCurrentPageId() == HMIPageElems::calibrations) { // CalibratePage
				calDispObjs[sendChannel][0]->setValue(rawChannels[sendChannel]);
				calDispObjs[sendChannel][1]->setValue(parsedChannels[sendChannel]);
				sendChannel++;
				if (sendChannel == ADCCHANNELNUMBERS) {
					sendChannel = 0;
				}
			}
			if (HMI.getCurrentPageId() == HMIPageElems::setupChannel) {
				if (detectingIO != 0 && !detectingChannelsSet) {
					detectingChannelsSet = true;
					memcpy(detectingRawChannels, rawChannels, ADCCHANNELNUMBERS * 2);
				}
				if (detectingIO != 0) {
					for (int8_t i = 0; i < 12; i++) {
						if (abs((int16_t)detectingRawChannels[i] - (int16_t)rawChannels[i]) > 200) {
							auto str = String("Detected ADC ");
							str.concat(i);
							Serial.printf("ADCDETECT: %s\n", str.c_str());
							if (detectingIO == 1) {
								detectedIO1.type = CTYPE_ADC;
								detectedIO1.index = i;
								e_detectIO1.setValue(str.c_str());
							}
							else if (detectingIO == 2) {
								Serial.printf("INVALID");
								e_detectIO2.setValue("INVALID");
							}
							detectingChannelsSet = false;
							detectingIO = 0;
						}
					}
				}
				if (settings.model[settings.activeModel].channel_settings[channelToEditIdx].channelMapping[0].type != CTYPE_NONE ||
					settings.model[settings.activeModel].channel_settings[channelToEditIdx].channelMapping[1].type != CTYPE_NONE) {
						e_channelval.setValue(mappedChannels[channelToEditIdx]);
				}
			}
			if (HMI.getCurrentPageId() == HMIPageElems::DisplayRcValues) {
				DispDispObjs[sendChannel]->setValue(mappedChannels[sendChannel]);
				sendChannel++;
				if (sendChannel == 24) {
					sendChannel = 0;
				}
			}
			if (HMI.getCurrentPageId() == HMIPageElems::DisplayRawValues) {
				if (sendChannel < 10) {
					rawDispObjs[sendChannel]->setValue(rawChannels[sendChannel]);
				}
				else if (sendChannel == 10) {
					char buffer[33];
					for (int i = 0; i < 32; i++) buffer[31 - i] = '0' + ((prevIOExpanderBits & (1 << i)) > 0);
					buffer[32] = '\0';
					rawDispObjs[sendChannel]->setValue(buffer);
				}
				else if (sendChannel == 11) {
					char buffer[33];
					for (int i = 0; i < 32; i++) buffer[31 - i] = '0' + ((IOExpanderBits & (1 << i)) > 0);
					buffer[32] = '\0';
					rawDispObjs[sendChannel]->setValue(buffer);
				}
				sendChannel++;
				if (sendChannel == 12) {
					sendChannel = 0;
				}
			}
			if (millis() - lastHMIRefresh > 5000) {

				switch (HMI.getCurrentPageId()) {
				case HMIPageElems::calibrations:
				case HMIPageElems::DisplayRawValues:
				case HMIPageElems::DisplayRcValues:
					HMI.refreshDisplay();
					break;
				}
				lastHMIRefresh = millis();
			}
			xSemaphoreGive(hmi_mutex);
		}
		vTaskDelay(10 / portTICK_PERIOD_MS); // Delay 10 ms
	}
}

void processIOInterrupt(void* parameter) {
	while (true) {
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		IOExpanderBits = (IOExpander1.readGPIOAB() << 16) | IOExpander2.readGPIOAB();
		if (IOExpanderBits != prevIOExpanderBits) {
			Serial.print("IOExpander IRQ. ");
			printBits(&Serial, IOExpanderBits, false);
			Serial.print(" Changed bits: ");
			for (int b = 0; b < 32; b++) {
				if (bitRead(prevIOExpanderBits, b) != bitRead(IOExpanderBits, b)) {
					if (bitRead(IOExpanderBits, b) && detectingIO != 0) {
						auto str = String("Detected IO ");
						str.concat(b);
						Serial.printf("IODETECT: %s\n", str.c_str());
						if (detectingIO == 1) {
							detectedIO1.type = CTYPE_IO;
							detectedIO1.index = b;
							e_detectIO1.setValue(str.c_str());
						}
						else if (detectingIO == 2) {
							detectedIO2.type = CTYPE_IO;
							detectedIO2.index = b;
							e_detectIO2.setValue(str.c_str());
						}
						detectingIO = 0;
					}
					Serial.printf("%d now %s, ", b, bitRead(IOExpanderBits, b) ? "HIGH" : "LOW");
				}
			}
			Serial.println();
		}
	}
}

void processCALInterrupt(void* parameter) {
	while (1) {
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		xSemaphoreTake(i2c_mutex, portMAX_DELAY);
		uint16_t buttons = calButtonExpender.readGPIOAB();
		//Serial.print("CAL Interrupt ");
		//printBits(&Serial, buttons, true);
		for (int i = 0; i < 6; i++)
		{
			uint8_t btn = i * 2;
			int ch = i;
			if (bitRead(buttons, btn) && bitRead(buttons, btn + 1))
			{
				Serial.printf("CH%02d offset reset\n", ch + 1);
				settings.model[settings.activeModel].channel_settings[ch].chOffset = 0;
			}
			else if (bitRead(buttons, btn) && !bitRead(lastCalButtons, btn))
			{
				settings.model[settings.activeModel].channel_settings[ch].chOffset++;
				Serial.printf("CH%02d offset ++ to %d\n", ch + 1, settings.model[settings.activeModel].channel_settings[i].chOffset);
			}
			else if (bitRead(buttons, btn + 1) && !bitRead(lastCalButtons, btn + 1))
			{
				settings.model[settings.activeModel].channel_settings[ch].chOffset--;
				Serial.printf("CH%02d offset -- to %d\n", ch + 1, settings.model[settings.activeModel].channel_settings[i].chOffset);
			}
		}
		lastCalButtons = buttons;

		xSemaphoreGive(i2c_mutex);
	}
}

void processEncoder(void* parameter) {
	while (true) {
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		xSemaphoreTake(i2c_mutex, portMAX_DELAY);
		if (encoder.updateStatus()) {
			if (encoder.readStatus(i2cEncoderLibV2::RMAX)) {
				Serial.print("Maximum threshold: ");
				Serial.println(encoder.readCounterInt());

				/* Write here your code */
			}
			else if (encoder.readStatus(i2cEncoderLibV2::RINC)) {
				Serial.print("Increment: ");
				Serial.println(encoder.readCounterInt());

				/* Write here your code */
			}

			if (encoder.readStatus(i2cEncoderLibV2::RMIN)) {
				Serial.print("Minimum threshold: ");
				Serial.println(encoder.readCounterInt());

				/* Write here your code */
			}
			else if (encoder.readStatus(i2cEncoderLibV2::RDEC)) {
				Serial.print("Decrement: ");
				Serial.println(encoder.readCounterInt());

				/* Write here your code */
			}

			if (encoder.readStatus(i2cEncoderLibV2::PUSHR)) {
				Serial.println("Push button Released");

				/* Write here your code */
			}

			if (encoder.readStatus(i2cEncoderLibV2::PUSHP)) {
				Serial.println("Push button Pressed");

				/* Write here your code */
			}

			if (encoder.readStatus(i2cEncoderLibV2::PUSHD)) {
				Serial.println("Double push!");

				/* Write here your code */

			}
		}
		xSemaphoreGive(i2c_mutex);
	}
}

void handlePlotter(void* parameter) {
	while (true) {
		Plotter.loop();
		vTaskDelay((Plotter.getTransmitInterval() + 2) / portTICK_RATE_MS);
	}
}
void handleSerialControl(void* parameter) {
	while (true) {
		scl.loop();
		vTaskDelay(10 / portTICK_RATE_MS);
	}
}

void initFreeRTOS() {

	hmi_mutex = xSemaphoreCreateMutex();
	nrf_mutex = xSemaphoreCreateMutex();
	i2c_mutex = xSemaphoreCreateMutex();
	serial_mutex = xSemaphoreCreateMutex();

	xTaskCreate(check_radio, "checkRadio", 1024, NULL, 20, &nRFData_taskHandle);
	xTaskCreate(processCALInterrupt, "calibrate_task", 1024, NULL, 10, &cal_taskHandle);
	xTaskCreate(processIOInterrupt, "IOExpander", 1024, NULL, 10, &io_taskHandle);
	xTaskCreate(processEncoder, "encoder", 1024, NULL, 10, &encoder_taskHandle);
	xTaskCreate(handlePlotter, "plotter", 1024, NULL,1, &plotter_taskHandle);
	xTaskCreate(updateHMITask,"HMI",1024, NULL,6, &hmi_taskHandle);
	xTaskCreate(handleSerialControl,"SerialControl",1024, NULL,5, &serialControl_taskHandle);
	xTaskCreate(nrfTransmitTest,"nrfTest",1024, NULL,20, &nrfTransmitTest_taskHandle);
	vTaskSuspend(nrfTransmitTest_taskHandle);
	xTaskCreate(nrfTransmitChannels,"nrfChannels",1024, NULL,20, &nrfTransit_taskHandle);
	xTaskCreate(printNrfStats,"nrfChannels",1024, NULL,1, &printNrfStats_taskHandle);
}
#pragma endregion

void setup()
{
	uint32_t startSetup = millis();
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(PE3, INPUT_PULLDOWN);
	pinMode(BTN_K0, INPUT_PULLDOWN);
	pinMode(BTN_K1, INPUT_PULLDOWN);
	delay(50);

	if (digitalRead(PE3)) {
		transmitTest = true;
		Serial.println("TransmitTest");
	}
	digitalWrite(LED_BUILTIN, HIGH);

	//HMI.setDebugging(true);
	//HMI.setTracing(true);
	Serial.println("Starting TX");
	initHMI();
	//Serial.print("Size of channel bits ");
	initStructs();
	Wire.setSCL(PB_10);
	Wire.setSDA(PB_11);
	Wire.begin();
	Wire.setClock(400000);

	while (!I2CDeviceConnected(&Wire, 0x50)) {
		Serial.println("Something is wrong with I2C. Check wiring");
		delay(1000);
	}

	setupMCPChips();

	//scanI2C(&Wire, &Serial);

	loadSettings();

	ADCInit();

	ADCStart();

	memset(&transmitterData.bytesUnion.u8, 0, 32);
	PrintCalValues();
	configureEncoder();

	pinMode(cePin, OUTPUT);
	pinMode(csnPin, OUTPUT);
	digitalWrite(csnPin, HIGH);
	pinMode(irqPin, INPUT);
	attachInterrupt(irqPin, setNrfIRQFlag, FALLING);
	nRF24_SetCEPin(cePin);
	nRF24_SetCSNPin(csnPin);
	initSPI();
	common_nRFInit();
	// Set TX power
	nRF24_SetTXPower(nRF24_TXPWR_18dBm);

	IOExpanderBits = (IOExpander1.readGPIOAB() << 16) | IOExpander2.readGPIOAB();
	Plotter.init(&Serial1, "Raw channels", &scl);
	for (int i = 0; i < ADCCHANNELNUMBERS; i++) {
		char adcNum[10] = { 0 };
		sprintf(adcNum, "ADC%02d\0", i);
		Plotter.addPlotData(&ADCDMABuffer[i], adcNum);
	}
	PlotterLib* chPlotter = Plotter.addNewPlotter("ChannelData");

	for (int i = 1; i <= 24; i++) {
		char chNum[10] = { 0 };
		sprintf(chNum, "CH%02d\0", i);
		chPlotter->addPlotData(&mappedChannels[i], chNum);
	}
	Plotter.setPlotState(false);
	chPlotter->setPlotState(false);

	scl.init(&Serial1);
	scl.addVoidCallback("*", resetMCU);
	scl.addVoidCallback("t", setTransmitTest);
	scl.addVoidCallback("w", wipeEeprom);
	scl.addVoidCallback("s", transmitSettingsToRX);

	initFreeRTOS();
	hcrc.Instance = CRC;
	if (HAL_CRC_Init(&hcrc) != HAL_OK)
	{
		Error_Handler();
	}
	__HAL_RCC_CRC_CLK_ENABLE();
	Serial.printf("Started in %d millis\n", millis() - startSetup);
	vTaskStartScheduler();
	Serial.println("FATAL ERROR OCCURED");
	Serial.printf("Free head %d\r\n", xPortGetFreeHeapSize);
}

void loop()
{
	//Plotter.loop();
	//scl.loop();
	//if (transmitTest) {
	//	uint32_t now = millis();
	//	if (now - lastMessageSend >= 1000) {
	//	}

	//	if (gotRFData) {
	//		gotRFData = false;

	//		uint8_t buf[32];
	//		uint8_t length = 0;
	//		nRF24_RXResult pipeLine = nRF24_ReadPayloadDpl(buf, &length);

	//		Serial.printf("%s Message size '%d'. Data: ", isTransmitter ? "ACK" : "Message", length);
	//		for (int i = 0; i < length; i++) {
	//			Serial.printf(" %02d ", buf[i]);
	//		}
	//		Serial.println();
	//	}
	//	return;
	//}

	//if (refreshHMITimer.TimePassed_Seconds(5)) {
	//	refreshHMI();
	//}

	//if (updateHMITimer.TimePassed_Milliseconds(25)) {
	//	updateHMITask();
	//}

	//if (printChannelValuesTimer.TimePassed_Seconds(1) && printChannelValues) {
	//	if (printDMAValues) {
	//		Serial.print("DMA ");
	//		for (int i = 0; i < ADCCHANNELNUMBERS; i++) {
	//			Serial.printf("CH%02d %04d ", i, ADCDMABuffer[i]);
	//		}
	//		Serial.println();
	//	}
	//	else {
	//		bool printedHeader = false;
	//		int i = printADCChannels ? 0 : ADCCHANNELNUMBERS;
	//		for (printADCChannels; i < 24; i++) {
	//			if (prevRawChannels[i] == rawChannels[i]) continue;
	//			if (!printedHeader) {
	//				printedHeader = true;
	//				Serial.print("CHANGEDRAW: ");
	//			}
	//			Serial.printf("CH%02d %04d ", i + 1, rawChannels[i]);
	//		}
	//		if (printedHeader) {
	//			Serial.println();
	//		}
	//		memcpy(prevRawChannels, rawChannels, 24 * 2);
	//	}
	//}

	//HMI.loop(hmiObjects);
	//nexLoop(nex_listen_list);
	//if (encoderInterrupted)
	//{
	//	handleEncoder();
	//	encoderInterrupted = false;
	//}

	//if (calButtonsInterrupted)
	//{
	//	processCALInterrupt();
	//}
	//else if (!digitalRead(CALEXPENDER_INT_PIN))
	//{
	//	//Serial.println("Uncaught CAL interrupt");
	//	calButtonsInterrupted = true;
	//}

	//if (ioInterrupted)
	//{
	//	processIOInterrupt();
	//}
	//else if (!digitalRead(IOEXPENDER_INT_PIN)) {
	//	//Serial.println("Uncaugh IOExpander IRQ");
	//	updateIOExpander();
	//}

	//genericTimer.loop();
	//CheckBatteryAction.check();
}