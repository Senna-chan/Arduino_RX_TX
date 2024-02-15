/*
 Name:		nrf24l01Test.ino
 Created:	1/3/2022 6:57:23 PM
 Author:	Senna
*/
#include <nrf24.h>
#include <config.h>
bool gotData = false;

extern "C" void _Error_Handler(const char* file, int line) {
	Serial.printf("Error in file '%s' at line %d", file, line);
	while (1);
}




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


void check_radio(void)
{
	bool tx, fail, rx;
	uint8_t status = nRF24_GetIRQFlags();
	tx = (status & nRF24_FLAG_TX_DS) != 0;
	fail = (status & nRF24_FLAG_MAX_RT) != 0;
	rx = (status& nRF24_FLAG_RX_DR) != 0;
	Serial.print(("DS"));
	Serial.print(tx);                            // print "data sent" mask state
	Serial.print((" DF"));
	Serial.print(fail);                            // print "data fail" mask state
	Serial.print(F(" DR"));
	Serial.println(rx);                          // print "data ready" mask state
	if (tx) {                                         // Have we successfully transmitted?
		if (isTransmitter)
		{
			Serial.println("Send:OK");
		}
		if (!isTransmitter) { Serial.println("Ack Payload:Sent"); }
	}

	if (fail) {                                       // Have we failed to transmit?
		if (isTransmitter)
		{
			Serial.println("Send:Failed");
		}
		if (!isTransmitter) { Serial.println(F("Ack Payload:Failed")); }
	}

	if (rx) {                      // Did we receive a message?
		gotData = true;
	}
	nRF24_ClearIRQFlags();
}

// the setup function runs once when you press reset or power the board
void setup() {

	Serial.begin(115200);
	Serial.println("Starting nrf test");
	initSPI();
	delay(100);
	pinMode(PE2, INPUT_PULLUP);
	isTransmitter = digitalRead(PE2);
	Serial.printf("we are %s\n", isTransmitter ? "Transmitter" : "Receiver");

	pinMode(cePin, OUTPUT);
	pinMode(csnPin, OUTPUT);
	digitalWrite(csnPin, HIGH);
	pinMode(irqPin, INPUT);
	attachInterrupt(irqPin, check_radio, FALLING);
	nRF24_SetCEPin(cePin);
	nRF24_SetCSNPin(csnPin);
	common_nRFInit();
	Serial.println("Started nrf test");
}

uint32_t lastMessageSend = 0;
// the loop function runs over and over again until power down or reset
void loop() {
	uint32_t now = millis();
	if (isTransmitter) {
		if (now - lastMessageSend > 1000) {
			lastMessageSend = now;
			uint8_t txBuf[32];
			txBuf[0] = 1;
			txBuf[1] = 0;
			txBuf[2] = now >> 24 & 0xFF;
			txBuf[3] = now >> 16 & 0xFF;
			txBuf[4] = now >> 8  & 0xFF;
			txBuf[5] = now >> 0  & 0xFF;
			Serial.printf("Sending message with time %d\n", now);
			nRF24_CE_L();

			// Transfer a data from the specified buffer to the TX FIFO
			nRF24_WritePayload(txBuf, 6);

			// Start a transmission by asserting CE pin (must be held at least 10us)
			nRF24_CE_H();

			delayMicroseconds(50);
			nRF24_CE_L();
			
		}
	}
	if (gotData) {
		gotData = false;

		uint8_t buf[32];
		uint8_t length = 0;
		nRF24_RXResult pipeLine = nRF24_ReadPayloadDpl(buf, &length);

		Serial.printf("%s Message size '%d'. Data: ", isTransmitter ? "ACK" : "Message", length);
		for (int i = 0; i < length; i++) {
			Serial.printf(" %02d ", buf[i]);
		}
		Serial.println();



		if (!isTransmitter) {
			Serial.printf("Sending ACK with time %d\n", now);
			uint8_t txBuf[32];
			txBuf[0] = 0;
			txBuf[1] = 0;
			txBuf[2] = now >> 24 & 0xFF;
			txBuf[3] = now >> 16 & 0xFF;
			txBuf[4] = now >> 8 & 0xFF;
			txBuf[5] = now >> 0 & 0xFF;
			nRF24_WriteAckPayload(pipeLine, (char*)txBuf,6);
		}
  }
}
