// 
// 
// 
#include <GUISlice_HMI.h>
#include <i2cEncoderLibV2.h>
#include <Adafruit_MCP23008.h>
#include "ChannelFunctions.h"
#include <RF24.h>
#include <SPI.h>
#include <MyHelpers.h>
#include <Wire.h>
#include <eepromi2c_Anything.h>
#include <Adafruit_MCP23017.h>
#include <TimedAction.h>
#include "Structs.h"
//#include "HMIDisplay.h"
#include "Arduino_TX_Display_hmi.h"
#include "SharedVars.h"
#include <config.h>
#include "ADCDMAFunctions.h"

Adafruit_MCP23017 twoWayExpender, calButtonExpender;
Adafruit_MCP23008 oneWayExpender;

TwoWire Wire2 = TwoWire(PB10,PB11);
i2cEncoderLibV2 encoder(&Wire, ENCODER_ADDR);
bool encoderSettingsIndex = 0;
long prevSendTime;
TimedAction CheckBatteryAction; // Checking battery

RF24 radio = RF24(RF24CE, RF24CS); // CE CS
Settings settings;

bool sendDataFlag = false;
bool allowSend = true;
bool ioInterrupted = false;
bool calButtonsInterrupted = false;
bool encoderInterrupted = false;
bool gotRFData = false;
uint16_t buttonValues, oldButtonValues;

byte sendChannel = 0;


typedef enum { role_sender = 1, role_receiver } role_e;                 // The various roles supported by this sketch
role_e role = role_sender;                                                            // The role of the current running sketch

String serialBuffer = "";
uint16_t sendFailed = 0;
void check_radio(void)                                // Receiver role: Does nothing!  All the work is in IRQ
{
	allowSend = true;
	bool tx, fail, rx;
	radio.whatHappened(tx, fail, rx);                     // What happened?

	if (tx) {                                         // Have we successfully transmitted?
		if (role == role_sender)
		{
			if(sendFailed > 10)			sendFailed-=10;
			serialBuffer = ("Send:OK");
		}
		if (role == role_receiver) { serialBuffer = ("Ack Payload:Sent"); }
	}

	if (fail) {                                       // Have we failed to transmit?
		if (role == role_sender)
		{
			if(sendFailed != UINT16_MAX) sendFailed++;
			//serialBuffer = ("Send:Failed");
		}
		if (role == role_receiver) { Serial.println(F("Ack Payload:Failed")); }
	}

	if (rx || radio.available()) {                      // Did we receive a message?

		if (role == role_sender) {                      // If we're the sender, we've received an ack payload
			gotRFData = true;
		}


		if (role == role_receiver) {                    // If we're the receiver, we've received a time message
			// gotData = true;
		}
	}
}

// The big function. Read ADC IOExpenders and makes the radio packet
void updateValues() {


	uint16_t twoWay = twoWayExpender.readGPIOAB();
	uint8_t oneWay = oneWayExpender.readGPIO();


	// Used to not overwhelm the serialbus and slow this all down
	sendChannel++;
	if (sendChannel == CHANNELNUMBERS) sendChannel = 0;


	uint16_t tempCH[24];
	uint16_t tempCHMAPPED[24];
	memcpy(ADCDMABuffer, tempCH, 10);
	for(int i = 0; i < 16;i+=2) // Loop over twobool options
	{
		if (bitRead(twoWay, i))
		{
			tempCH[i / 2 + 8] = 1000;
		} else if(bitRead(twoWay, i + 1))
		{
			tempCH[i / 2 + 8] = 2000;
		} else
		{
			tempCH[i / 2 + 8] = 1500;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		tempCH[i+16] = bitRead(oneWay, i) ? 1000 : 2000;
	}



	//if (currentPage == 1) { // CalibratePage
		if (sendChannel == 0).setValue(tempCH[0]);
		if (sendChannel == 1)r1p1.setValue(tempCH[1]);
		if (sendChannel == 2)r2p1.setValue(tempCH[2]);
		if (sendChannel == 3)r3p1.setValue(tempCH[3]);
		if (sendChannel == 4)r4p1.setValue(tempCH[4]);
		if (sendChannel == 5)r5p1.setValue(tempCH[5]);
		if (sendChannel == 6)r6p1.setValue(tempCH[6]);
		if (sendChannel == 7)r7p1.setValue(tempCH[7]);
	//}
	//if (currentPage == 1) { // CalibratePage
		if (sendChannel == 0)o0p1.setValue(settings.model[settings.activeModel].channel_settings.chOffset[0]);
		if (sendChannel == 1)o1p1.setValue(settings.model[settings.activeModel].channel_settings.chOffset[1]);
		if (sendChannel == 2)o2p1.setValue(settings.model[settings.activeModel].channel_settings.chOffset[2]);
		if (sendChannel == 3)o3p1.setValue(settings.model[settings.activeModel].channel_settings.chOffset[3]);
		if (sendChannel == 4)o4p1.setValue(settings.model[settings.activeModel].channel_settings.chOffset[4]);
		if (sendChannel == 5)o5p1.setValue(settings.model[settings.activeModel].channel_settings.chOffset[5]);
		if (sendChannel == 6)o6p1.setValue(settings.model[settings.activeModel].channel_settings.chOffset[6]);
		if (sendChannel == 6)o7p1.setValue(settings.model[settings.activeModel].channel_settings.chOffset[7]);
	//}

	
	for (int i = 0; i < CHANNELNUMBERS; i++)
	{
		if(between(tempCH[i], settings.model[settings.activeModel].channel_settings.chMid[i] - settings.deadzone, settings.model[settings.activeModel].channel_settings.chMid[i] + settings.deadzone))
		{
			tempCH[i] = 1500;
		}
		else {
			if (tempCH[i] < settings.model[settings.activeModel].channel_settings.chMid[i])
			{
				tempCH[i] = map(tempCH[i], settings.model[settings.activeModel].channel_settings.chMin[i], settings.model[settings.activeModel].channel_settings.chMid[i], 1000, 1500);
			} 
			else
			{
				tempCH[i] = map(tempCH[i], settings.model[settings.activeModel].channel_settings.chMid[i], settings.model[settings.activeModel].channel_settings.chMax[i], 1500, 2000);
			}
		}
		tempCH[i] += settings.model[settings.activeModel].channel_settings.chOffset[i];
		tempCH[i] = constrain(tempCH[i], 1000, 2000);
	}

	for (int i = 0; i < 24; i++)
	{
		tempCHMAPPED[settings.model[settings.activeModel].channelMapping[i]] = tempCH[i];
	}

	for (channelMixStruct channel_mixing : settings.model[settings.activeModel].channelMixing)
	{
		if(channel_mixing.dest1 != 0 && channel_mixing.dest2 != 0 && channel_mixing.source1 != 0 && channel_mixing.source2 != 0)
		{
			mixChannels(tempCHMAPPED[channel_mixing.source1], tempCHMAPPED[channel_mixing.source2], &tempCHMAPPED[channel_mixing.dest1], &tempCHMAPPED[channel_mixing.dest2], MixTypes::AddSubtract);
		}
	}

	// We can only send the 24 channels if it are 10 bit values so we need to subtract 1000 to get a range from 0 to 1000
	transmitData.ch_data.channel1  = tempCHMAPPED[0]  - 1000;
	transmitData.ch_data.channel2  = tempCHMAPPED[1]  - 1000;
	transmitData.ch_data.channel3  = tempCHMAPPED[2]  - 1000;
	transmitData.ch_data.channel4  = tempCHMAPPED[3]  - 1000;
	transmitData.ch_data.channel5  = tempCHMAPPED[4]  - 1000;
	transmitData.ch_data.channel6  = tempCHMAPPED[5]  - 1000;
	transmitData.ch_data.channel7  = tempCHMAPPED[6]  - 1000;
	transmitData.ch_data.channel8  = tempCHMAPPED[7]  - 1000;
	transmitData.ch_data.channel9  = tempCHMAPPED[8]  - 1000;
	transmitData.ch_data.channel10 = tempCHMAPPED[9]  - 1000;
	transmitData.ch_data.channel11 = tempCHMAPPED[10] - 1000;
	transmitData.ch_data.channel12 = tempCHMAPPED[11] - 1000;
	transmitData.ch_data.channel13 = tempCHMAPPED[12] - 1000;
	transmitData.ch_data.channel14 = tempCHMAPPED[13] - 1000;
	transmitData.ch_data.channel15 = tempCHMAPPED[14] - 1000;
	transmitData.ch_data.channel16 = tempCHMAPPED[15] - 1000;
	transmitData.ch_data.channel17 = tempCHMAPPED[16] - 1000;
	transmitData.ch_data.channel18 = tempCHMAPPED[17] - 1000;
	transmitData.ch_data.channel19 = tempCHMAPPED[18] - 1000;
	transmitData.ch_data.channel20 = tempCHMAPPED[19] - 1000;
	transmitData.ch_data.channel21 = tempCHMAPPED[20] - 1000;
	transmitData.ch_data.channel22 = tempCHMAPPED[21] - 1000;
	transmitData.ch_data.channel23 = tempCHMAPPED[22] - 1000;
	transmitData.ch_data.channel24 = tempCHMAPPED[23] - 1000;

	if (currentPage == 1) { // CalibratePage
		if (sendChannel == 0)t0p1.setValue(transmitData.ch_data.channel1);
		if (sendChannel == 1)t1p1.setValue(transmitData.ch_data.channel2);
		if (sendChannel == 2)t2p1.setValue(transmitData.ch_data.channel3);
		if (sendChannel == 3)t3p1.setValue(transmitData.ch_data.channel4);
		if (sendChannel == 4)t4p1.setValue(transmitData.ch_data.channel5);
		if (sendChannel == 5)t5p1.setValue(transmitData.ch_data.channel6);
		if (sendChannel == 6)t6p1.setValue(transmitData.ch_data.channel7);
		if (sendChannel == 7)t7p1.setValue(transmitData.ch_data.channel8);
	}

	if (currentPage == 2) { // MainScreen
		if (sendChannel == 0) n0p2.setValue(transmitData.ch_data.channel1);
		if (sendChannel == 1) n1p2.setValue(transmitData.ch_data.channel2);
		if (sendChannel == 2) n2p2.setValue(transmitData.ch_data.channel3);
		if (sendChannel == 3) n3p2.setValue(transmitData.ch_data.channel4);
		if (sendChannel == 4) n4p2.setValue(transmitData.ch_data.channel5);
		if (sendChannel == 5) n5p2.setValue(transmitData.ch_data.channel6);
		if (sendChannel == 6) n6p2.setValue(transmitData.ch_data.channel7);
		if (sendChannel == 7) n7p2.setValue(transmitData.ch_data.channel8);
	}
}

void UpdateCalButtons()
{
	calButtonsInterrupted = true;
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
	radio.startWrite(&transmitData, sizeof(transmitData),0);
	allowSend = false;
}


void setupradio() {
	radio.begin();
	radio.setPALevel(RF24PA);
	radio.setDataRate(RF24BR);
	radio.enableAckPayload();                         // We will be using the Ack Payload feature, so please enable it
	radio.enableDynamicPayloads();                    // Ack payloads are dynamic payloads
													  // Open pipes to other node for communication
	                    // This simple sketch opens a pipe on a single address for these two nodes to 
	radio.openWritingPipe(address[0]);             // communicate back and forth.  One listens on it, the other talks to it.
	radio.openReadingPipe(1, address[1]);
	radio.printDetails();                             // Dump the configuration of the rf unit for debugging

	attachInterrupt(RF24INT, check_radio, FALLING);
}

void CheckBattery() {
	int BatteryVoltage = (ADCDMABuffer[batIndex]  * (3.3 / 1024.0)) * 2;
	// if (BatteryVoltage < 3.3) {
	// 	digitalWrite(redLedPin, HIGH);
	// }
}

void checkAndSend()
{
	updateValues();
	SendData();
}

void saveSettings()
{
	eeWrite(0, settings);
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
		for (int i = 0; i < CHANNELNUMBERS; i++)
		{
			settings.model[0].channel_settings.chMin[i] = 0;
			settings.model[0].channel_settings.chMax[i] = 4000;
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
		settings.deadzone = 0;
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
	buttonValues = random(0, UINT16_MAX);
	Serial.println("ch\tmin\tmax\toffset");
	for (int i = 0; i < CHANNELNUMBERS; i++)
	{
		Serial.printf("ch%d %04d %04d %04d\r\n", i, settings.model[settings.activeModel].channel_settings.chMin[i], settings.model[settings.activeModel].channel_settings.chMax[i], settings.model[settings.activeModel].channel_settings.chOffset[i]);
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

void setup()
{	
	pinMode(CALEXPENDER_INT_PIN, INPUT_PULLUP);						// Expender Interupt pin
	pinMode(ENCODER_INT_PIN, INPUT);						// Expender Interupt pin
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);
	Serial.begin(115200);
	initHMI();
	delay(2000);
	Serial.println("Starting TX");
	//Serial.print("Size of channel bits ");
	initStructs();
	Wire.setSCL(PB_10);
	Wire.setSDA(PB_11);
	Wire.begin();
	Wire.setClock(400000);
	Serial.printf("Twoway %s Oneway %s Calc %s\n", I2CDeviceConnected(&Wire, 0x20 + TWOWAYEXPENDER_ADDR) ? "found" : "not found", I2CDeviceConnected(&Wire, 0x20 + ONEWAYEXPENDER_ADDR) ? "found" : "not found", I2CDeviceConnected(&Wire, 0x20 + CALEXPENDER_ADDR) ? "found" : "not found");
	twoWayExpender.begin(TWOWAYEXPENDER_ADDR, &Wire);
	loadSettings();
	#pragma region MCP Initing

	twoWayExpender.begin(TWOWAYEXPENDER_ADDR, &Wire);
	while (!I2CDeviceConnected(&Wire, 0x20 + TWOWAYEXPENDER_ADDR))
	{
		Serial.println("2WayExpander not found");
		digitalWrite(LED_BUILTIN, LOW);
		delay(500);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(500);
	}

	twoWayExpender.writeRegister(MCP23017_IODIRA, 0xFF);   // IO TO INPUT
	twoWayExpender.writeRegister(MCP23017_IODIRB, 0xFF);
	twoWayExpender.writeRegister(MCP23017_GPPUA, 0xFF);	// ENABLE PULLUP
	twoWayExpender.writeRegister(MCP23017_GPPUB, 0xFF);
	twoWayExpender.writeRegister(MCP23017_IPOLA, 0xFF);  // ENABLE REVERSING OF IO. DOES THIS FIX A BUG?
	twoWayExpender.writeRegister(MCP23017_IPOLB, 0xFF);

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
	calButtonExpender.readGPIOAB(); // Clearing any interrupts that may be active
	#pragma endregion 

	ADCInit();

	ADCStart();

	memset(&transmitData.bytes, 0, 32);
	memset(&receiveData.bytes, 0, 32);
	CheckBatteryAction = TimedAction(1000 * 60, &CheckBattery);			// Check battery every minute
	PrintCalValues();
	configureEncoder();
	calButtonsInterrupted = true;
	setupradio();
	attachInterrupt(CALEXPENDER_INT_PIN, UpdateCalButtons, FALLING);
	delay(2000);
	Serial.println("Started");
}

void loop()
{
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
	if(calButtonsInterrupted)
	{
		uint16_t buttons = calButtonExpender.readGPIOAB();
		//Serial.printf("Interrupt caused by pin %d\r\n", calButtonExpender.getLastInterruptPin());
		calButtonsInterrupted = false;
		for (int i = 0; i < 4; i++)
		{
			if (bitRead(buttons, i) && bitRead(buttons, i + 4))
			{
				settings.model[settings.activeModel].channel_settings.chOffset[i] = 0;
			}
			else if (bitRead(buttons, i))
			{
				settings.model[settings.activeModel].channel_settings.chOffset[i]++;
			}
			else if (bitRead(buttons, i + 4))
			{
				settings.model[settings.activeModel].channel_settings.chOffset[i]--;
			} 
		}
		calButtonsInterrupted = false;
	} 
	else if(!digitalRead(CALEXPENDER_INT_PIN))
	{
		Serial.println("Uncaught CAL interrupt");
		calButtonsInterrupted = true;
	}
	if(!serialBuffer.equalsIgnoreCase(""))
	{
		Serial.println(serialBuffer);
		serialBuffer = "";
	}
	if(gotRFData)
	{
		radio.read(&receiveData, sizeof(receiveData));
		Serial.print("ACK: ");
		for (uint8_t data : receiveData.bytes)
		{
			Serial.printf("%03d ",data);
		}
		Serial.println();
		gotRFData = false;
	}

	if (micros() - prevSendTime >= 10000 || sendDataFlag)
	{
		if(micros() - prevSendTime >= 11000)
		{
			Serial.println("11000");
		}	
		prevSendTime = micros();
		checkAndSend();
		sendDataFlag = false;
	}
	CheckBatteryAction.check();
}