// 
// 
// 
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
//#include "HMIDisplay.h"
#include "Arduino_TX_Display_hmi.h"
#include "SharedVars.h"
#include <config.h>
#include "ADCDMAFunctions.h"
#include <ArduinoTimer.h>
#include "nrf24.h"

bool debugging = true;

Adafruit_MCP23017 twoWayExpender, calButtonExpender;
Adafruit_MCP23008 oneWayExpender;
uint16_t lastCalButtons = 0;


TwoWire Wire2 = TwoWire(PB10,PB11);
i2cEncoderLibV2 encoder(&Wire, ENCODER_ADDR);
bool encoderSettingsIndex = 0;
long prevSendTime;
TimedAction CheckBatteryAction; // Checking battery
bool printChannelValues = false;
bool printDMAValues = false;
bool printADCChannels = false;
ArduinoTimer printChannelValuesTimer;
ArduinoTimer updateHMITimer;
ArduinoTimer refreshHMITimer;

ArduinoTimer readMCPTimer; // Interrupts are broken on the chips. I will poll them instead in main loop

bool allowSend = true;
bool ioInterrupted = false;
bool calButtonsInterrupted = false;
bool ioButtonsInterrupted = false;
bool encoderInterrupted = false;
bool gotRFData = false;
uint16_t buttonValues, oldButtonValues;

byte sendChannel = 0;

uint16_t rawChannels[24];
uint16_t prevRawChannels[24];
uint16_t parsedChannels[24];
uint16_t mappedChannels[24];
uint16_t twoWay = 0;
uint8_t oneWay = 0;
bool transmitTest = false;
uint32_t lastMessageSend = 0;


String serialBuffer = "";
uint16_t sendFailed = 0;
bool tx, fail, rx;

#define BTN_K0 PE4
#define BTN_K1 PE3

BetterHardwareTimer nrfSendTim(TIM7);

HMI_Text* DispDispObjs[24]{
 &e_n0, &e_n1, &e_n2, &e_n3, &e_n4, &e_n5, &e_n6, &e_n7, &e_n8, &e_n9, 
 &e_n10, &e_n11, &e_n12, &e_n13, &e_n14, &e_n15, &e_n16, &e_n17, &e_n18, &e_n19,
 &e_n20, &e_n21, &e_n22, &e_n23
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
	int count = 0;
	while (1) {
		if (++count % 10 == 0) {
			Serial.printf("Error in file '%s' Line %d\n", file, line);
		}
		if (count == 100) HAL_NVIC_SystemReset();
		digitalToggle(LED_BUILTIN);
		delay(250);
	}
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
	nRF_hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
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

void check_radio(void)
{
	bool tx, fail, rx;
	uint8_t status = nRF24_GetIRQFlags();
	tx = (status & nRF24_FLAG_TX_DS) != 0;
	fail = (status & nRF24_FLAG_MAX_RT) != 0;
	rx = (status & nRF24_FLAG_RX_DR) != 0;
	if (tx) {
		allowSend = true; // Transmission done Allowed to send again
		//Serial.println("TXOK");
	}
	if (fail) { // TXFail
		allowSend = true; // Transmission done Allowed to send again
		//Serial.println("TXFERR");
	}

	if (rx) {                      // Did we receive a message?
		gotRFData = true;
	}
	nRF24_ClearIRQFlags();
}

// The big function. Parse all the data and create a nRF Packet
void updateValues() {
	memcpy(rawChannels, ADCDMABuffer, ADCCHANNELNUMBERS * 2);

	for (int i = 0; i < 8; i++)
	{
		rawChannels[i+ ADCCHANNELNUMBERS] = bitRead(oneWay, i) ? 1000 : 2000;
	}

	for (int i = 0; i < 12; i += 2) // Loop over twobool options
	{
		int chValue = 1500;
		if (bitRead(twoWay, i))
		{
			chValue = 1000;
		}
		else if (bitRead(twoWay, i + 1))
		{
			chValue = 2000;
		}
		rawChannels[i / 2 + ADCCHANNELNUMBERS + 8] = chValue;
	}

	memmove(parsedChannels, rawChannels, 24 * 2);

	
	for (int i = 0; i < ADCCHANNELNUMBERS; i++)
	{
		if(between(rawChannels[i], settings.model[settings.activeModel].channel_settings.chMid[i] - settings.model[0].deadzone, settings.model[settings.activeModel].channel_settings.chMid[i] + settings.model[0].deadzone))
		{
			parsedChannels[i] = 1500;
		}
		else {
			if (rawChannels[i] < settings.model[settings.activeModel].channel_settings.chMid[i])
			{
				parsedChannels[i] = map(rawChannels[i], settings.model[settings.activeModel].channel_settings.chMin[i], settings.model[settings.activeModel].channel_settings.chMid[i], 1000, 1500);
			} 
			else
			{
				parsedChannels[i] = map(rawChannels[i], settings.model[settings.activeModel].channel_settings.chMid[i], settings.model[settings.activeModel].channel_settings.chMax[i], 1500, 2000);
			}
		}
		parsedChannels[i] += settings.model[settings.activeModel].channel_settings.chOffset[i];
		parsedChannels[i] = constrain(parsedChannels[i], 1000, 2000);
	}

	for (int i = 0; i < 24; i++)
	{
		mappedChannels[settings.model[settings.activeModel].channelMapping[i]] = parsedChannels[i];
	}

	for (channelMixStruct channel_mixing : settings.model[settings.activeModel].channelMixing)
	{
		if(channel_mixing.dest1 != 0 && channel_mixing.dest2 != 0 && channel_mixing.source1 != 0 && channel_mixing.source2 != 0)
		{
			mixChannels(mappedChannels[channel_mixing.source1], mappedChannels[channel_mixing.source2], &mappedChannels[channel_mixing.dest1], &mappedChannels[channel_mixing.dest2], MixTypes::AddSubtract);
		}
	}

	// We can only send the 24 channels if it are 10 bit values so we need to subtract 1000 to get a range from 0 to 1000
	transmitData.ch_data.channel1  = mappedChannels[0]  - 1000;
	transmitData.ch_data.channel2  = mappedChannels[1]  - 1000;
	transmitData.ch_data.channel3  = mappedChannels[2]  - 1000;
	transmitData.ch_data.channel4  = mappedChannels[3]  - 1000;
	transmitData.ch_data.channel5  = mappedChannels[4]  - 1000;
	transmitData.ch_data.channel6  = mappedChannels[5]  - 1000;
	transmitData.ch_data.channel7  = mappedChannels[6]  - 1000;
	transmitData.ch_data.channel8  = mappedChannels[7]  - 1000;
	transmitData.ch_data.channel9  = mappedChannels[8]  - 1000;
	transmitData.ch_data.channel10 = mappedChannels[9]  - 1000;
	transmitData.ch_data.channel11 = mappedChannels[10] - 1000;
	transmitData.ch_data.channel12 = mappedChannels[11] - 1000;
	transmitData.ch_data.channel13 = mappedChannels[12] - 1000;
	transmitData.ch_data.channel14 = mappedChannels[13] - 1000;
	transmitData.ch_data.channel15 = mappedChannels[14] - 1000;
	transmitData.ch_data.channel16 = mappedChannels[15] - 1000;
	transmitData.ch_data.channel17 = mappedChannels[16] - 1000;
	transmitData.ch_data.channel18 = mappedChannels[17] - 1000;
	transmitData.ch_data.channel19 = mappedChannels[18] - 1000;
	transmitData.ch_data.channel20 = mappedChannels[19] - 1000;
	transmitData.ch_data.channel21 = mappedChannels[20] - 1000;
	transmitData.ch_data.channel22 = mappedChannels[21] - 1000;
	transmitData.ch_data.channel23 = mappedChannels[22] - 1000;
	transmitData.ch_data.channel24 = mappedChannels[23] - 1000;

}

void UpdateCalButtons()
{
	calButtonsInterrupted = true;
}

void updateIOExpander() {
	ioInterrupted = true;
}

void setEncoderInterruptFlag()
{
	encoderInterrupted = true;
}

void SendData() {
	// if (!allowSend) {
	// 	Serial.println("NO SEND");
	// 	return;
	// }
	//Serial.print("Sending");
	nRF24_CE_L();

	// Transfer a data from the specified buffer to the TX FIFO
	nRF24_WritePayload(transmitData.bytes, sizeof(transmitData));

	// Start a transmission by asserting CE pin (must be held at least 10us)
	nRF24_CE_H();

	delayMicroseconds(10);
	nRF24_CE_L();
	prevSendTime = micros();
}

void CheckBattery() {
	int BatteryVoltage = (ADCDMABuffer[batIndex]  * (3.3 / 1024.0)) * 2;
	// if (BatteryVoltage < 3.3) {
	// 	digitalWrite(redLedPin, HIGH);
	// }
}

//uint32_t printSendTimeModulo = 0;
uint8_t notAllowedToSendCounter = 0;
void checkAndSend()
{
	if (!allowSend && ++notAllowedToSendCounter < 10) {		
		return;
	}
	notAllowedToSendCounter = 0;
	allowSend = false;
	//Serial.printf("Millis %d\n", millis());
	//uint32_t start = micros();
	updateValues();
	SendData();
	//uint32_t stop = micros();
	//uint32_t total = stop - start;
	//printSendTimeModulo++;
	//if (printSendTimeModulo % 30 == 0) {
	//	Serial.printf("checkAndSendTime %d uS\n", total);
	//}
}

void loadSettings()
{
	Serial.print("Settings size is ");
	Serial.println(sizeof(settings));
	eeRead(0, settings);
	if(settings.version != SETTINGSVERSION)
	{
		Serial.printf("Settings are not correct. Current version %d, expected version %d\r\nReloading to clean settings\r\n", settings.version, SETTINGSVERSION);
		delay(1000);
		for (int i = 0; i < ADCCHANNELNUMBERS; i++)
		{
			settings.model[0].channel_settings.chMin[i] = 0;
			settings.model[0].channel_settings.chMid[i] = 512;
			settings.model[0].channel_settings.chMax[i] = 1023;
			settings.model[0].channel_settings.chOffset[i] = 0;
			settings.model[0].channelMixing[i].source1 = 0;
			settings.model[0].channelMixing[i].source2 = 0;
			settings.model[0].channelMixing[i].dest1 = 0;
			settings.model[0].channelMixing[i].dest2 = 0;
		}
		for(int i = 0; i < 24; i++)
		{
			settings.model[0].channelMapping[i] = i;
		}
		settings.model[0].deadzone = 0;
		settings.model[0].encoderSettings[0].minValue = 0;
		settings.model[0].encoderSettings[0].maxValue = 10;
		settings.model[0].encoderSettings[0].curValue = 1;
		settings.model[0].encoderSettings[0].steps = 1;
		settings.model[0].encoderSettings[1].division = 1;
		settings.model[0].encoderSettings[1].minValue = -105;
		settings.model[0].encoderSettings[1].maxValue = 105;
		settings.model[0].encoderSettings[1].curValue = 5;
		settings.model[0].encoderSettings[1].steps = 1;
		settings.model[0].encoderSettings[1].division = 10;

		for(int i = 1; i < 8; i++)
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
	Serial.println("ch\tmin\tmid\tmax\toffset");
	for (int i = 0; i < ADCCHANNELNUMBERS; i++)
	{
		Serial.printf("ch%d\t%04d\t%04d\t%04d\t%04d\r\n", i, settings.model[settings.activeModel].channel_settings.chMin[i], settings.model[settings.activeModel].channel_settings.chMid[i],settings.model[settings.activeModel].channel_settings.chMax[i], settings.model[settings.activeModel].channel_settings.chOffset[i]);
	}
	Serial.println();
}

void configureEncoder()
{
	encoder.begin(i2cEncoderLibV2::INT_DATA | i2cEncoderLibV2::WRAP_DISABLE | i2cEncoderLibV2::DIRE_RIGHT | i2cEncoderLibV2::IPUP_DISABLE | i2cEncoderLibV2::RMOD_X1 | i2cEncoderLibV2::STD_ENCODER);
	encoder.writeCounter(settings.model[settings.activeModel].encoderSettings[encoderSettingsIndex].curValue); /* Reset the counter value */
	encoder.writeMax(settings.model[settings.activeModel].encoderSettings[encoderSettingsIndex].maxValue); /* Set the maximum threshold*/
	encoder.writeMin(settings.model[settings.activeModel].encoderSettings[encoderSettingsIndex].minValue); /* Set the minimum threshold */
	encoder.writeStep(settings.model[settings.activeModel].encoderSettings[encoderSettingsIndex].steps); /* Set the step to 1*/
	encoder.writeInterruptConfig(0xff); /* Enable all the interrupt */
	encoder.writeAntibouncingPeriod(20);  /* Set an anti-bouncing of 200ms */
	encoder.writeDoublePushPeriod(50);  /*Set a period for the double push of 500ms */
	attachInterrupt(ENCODER_INT_PIN, setEncoderInterruptFlag, CHANGE);
}

void setupMCPChips() {

	pinMode(CALEXPENDER_INT_PIN, INPUT_PULLUP);				// Expender Interupt pin
	pinMode(IOEXPENDER_INT_PIN, INPUT_PULLUP);				// IO twoway/oneway IRQ pin

	Serial.printf("Twoway %s Oneway %s Calc %s\n", I2CDeviceConnected(&Wire, 0x20 + TWOWAYEXPENDER_ADDR) ? "found" : "not found", I2CDeviceConnected(&Wire, 0x20 + ONEWAYEXPENDER_ADDR) ? "found" : "not found", I2CDeviceConnected(&Wire, 0x20 + CALEXPENDER_ADDR) ? "found" : "not found");

	twoWayExpender.begin(TWOWAYEXPENDER_ADDR, &Wire);
	while (!I2CDeviceConnected(&Wire, 0x20 + TWOWAYEXPENDER_ADDR))
	{
		Serial.println("2WayExpander not found");
		digitalWrite(LED_BUILTIN, LOW);
		delay(500);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(500);
	}


	twoWayExpender.writeRegister(MCP23017_IODIRA, 0xFF);   // IO TO INPUT.writeRegister(MCP23017_IODIRA, 0xFF);   // IO TO INPUT
	twoWayExpender.writeRegister(MCP23017_IODIRB, 0xFF);
	twoWayExpender.writeRegister(MCP23017_GPPUA, 0xFF);	// ENABLE PULLUP.writeRegister(MCP23017_GPPUA, 0xFF);	// ENABLE PULLUP
	twoWayExpender.writeRegister(MCP23017_GPPUB, 0xFF);
	twoWayExpender.writeRegister(MCP23017_IPOLA, 0xFF);  // ENABLE REVERSING OF IO. DOES THIS FIX A BUG?
	twoWayExpender.writeRegister(MCP23017_IPOLB, 0xFF);
	twoWayExpender.setupInterrupts(true, true, LOW);
	twoWayExpender.writeRegister(MCP23017_GPINTENA, 0xFF);  // Enable IRQ
	twoWayExpender.writeRegister(MCP23017_GPINTENA, 0xFF);

	oneWayExpender.begin(ONEWAYEXPENDER_ADDR, &Wire);
	while (!I2CDeviceConnected(&Wire, 0x20 + ONEWAYEXPENDER_ADDR))
	{
		Serial.println("1WayExpander not found");
		digitalWrite(LED_BUILTIN, LOW);
		delay(500);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(500);
	}
	oneWayExpender.write8(MCP23008_IODIR, 0xFF);   // IO TO INPUT
	oneWayExpender.write8(MCP23008_GPPU, 0xFF);	// ENABLE PULLUP
	oneWayExpender.write8(MCP23008_IPOL, 0xFF);  // ENABLE REVERSING OF IO. DOES THIS FIX A BUG?
	uint8_t ioconfValue = oneWayExpender.read8(MCP23008_IOCON);
	Serial.print("MCP23008 IOCON before ");
	printBits(&Serial, ioconfValue);
	bitWrite(ioconfValue, 2, true); // Set IRQ pin as open_drain
	oneWayExpender.write8(MCP23008_IOCON, ioconfValue);
	Serial.print(" after ");

	printBits(&Serial, oneWayExpender.read8(MCP23008_IOCON), true);
	oneWayExpender.write8(MCP23008_GPINTEN, 0xFF); // Enable IRQ

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

	attachInterrupt(CALEXPENDER_INT_PIN, UpdateCalButtons, FALLING);
	attachInterrupt(IOEXPENDER_INT_PIN, updateIOExpander, FALLING);
}

void setup()
{	
	uint32_t startSetup = millis();
	Serial.begin(115200);
	pinMode(ENCODER_INT_PIN, INPUT);						// encoder Interupt pin
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(PE3, INPUT_PULLDOWN);
	pinMode(BTN_K0, INPUT_PULLDOWN);
	pinMode(BTN_K1, INPUT_PULLDOWN);
	delay(50);
	Serial.printf("K0 %d, K1 %d\n", digitalRead(BTN_K0), digitalRead(BTN_K1));

	if(digitalRead(PE3)){
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
	setupMCPChips();

	//scanI2C(&Wire, &Serial);


	loadSettings();


	ADCInit();

	ADCStart();

	memset(&transmitData.bytes, 0, 32);
	memset(&receiveData.bytes, 0, 32);
	CheckBatteryAction = TimedAction(1000 * 60, &CheckBattery);			// Check battery every minute
	PrintCalValues();
	configureEncoder();
	calButtonsInterrupted = true;

	pinMode(cePin, OUTPUT);
	pinMode(csnPin, OUTPUT);
	digitalWrite(csnPin, HIGH);
	pinMode(irqPin, INPUT);
	attachInterrupt(irqPin, check_radio, FALLING);
	nRF24_SetCEPin(cePin);
	nRF24_SetCSNPin(csnPin);
	initSPI();
	common_nRFInit();
	Serial.println("POWER IS SET TO LOW");
	nRF24_SetTXPower(nRF24_TXPWR_18dBm);
	delay(1000);
	nrfSendTim.setCount(200, HERTZ_FORMAT);
	nrfSendTim.attachInterrupt(checkAndSend);
	nrfSendTim.resume();
	Serial.printf("Started in %d millis\n", millis() - startSetup);
}

void loop()
{
	if (transmitTest) {
		uint32_t now = millis();
		if (now - lastMessageSend > 1000) {
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

			delayMicroseconds(50);
			nRF24_CE_L();

		}

		if (gotRFData) {
			gotRFData = false;

			uint8_t buf[32];
			uint8_t length = 0;
			nRF24_RXResult pipeLine = nRF24_ReadPayloadDpl(buf, &length);

			Serial.printf("%s Message size '%d'. Data: ", isTransmitter ? "ACK" : "Message", length);
			for (int i = 0; i < length; i++) {
				Serial.printf(" %02d ", buf[i]);
			}
			Serial.println();
		}
		return;
	}

	if (refreshHMITimer.TimePassed_Seconds(5)) {
		switch(HMI.getCurrentPageId()){
			case HMIPageElems::calibrations:
			case HMIPageElems::DisplayValues:
				HMI.refreshDisplay();
				break;

		}
	}

	if (updateHMITimer.TimePassed_Milliseconds(25)) {

		//sendChannel++;
		//if (sendChannel == ADCCHANNELNUMBERS) sendChannel = 0;
		//sendChannel = 9;
		if (HMI.getCurrentPageId() == HMIPageElems::calibrations) { // CalibratePage
			calDispObjs[sendChannel][0]->setText(rawChannels[sendChannel]);
			calDispObjs[sendChannel][1]->setText(parsedChannels[sendChannel]);
			sendChannel++;
			if (sendChannel == ADCCHANNELNUMBERS) {
				sendChannel = 0;
			}
		}
		if (HMI.getCurrentPageId() == HMIPageElems::DisplayValues) {
			DispDispObjs[sendChannel]->setText(mappedChannels[sendChannel]);
			sendChannel++;
			if (sendChannel == 24) {
				sendChannel = 0;
			}
		}
	}
	if (Serial.available()) {
		char c = Serial.read();
		if (c == 'c') {
			printChannelValues = !printChannelValues;
		}
		else if (c == 'r' || c == 'd') {
			printDMAValues = !printDMAValues;
		}
	}
	if(printChannelValuesTimer.TimePassed_Seconds(1) && printChannelValues) {
		if (printDMAValues) {
			Serial.print("DMA ");
			for (int i = 0; i < ADCCHANNELNUMBERS; i++) {
				Serial.printf("CH%02d %04d ", i, ADCDMABuffer[i]);
			}
			Serial.println();
		}
		else {
			bool printedHeader = false;
			int i = printADCChannels ? 0 : ADCCHANNELNUMBERS;
			for (printADCChannels; i < 24; i++) {
				if (prevRawChannels[i] == rawChannels[i]) continue;
				if (!printedHeader) {
					printedHeader = true;
					Serial.print("CHANGEDRAW: ");
				}
				Serial.printf("CH%02d %04d ", i + 1, rawChannels[i]);
			}
			if (printedHeader) {
				Serial.println();
			}
			memcpy(prevRawChannels, rawChannels, 24 * 2);
		}
	}
	HMI.loop(hmiObjects);
	//nexLoop(nex_listen_list);
	if(encoderInterrupted)
	{
		if (encoder.updateStatus()) {
			if (encoder.readStatus(i2cEncoderLibV2::RINC)) {
				Serial.print("Increment: ");
				Serial.println(encoder.readCounterByte());

				/* Write here your code */

			}
			if (encoder.readStatus(i2cEncoderLibV2::RDEC)) {
				Serial.print("Decrement: ");
				Serial.println(encoder.readCounterByte());

				/* Write here your code */

			}

			if (encoder.readStatus(i2cEncoderLibV2::RMAX)) {
				Serial.print("Maximum threshold: ");
				Serial.println(encoder.readCounterByte());

				/* Write here your code */

			}

			if (encoder.readStatus(i2cEncoderLibV2::RMIN)) {
				Serial.print("Minimum threshold: ");
				Serial.println(encoder.readCounterByte());

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
		encoderInterrupted = false;
	}
	if (calButtonsInterrupted)
	{
		uint16_t buttons = calButtonExpender.readGPIOAB();
		//Serial.print("CAL Interrupt ");
		//printBits(&Serial, buttons, true);
		calButtonsInterrupted = false;
		for (int i = 0; i < 6; i++)
		{
			uint8_t btn = i * 2;
			int ch = i;
			if (bitRead(buttons, btn) && bitRead(buttons, btn + 1))
			{
				Serial.printf("CH%02d offset reset\n",ch + 1);
				settings.model[settings.activeModel].channel_settings.chOffset[ch] = 0;
			}
			else if (bitRead(buttons, btn) && !bitRead(lastCalButtons, btn))
			{
				settings.model[settings.activeModel].channel_settings.chOffset[ch]++;
				Serial.printf("CH%02d offset ++ to %d\n",ch+1, settings.model[settings.activeModel].channel_settings.chOffset[ch]);
			}
			else if (bitRead(buttons, btn + 1) && !bitRead(lastCalButtons, btn + 1))
			{
				settings.model[settings.activeModel].channel_settings.chOffset[ch]--;
				Serial.printf("CH%02d offset -- to %d\n", ch + 1, settings.model[settings.activeModel].channel_settings.chOffset[ch]);
			}
		}
		lastCalButtons = buttons;
		calButtonsInterrupted = false;
	}
	else if (!digitalRead(CALEXPENDER_INT_PIN))
	{
		//Serial.println("Uncaught CAL interrupt");
		calButtonsInterrupted = true;
	}
	
	if (ioInterrupted)
	{
		twoWay = twoWayExpender.readGPIOAB();
		oneWay = oneWayExpender.readGPIO();
		//Serial.print("IO IRQ twoway ");
		//printBits(&Serial, twoWay, false);
		//Serial.print(" oneway ");
		//printBits(&Serial, oneWay,true);
		ioInterrupted = false;
	}
	else if (!digitalRead(IOEXPENDER_INT_PIN))
	{
		//Serial.println("Uncaught IO interrupt");
		ioInterrupted = true;
	}
	

	if(gotRFData)
	{
		uint8_t length = 0;
		nRF24_RXResult pipeLine = nRF24_ReadPayloadDpl(receiveData.bytes, &length);
		//Serial.print("ACK: ");
		//for (uint8_t data : receiveData.bytes)
		//{
		//	Serial.printf("%03d ",data);
		//}
		//Serial.println();
		gotRFData = false;
	}
	CheckBatteryAction.check();
}