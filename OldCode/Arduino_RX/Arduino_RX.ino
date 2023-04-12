#include <HardwareSerial.h>
#include <Serial_Anything.h>
#include <EEPROM.h>
#include <TimedAction.h>
#include <SPI.h>
#include <MyHelpers.h>
#include "Structs.h"
#include "SBUS.h"
#include "SharedVars.h"
#include "config.h"
SPIClass nrfSPI = SPIClass(PB15, PB14, PB13, PB12);
#define _SPI nrfSPI
#include <RF24.h>

#undef RF24CE
#undef RF24CS
#undef RF24INT

#define RF24CE					PB11 //RADIO CHIP ENABLE
#define RF24CS					PB12 // SPI CHIP SELECT
#define RF24INT					PB10  

#define SLEDR					PC1
#define SLEDG					PC2
#define SLEDB					PC3

#define BINDPIN					0
#define SBUSSERIAL				Serial4
#define CUSTOMSERIAL			Serial5

HardwareTimer Timer1 = HardwareTimer(TIM1);
HardwareTimer Timer2 = HardwareTimer(TIM2);
HardwareTimer Timer3 = HardwareTimer(TIM3);
HardwareTimer Timer4 = HardwareTimer(TIM4);
HardwareTimer Timer5 = HardwareTimer(TIM5);
HardwareTimer Timer8 = HardwareTimer(TIM8);


HardwareSerial Serial4(PC11,PC10);
HardwareSerial Serial5(PD2,PC12);

const uint64_t pipe = 0xE8E8F0F0E1LL;
volatile boolean gotRFDate = false;

uint32_t loop_timer = 0;

struct chDefines
{
	uint8_t chNumber;
	uint16_t pin;
	HardwareTimer *timer;
	uint8_t timer_ch;
};

SBUS sbus;

uint32_t setPWMLoops = 0; // Used to count how many times the setPWM function is called WITHOUT receiving new transmitter data

bool transmitError = 0; // Error that is major but can still be ignored
bool criticalError = 0; // Fatal error that needs to trigger fail safe
uint16_t channelData[24]; // Channel data from 1000 to 2000
uint16_t sbuschannelData[30]; // Channel data from SBUS

typedef enum { role_sender = 1, role_receiver } role_e;                 // The various roles supported by this sketch
role_e role = role_receiver;                                            // The role of the current running sketch
String SerialBuffer = "";

TimedAction sendDataToControllerAction = TimedAction();

bigUnion bigDataUnion;

Settings settings;
Model activeSettings;


chDefines ch_defines[24] = {
	{10, PA8,  &Timer1, 1},
	{17, PA4,  &Timer1, 2}, // DAC1	   // Mosfet switching output pin?
	{18, PA5,  &Timer1, 3}, // DAC2	   // Mosfet switching output pin?
	{20, PA11, &Timer1, 4},
	{9,  PA15, &Timer2, 1},
	{21, PB3,  &Timer2, 2},
	{24, PB10, &Timer2, 3},		
	{16, PA3,  &Timer2, 4},
	{22, PB4,  &Timer3, 1},
	{19, PB5,  &Timer3, 2},
	{11, PB0,  &Timer3, 3},
	{12, PB1,  &Timer3, 4},
	{5,  PB6,  &Timer4, 1},
	{6,  PB7,  &Timer4, 2},
	{7,  PB8,  &Timer4, 3},
	{8,  PB0,  &Timer4, 4},
	{13, PA0,  &Timer5, 1},
	{14, PA1,  &Timer5, 2},
	{15, PA2,  &Timer5, 3},
	{23, PA3,  &Timer5, 3},
	{1,  PC6,  &Timer8, 1},
	{2,  PC7,  &Timer8, 2},
	{3,  PC8,  &Timer8, 3},
	{4,  PC9,  &Timer8, 4},
};

chDefines getchDefineByTimerAndCH(HardwareTimer* timer, uint8_t channel);
chDefines getchDefineByTimerAndCH(HardwareTimer* timer, uint8_t channel)
{
	for (auto chdefine : ch_defines)
	{
		if (chdefine.timer == timer && chdefine.timer_ch == channel) return chdefine;
	}
}

uint16_t getChDefault(uint8_t channel)
{
	return activeSettings.channel_settings.chDefaults[channel - 1];
}

void saveSettings()
{
	EEPROM.put(0, settings);
}

void loadSettings()
{
	Serial.print("Settings size is ");
	Serial.println(sizeof(settings));
	EEPROM.get(0, settings);
	if (settings.version != SETTINGSVERSION || EEPROMFULLWIPE)
	{
		Serial.printf("Settings are not correct or full wipe requested. Current version %d, expected version %d\r\nWiping EEPROM config\r\n", settings.version, SETTINGSVERSION);
		delay(1000);
		for (int i = 0; i < 8; i++)
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

void check_radio(void)
{
	bool tx, fail, rx;
	radio.whatHappened(tx, fail, rx);                     // What happened?

	if (tx) {                                         // Have we successfully transmitted?
		if (role == role_sender) { Serial.println(F("Send:OK")); }
		if (role == role_receiver) { Serial.println("Ack Payload:Sent"); }
	}

	if (fail) {                                       // Have we failed to transmit?
		if (role == role_sender) { Serial.println(F("Send:Failed")); }
		if (role == role_receiver) { Serial.println("Ack Payload:Failed"); }
	}

	if (rx || radio.available()) {                      // Did we receive a message?

		if (role == role_sender) {                      // If we're the sender, we've received an ack payload
			// radio.read(&message_count, sizeof(message_count));
			// Serial.print(F("Ack: "));
			// Serial.println(message_count);
		}


		if (role == role_receiver) {                    // If we're the receiver, we've received a time message
			// static unsigned long got_time;                  // Get this payload and dump it
			// radio.read(&got_time, sizeof(got_time));
			// Serial.print(F("Got payload "));
			// Serial.println(got_time);
			// radio.writeAckPayload(1, &message_count, sizeof(message_count));  // Add an ack packet for the next time around.  This is a simple
			// ++message_count;                                // packet counter
			uint32_t micro = micros();
			radio.read(&transmitData, sizeof(transmitData));

			radio.writeAckPayload(1, &micro, sizeof(uint32_t));
		}
	}
}

void nrfInterrupted() {
	gotRFDate = true;
}

void setPWM()
{
	if (setPWMLoops < 100) // Half a second
	{
		criticalError = transmitError = false;
		for(int i = 0; i < 24; i++)
		{
			chDefines chDefine = ch_defines[i];
			if (activeSettings.channel_settings.outputMode[i] != RC_OUTPUT_DAC) {
				chDefine.timer->setCaptureCompare(chDefine.timer_ch, channelData[i]);
			}
			else {
				if (chDefine.pin == PA4 || chDefine.pin == PA5) {
					analogWrite(chDefine.pin, channelData[i] / 4);
				}
			}
		}
	}
	else
	{
		if (setPWMLoops > 300) {
			digitalWrite(SLEDR, HIGH);
			criticalError = true;
		}
		for (int i = 0; i < 24; i++)
		{
			chDefines chDefine = ch_defines[i];
			if (activeSettings.channel_settings.outputMode[i] != RC_OUTPUT_DAC) {
				chDefine.timer->setCaptureCompare(chDefine.timer_ch, activeSettings.channel_settings.chDefaults[i]);
			}
			else {
				if (chDefine.pin == PA4 || chDefine.pin == PA5) {
					analogWrite(chDefine.pin, activeSettings.channel_settings.chDefaults[i] / 4);
				}
			}
		}
		transmitError = true;
	}
	setPWMLoops++;
}

void setCHHigh(uint16_t pin)
{
	digitalWrite(pin, HIGH);
}
void setCHLow(uint16_t pin)
{
	digitalWrite(pin, HIGH);
}

void setCHsTimer1High()
{
	setCHHigh(ch_defines[16].pin);
	setCHHigh(ch_defines[17].pin);
}
void setCHsTimer5High()
{
	setCHHigh(ch_defines[23].pin);
	setCHHigh(ch_defines[24].pin);
}


void setupTransmitter() {
	radio.begin();
	radio.setPALevel(RF24PA);
	radio.setDataRate(RF24BR);
	radio.enableAckPayload();                         // We will be using the Ack Payload feature, so please enable it
	radio.enableDynamicPayloads();                    // Ack payloads are dynamic payloads

	radio.openWritingPipe(nrfAddress[1]);
	radio.openReadingPipe(1, nrfAddress[0]);
	radio.startListening();
	radio.writeAckPayload(1, &receiveData, sizeof(receiveData));
	radio.printDetails();
	pinMode(RF24INT, INPUT);
	attachInterrupt(RF24INT, nrfInterrupted, FALLING);
}

void sendDataToController()
{
	Serial_writeAnything(&CUSTOMSERIAL, &transmitData);
}

extern "C" void _Error_Handler(const char* file, int line)
{
	Serial.print("Error in file ");
	Serial.print(file);
	Serial.print(" at line ");
	Serial.println(line);
	for (;;) {
		digitalToggle(SLEDR);
		delay(1000);
	}
}

bool dacInited = false;
void setup() {
	Serial.begin(115200);
	delay(1000);
	loadSettings();
	Serial.println("Starting RX");
	sendDataToControllerAction = TimedAction(20, sendDataToController);
	sbus.init(&SBUSSERIAL);

	pinMode(SLEDR, OUTPUT);
	pinMode(SLEDG, OUTPUT);
	pinMode(SLEDB, OUTPUT);

	CUSTOMSERIAL.begin(500000); // Super fast

	delay(100);
	// Channels
	for (int i = 0; i < 24; i++)
	{
		channelData[i] = activeSettings.channel_settings.chDefaults[i];
		if(activeSettings.channel_settings.outputMode[i] == RC_OUTPUT_DAC)
		{
			analogWrite(ch_defines[i].pin, getChDefault(i)); // This also configures the pin
		} 
		else
		{
			pinMode(ch_defines[i].pin, OUTPUT);
			pinMode(ch_defines[i].pin, OUTPUT);
		}
	}
	delay(100);
#pragma region Timer Setup
	Timer1.pause();
	Timer1.setPrescaleFactor(72);
	Timer1.setOverflow(5000);
	Timer1.setMode(1, TIMER_OUTPUT_COMPARE_PWM1, getchDefineByTimerAndCH(&Timer1, 1).pin);
	Timer1.setMode(2, TIMER_OUTPUT_COMPARE_PWM1);
	Timer1.setMode(3, TIMER_OUTPUT_COMPARE_PWM1);
	Timer1.setMode(4, TIMER_OUTPUT_COMPARE_PWM1, getchDefineByTimerAndCH(&Timer1, 4).pin);
	Timer1.setCaptureCompare(1, getChDefault(getchDefineByTimerAndCH(&Timer1, 1).chNumber));
	Timer1.setCaptureCompare(2, getChDefault(getchDefineByTimerAndCH(&Timer1, 2).chNumber));
	Timer1.setCaptureCompare(3, getChDefault(getchDefineByTimerAndCH(&Timer1, 3).chNumber));
	Timer1.setCaptureCompare(4, getChDefault(getchDefineByTimerAndCH(&Timer1, 4).chNumber));
	Timer1.attachInterrupt(std::bind(setCHsTimer1High));
	Timer1.attachInterrupt(2, std::bind(setCHLow, ch_defines[17].pin));
	Timer1.attachInterrupt(3, std::bind(setCHLow, ch_defines[18].pin));
	Timer1.resume();
	Timer1.refresh();
	delay(100);

	Timer2.pause();
	Timer2.setPrescaleFactor(72);
	Timer2.setOverflow(5000);
	Timer2.setMode(1, TIMER_OUTPUT_COMPARE_PWM1, getchDefineByTimerAndCH(&Timer2, 1).pin);
	Timer2.setMode(2, TIMER_OUTPUT_COMPARE_PWM1, getchDefineByTimerAndCH(&Timer2, 2).pin);
	Timer2.setMode(3, TIMER_OUTPUT_COMPARE_PWM1, getchDefineByTimerAndCH(&Timer2, 3).pin);
	Timer2.setMode(4, TIMER_OUTPUT_COMPARE_PWM1, getchDefineByTimerAndCH(&Timer2, 4).pin);
	Timer2.attachInterrupt(setPWM);
	Timer2.setCaptureCompare(1, getChDefault(getchDefineByTimerAndCH(&Timer2, 1).chNumber));
	Timer2.setCaptureCompare(2, getChDefault(getchDefineByTimerAndCH(&Timer2, 2).chNumber));
	Timer2.setCaptureCompare(3, getChDefault(getchDefineByTimerAndCH(&Timer2, 3).chNumber));
	Timer2.setCaptureCompare(4, getChDefault(getchDefineByTimerAndCH(&Timer2, 4).chNumber));
	Timer2.resume();
	Timer2.refresh();
	delay(100);

	Timer3.pause();
	Timer3.setPrescaleFactor(72);
	Timer3.setOverflow(5000);
	Timer3.setMode(1, TIMER_OUTPUT_COMPARE_PWM1, getchDefineByTimerAndCH(&Timer3, 1).pin);
	Timer3.setMode(2, TIMER_OUTPUT_COMPARE_PWM1, getchDefineByTimerAndCH(&Timer3, 2).pin);
	Timer3.setMode(3, TIMER_OUTPUT_COMPARE_PWM1, getchDefineByTimerAndCH(&Timer3, 3).pin);
	Timer3.setMode(4, TIMER_OUTPUT_COMPARE_PWM1, getchDefineByTimerAndCH(&Timer3, 4).pin);
	Timer3.setCaptureCompare(1, getChDefault(getchDefineByTimerAndCH(&Timer3, 1).chNumber));
	Timer3.setCaptureCompare(2, getChDefault(getchDefineByTimerAndCH(&Timer3, 2).chNumber));
	Timer3.setCaptureCompare(3, getChDefault(getchDefineByTimerAndCH(&Timer3, 3).chNumber));
	Timer3.setCaptureCompare(4, getChDefault(getchDefineByTimerAndCH(&Timer3, 4).chNumber));
	Timer3.resume();
	Timer3.refresh();
	delay(100);

	Timer4.pause();
	Timer4.setPrescaleFactor(72);
	Timer4.setOverflow(5000);
	Timer4.setMode(1, TIMER_OUTPUT_COMPARE_PWM1, getchDefineByTimerAndCH(&Timer4, 1).pin);
	Timer4.setMode(2, TIMER_OUTPUT_COMPARE_PWM1, getchDefineByTimerAndCH(&Timer4, 2).pin);
	Timer4.setMode(3, TIMER_OUTPUT_COMPARE_PWM1, getchDefineByTimerAndCH(&Timer4, 3).pin);
	Timer4.setMode(4, TIMER_OUTPUT_COMPARE_PWM1, getchDefineByTimerAndCH(&Timer4, 4).pin);
	Timer4.setCaptureCompare(1, getChDefault(getchDefineByTimerAndCH(&Timer4, 1).chNumber));
	Timer4.setCaptureCompare(2, getChDefault(getchDefineByTimerAndCH(&Timer4, 2).chNumber));
	Timer4.setCaptureCompare(3, getChDefault(getchDefineByTimerAndCH(&Timer4, 3).chNumber));
	Timer4.setCaptureCompare(4, getChDefault(getchDefineByTimerAndCH(&Timer4, 4).chNumber));
	Timer4.resume();
	Timer4.refresh();
	delay(100);

	Timer5.pause();
	Timer5.setPrescaleFactor(72);
	Timer5.setOverflow(5000);
	Timer5.setMode(1, TIMER_OUTPUT_COMPARE_PWM1, getchDefineByTimerAndCH(&Timer5, 1).pin);
	Timer5.setMode(2, TIMER_OUTPUT_COMPARE_PWM1, getchDefineByTimerAndCH(&Timer5, 2).pin);
	Timer5.setMode(3, TIMER_OUTPUT_COMPARE_PWM1);
	Timer5.setMode(4, TIMER_OUTPUT_COMPARE_PWM1);
	Timer5.setCaptureCompare(1, getChDefault(getchDefineByTimerAndCH(&Timer5, 1).chNumber));
	Timer5.setCaptureCompare(2, getChDefault(getchDefineByTimerAndCH(&Timer5, 2).chNumber));
	Timer5.setCaptureCompare(3, getChDefault(getchDefineByTimerAndCH(&Timer5, 3).chNumber));
	Timer5.setCaptureCompare(4, getChDefault(getchDefineByTimerAndCH(&Timer5, 4).chNumber));
	Timer5.attachInterrupt(std::bind(setCHsTimer5High));
	Timer5.attachInterrupt(3, std::bind(setCHLow, ch_defines[23].pin));
	Timer5.attachInterrupt(4, std::bind(setCHLow, ch_defines[24].pin));
	Timer5.resume();
	Timer5.refresh();
	delay(100);

	Timer8.pause();
	Timer8.setPrescaleFactor(72);
	Timer8.setOverflow(5000);
	Timer8.setMode(1, TIMER_OUTPUT_COMPARE_PWM1, getchDefineByTimerAndCH(&Timer8, 1).pin);
	Timer8.setMode(2, TIMER_OUTPUT_COMPARE_PWM1, getchDefineByTimerAndCH(&Timer8, 2).pin);
	Timer8.setMode(3, TIMER_OUTPUT_COMPARE_PWM1, getchDefineByTimerAndCH(&Timer8, 3).pin);
	Timer8.setMode(4, TIMER_OUTPUT_COMPARE_PWM1, getchDefineByTimerAndCH(&Timer8, 4).pin);
	Timer8.setCaptureCompare(1, getChDefault(getchDefineByTimerAndCH(&Timer8, 1).chNumber));
	Timer8.setCaptureCompare(2, getChDefault(getchDefineByTimerAndCH(&Timer8, 2).chNumber));
	Timer8.setCaptureCompare(3, getChDefault(getchDefineByTimerAndCH(&Timer8, 3).chNumber));
	Timer8.setCaptureCompare(4, getChDefault(getchDefineByTimerAndCH(&Timer8, 4).chNumber));
	Timer8.resume();
	Timer8.refresh();
	delay(100);
#pragma endregion 
	setPWM();
	memset(transmitData.bytes, 0, 24);
	memset(receiveData.bytes, 0, 24);

	setupTransmitter(); // Do this as last. It is not wanted before the init process

	Serial.println("Started RX");
}
void loop() {
	if(sbus.loop()) // We got data via the SBUS connection
	{
		Serial.println("Some data on SBUS serial");
		sbus.read(sbuschannelData, &criticalError, &transmitError);
	}
	
	sendDataToControllerAction.check();

	if (CUSTOMSERIAL.available() > 0) // We got data from the connected MCU to send to the transmitter
	{
		CUSTOMSERIAL.readBytes(receiveData.bytes, 32);
	}


	//Flight controller code here
	if (gotRFDate) {
		digitalWrite(SLEDR, HIGH);
		check_radio();
		if (transmitData.bytes[0] == channelBitID) {
			Serial.println("Got channel data");
			channelData[0]  = transmitData.ch_data.channel1 ;
			channelData[1]  = transmitData.ch_data.channel2 ;
			channelData[2]  = transmitData.ch_data.channel3 ;
			channelData[3]  = transmitData.ch_data.channel4 ;
			channelData[4]  = transmitData.ch_data.channel5 ;
			channelData[5]  = transmitData.ch_data.channel6 ;
			channelData[6]  = transmitData.ch_data.channel7 ;
			channelData[7]  = transmitData.ch_data.channel8 ;
			channelData[8]  = transmitData.ch_data.channel9 ;
			channelData[9]  = transmitData.ch_data.channel10;
			channelData[10] = transmitData.ch_data.channel11;
			channelData[11] = transmitData.ch_data.channel12;
			channelData[12] = transmitData.ch_data.channel13;
			channelData[13] = transmitData.ch_data.channel14;
			channelData[14] = transmitData.ch_data.channel15;
			channelData[15] = transmitData.ch_data.channel16;
			channelData[16] = transmitData.ch_data.channel17;
			channelData[17] = transmitData.ch_data.channel18;
			channelData[18] = transmitData.ch_data.channel19;
			channelData[19] = transmitData.ch_data.channel20;
			channelData[20] = transmitData.ch_data.channel21;
			channelData[21] = transmitData.ch_data.channel22;
			channelData[22] = transmitData.ch_data.channel23;
			channelData[23] = transmitData.ch_data.channel24;

			for (uint8_t i = 0; i < 24; i++) {
				if(channelData[i] > 1000)
				{
					if (bitRead(channelData[i], RC_OUTPUT_DAC))
					{
						analogWrite(ch_defines[i].pin, channelData[i] / 4); // If DAC is enabled then this will write it via the DAC
					}
					else if(bitRead(channelData[i], RC_OUTPUT_PWM))
					{
						channelData[i] = (channelData[i] - 3) *  5;
					}
					else if(bitRead(channelData[i], RC_OUTPUT_HTL)) // High to low so default is HIGH
					{
						channelData[i] = channelData[i] > 500 ? 0 : 5000;
					}
					else if(bitRead(channelData[i], RC_OUTPUT_LTH))
					{
						channelData[i] = channelData[i] > 500 ? 5000 : 0;
					}
					
				} 
				else
				{
					channelData[i] += 1000;
				}
				bigDataUnion.big_struct.channel[i] = channelData[i];
			}
			gotRFDate = false;
			setPWMLoops = 0;
			sbus.sbusPreparePacket(channelData, transmitError, criticalError);
			digitalWrite(SLEDR, LOW);
		}
	}
}