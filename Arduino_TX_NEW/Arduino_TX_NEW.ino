/*
 Name:		WifiConfigurator.ino
 Created:	9/1/2019 12:46:55 PM
 Author:	Natsuki
*/
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <eepromi2c_Anything.h>
#include <Wire.h>
#include <EEPROM.h>
#include <SPI.h>
#include <RF24.h>
#include <TimedAction.h>
#include <RemoteDebug.h>
#include <MyHelpers.h>
#include <i2cEncoderLibV2.h>
#include <aREST.h>
#include <ArduinoJson.hpp>
#include <ArduinoJson.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_MCP23008.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "SharedVars.h"
#include "Structs.h"
#include "ChannelFunctions.h"

const char* ssid = "Natsuki-WiFi";
const char* password = "Golden-Darkness";

#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#define FREE_CORE			 1
#else
#define ARDUINO_RUNNING_CORE 1
#define FREE_CORE			 0
#endif

#define LED_BUILTIN				15	// LED PIN
#define CALEXPENDER_INT_PIN		14	// Pin on which the calibratebutton expender interrupts
#define ENCODER_INT_PIN			4	// Pin on which the encoder interrupts
#define ch1Pin					36
#define ch2Pin					39
#define ch3Pin					34
#define ch4Pin					35
#define ch5Pin					32
#define ch6Pin					33
#define ch7Pin					25
#define ch8Pin					26
#define batPin					27

uint16_t chPins[8]{ ch1Pin, ch2Pin, ch3Pin, ch4Pin, ch5Pin, ch6Pin, ch7Pin, ch8Pin };


#define RF24CE					15  //RADIO CHIP ENABLE
#define RF24CS					5 // SPI CHIP SELECT
#define RF24INT					2  

#define EEPROM_ADDRESS			0x50 // 24LC256 EEPROM Address in i2c bus 


int midDeadZone = 100;

Adafruit_MCP23017 twoWayExpender, calButtonExpender;
Adafruit_MCP23008 oneWayExpender;
i2cEncoderLibV2 encoder(0x41);
bool encoderSettingsIndex = 0;
long prevSendTime;
TimedAction CheckBatteryAction; // Checking battery

RF24 radio = RF24(RF24CE, RF24CS); // CE CS
Settings settings;
Model activeSettings;
int ch1; // speed/altitude
int ch2; // turning
int ch3; // Camera tilt/Drone forwards
int ch4; // Camera pan/Drone sideways
int ch5; // Optional channel
int ch6; // Optional channel
int ch7; // Optional channel
int ch8; // Optional channel

bool sendDataFlag = false;
bool allowSend = true;
bool ioInterrupted = false;
bool calButtonsInterrupted = false;
bool encoderInterrupted = false;
bool gotRFData = false;
uint16_t buttonValues, oldButtonValues;

byte sendChannel = 0;
AsyncWebServer server(80);

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
			if (sendFailed > 10)			sendFailed -= 10;
			serialBuffer = ("Send:OK");
		}
		if (role == role_receiver) { Serial.println(F("Ack Payload:Sent")); }
	}

	if (fail) {                                       // Have we failed to transmit?
		if (role == role_sender)
		{
			if (sendFailed != UINT16_MAX) sendFailed++;
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



	sendChannel++;
	if (sendChannel == 8) sendChannel = 0;

	uint16_t tempCH[24];
	uint16_t tempCHMAPPED[24];
	for (int i = 0; i < 8; i++)
	{
		tempCH[i] = analogRead(chPins[i]);
	}
	for (int i = 0; i < 16; i += 2) // Loop over twobool options
	{
		if (bitRead(twoWay, i))
		{
			tempCH[i / 2 + 8] = 1000;
		}
		else if (bitRead(twoWay, i + 1))
		{
			tempCH[i / 2 + 8] = 2000;
		}
		else
		{
			tempCH[i / 2 + 8] = 1500;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		tempCH[i + 16] = bitRead(oneWay, i) ? 1000 : 2000;
	}



	for (int i = 0; i < 8; i++)
	{
		if (between(tempCH[i], settings.model[settings.activeModel].channel_settings.chMid[i] - settings.deadzone, settings.model[settings.activeModel].channel_settings.chMid[i] + settings.deadzone))
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
		if (channel_mixing.dest1 != 0 && channel_mixing.dest2 != 0 && channel_mixing.source1 != 0 && channel_mixing.source2 != 0)
		{
			mixChannels(tempCHMAPPED[channel_mixing.source1], tempCHMAPPED[channel_mixing.source2], &tempCHMAPPED[channel_mixing.dest1], &tempCHMAPPED[channel_mixing.dest2]);
		}
	}

	// We can only send the 24 channels if it are 10 bit values so we need to subtract 1000 to get a range from 0 to 1000
	transmitData.ch_data.channel1 = tempCHMAPPED[0] - 1000;
	transmitData.ch_data.channel2 = tempCHMAPPED[1] - 1000;
	transmitData.ch_data.channel3 = tempCHMAPPED[2] - 1000;
	transmitData.ch_data.channel4 = tempCHMAPPED[3] - 1000;
	transmitData.ch_data.channel5 = tempCHMAPPED[4] - 1000;
	transmitData.ch_data.channel6 = tempCHMAPPED[5] - 1000;
	transmitData.ch_data.channel7 = tempCHMAPPED[6] - 1000;
	transmitData.ch_data.channel8 = tempCHMAPPED[7] - 1000;
	transmitData.ch_data.channel9 = tempCHMAPPED[8] - 1000;
	transmitData.ch_data.channel10 = tempCHMAPPED[9] - 1000;
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
	radio.startWrite(&transmitData, sizeof(transmitData), 0);
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
	int BatteryVoltage = (analogRead(batPin) * (3.3 / 4095.0)) * 2;
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
	EEPROM.put(0, settings);
	EEPROM.commit();
}

void loadSettings()
{
	Serial.print("Settings size is ");
	Serial.println(sizeof(settings));
	EEPROM.get(0, settings);
	if (settings.version != SETTINGSVERSION)
	{
		Serial.printf("Settings are not correct. Current version %d, expected version %d\r\nReloading to clean settings\r\n", settings.version, SETTINGSVERSION);
		delay(1000);
		for (int i = 0; i < 8; i++)
		{
			settings.model[0].channel_settings.chMin[i] = 0;
			settings.model[0].channel_settings.chMid[i] = 2000;
			settings.model[0].channel_settings.chMax[i] = 4000;
			settings.model[0].channel_settings.chOffset[i] = 0;
			settings.model[0].channel_settings.chDefaults[i] = 1500;
			settings.model[0].channelMixing[i].source1 = 0;
			settings.model[0].channelMixing[i].source2 = 0;
			settings.model[0].channelMixing[i].dest1 = 0;
			settings.model[0].channelMixing[i].dest2 = 0;
		}
		for (int i = 0; i < 24; i++)
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

		for (int i = 1; i < 8; i++)
		{
			settings.model[i] = settings.model[0];
		}
		settings.version = SETTINGSVERSION;
		settings.activeModel = 0;
		saveSettings();
	}
	activeSettings = settings.model[settings.activeModel];
}


void PrintCalValues()
{
	buttonValues = random(0, UINT16_MAX);
	Serial.println("ch\tmin\tmax\toffset");
	for (int i = 0; i < 8; i++)
	{
		Serial.printf("ch%d\t%04d\t%04d\t%04d\r\n", i, settings.model[settings.activeModel].channel_settings.chMin[i], settings.model[settings.activeModel].channel_settings.chMax[i], settings.model[settings.activeModel].channel_settings.chOffset[i]);
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
void notFound(AsyncWebServerRequest* request) {
	request->send(404, "text/plain", "Not found");
}

void listDir(fs::FS& fs, const char* dirname, uint8_t levels) {
	Serial.printf("Listing directory: %s\r\n", dirname);

	File root = fs.open(dirname);
	if (!root) {
		Serial.println("- failed to open directory");
		return;
	}
	if (!root.isDirectory()) {
		Serial.println(" - not a directory");
		return;
	}

	File file = root.openNextFile();
	while (file) {
		if (file.isDirectory()) {
			Serial.print("  DIR : ");
			Serial.println(file.name());
			if (levels) {
				listDir(fs, file.name(), levels - 1);
			}
		}
		else {
			Serial.print("  FILE: ");
			Serial.print(file.name());
			Serial.print("\tSIZE: ");
			Serial.println(file.size());
		}
		file = root.openNextFile();
	}
}

void networkLoop(void *parameter);
// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	delay(2000);
	Serial.println("Booting");

	if (!SPIFFS.begin(true)) {
		Serial.println("An Error has occurred while mounting SPIFFS");
		return;
	}

	Serial.println(F("Starting wifi"));
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	while (WiFi.waitForConnectResult() != WL_CONNECTED) {
		Serial.println("Connection Failed! Rebooting...");
		delay(5000);
		ESP.restart();
	}

	ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

	ArduinoOTA.begin();

	MDNS.addService("http", "tcp", 80);

	pinMode(CALEXPENDER_INT_PIN, INPUT_PULLUP);						// Expender Interupt pin
	pinMode(ENCODER_INT_PIN, INPUT);						// Expender Interupt pin
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);
	// Server Part
	

	delay(2000);
	Serial.println("Initing TX part");
	Serial.print("Size of channel bits ");
	Serial.println(sizeof(channelBitSettings));
	initStructs();
	Wire.begin();
	Wire.setClock(400000);
	scanI2C(&Wire, &Serial);
	loadSettings();
#pragma region MCP Initing

	twoWayExpender.begin(B000);
	while (!twoWayExpender.isConnected())
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

	oneWayExpender.begin(B010);
	while (!oneWayExpender.isConnected())
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

	calButtonExpender.begin(B111);
	while (!calButtonExpender.isConnected())
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

	for (uint16_t pin : chPins) // Setup channel(analog) pins
	{
		pinMode(pin, ANALOG);
	}
	pinMode(batPin, ANALOG);

	for (unsigned char& bytes : transmitData.bytes)
	{
		bytes = 0;
	}
	CheckBatteryAction = TimedAction(1000 * 60, &CheckBattery);			// Check battery every minute
	PrintCalValues();
	configureEncoder();
	calButtonsInterrupted = true;
	setupradio();
	attachInterrupt(CALEXPENDER_INT_PIN, UpdateCalButtons, FALLING);

	xTaskCreatePinnedToCore(
		networkLoop,        // function
		"Network",       // name
		2048,                 // stack
		NULL,                  // void* to input parameter
		10,                   // priority 
		NULL,                   // task handle 
		FREE_CORE
	);

	delay(2000);
	Serial.println("Started");
	Serial.println("Ready");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
}

void networkLoop(void *parameter)
{
	server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
		request->send(SPIFFS, "/index.html", String(), false);
		});

	server.on("/save_ch_setting", HTTP_POST, [](AsyncWebServerRequest* request)
		{
			int paramsNr = request->params();
			int channel = request->getParam("channel")->value().toInt();
			int type = request->getParam("type")->value().toInt();
			int value = request->getParam("value")->value().toInt();
			switch (type)
			{
			case 1: // MIN
				activeSettings.channel_settings.chMin[channel] = value;
				break;
			case 2: // MID
				activeSettings.channel_settings.chMid[channel] = value;
				break;
			case 3: // MAX
				activeSettings.channel_settings.chMax[channel] = value;
				break;
			case 4: // OFFSET
				activeSettings.channel_settings.chOffset[channel] = value;
				break;
			case 5: // DEFAULT
				activeSettings.channel_settings.chDefaults[channel] = value;
				break;
			}
			request->send(200, "text/plain", "Success");
		});

	server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest* request) {
		request->send(SPIFFS, "/style.css", "text/css");
		});
	server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest* request) {
		request->send(SPIFFS, "/script.js", "text/javascript");
		});



	server.onNotFound(notFound);

	server.begin();

	while (true)
	{
		ArduinoOTA.handle();
		delay(1);
	}
}


// the loop function runs over and over again until power down or reset
void loop() {
		if (encoderInterrupted)
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
		else if (!digitalRead(CALEXPENDER_INT_PIN))
		{
			Serial.println("Uncaught CAL interrupt");
			calButtonsInterrupted = true;
		}
		if (!serialBuffer.equalsIgnoreCase(""))
		{
			Serial.println(serialBuffer);
			serialBuffer = "";
		}
		if (gotRFData)
		{
			radio.read(&transmitData, sizeof(transmitData));
			Serial.print("ACK: ");
			for (auto data : transmitData.bytes)
			{
				Serial.printf("%03d ", data);
			}
			Serial.println();
			gotRFData = false;
		}

		if (micros() - prevSendTime >= 10000 || sendDataFlag)
		{
			if (micros() - prevSendTime >= 11000)
			{
				Serial.printf("Loop tok more than 11000 micros. It was %d micros\r\n", micros() - prevSendTime);
			}
			prevSendTime = micros();
			checkAndSend();
			sendDataFlag = false;
		}
		CheckBatteryAction.check();
		delay(1);
	}