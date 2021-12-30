/*
 Name:		ExpenderTest.ino
 Created:	9/15/2021 8:57:02 PM
 Author:	Senna
*/


#include <Adafruit_SPIDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_MCP23008.h>
#include <MyHelpers.h>
#include <Wire.h>

Adafruit_MCP23017 twoWayExpender, calButtonExpender;
Adafruit_MCP23008 oneWayExpender;


uint8_t oldOne = 0;
uint16_t oldTwo = 0;
uint16_t oldCal = 0;


uint8_t twoWayAddr = 0b001;
uint8_t oneWayAddr = 0b010;
uint8_t calAddr = 0b111;

void readExpenders() {
	uint16_t twoWay = twoWayExpender.readGPIOAB();
	uint8_t oneWay = oneWayExpender.readGPIO();
	uint16_t cals = calButtonExpender.readGPIOAB();
	bool printed = false;
	if (oneWay != oldOne) {
		Serial.print("ONE: ");
		printBits(&Serial, oneWay);
		Serial.print(" ");
		printed = true;
	}
	if (twoWay != oldTwo) {
		Serial.print("TWO: ");
		printBits(&Serial, twoWay);
		Serial.print(" ");
		printed = true;
	}
	if (oldCal != cals) {
		Serial.print("CALS: ");
		printBits(&Serial, cals);
		Serial.print(" ");
		printed = true;
	}

	if (printed) Serial.println();

	oldTwo = twoWay;
	oldOne = oneWay;
	oldCal = cals;
}


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	Serial.println("ExpenderTest");
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);
	Wire.setSCL(PB_10);
	Wire.setSDA(PB_11);
	Wire.begin();
	//Wire2.setClock(400000);
	scanI2C(&Wire, &Serial);
	Serial.printf("Twoway %s Oneway %s Calc %s\n", I2CDeviceConnected(&Wire, 0x20 + twoWayAddr) ? "found" : "not found", I2CDeviceConnected(&Wire, 0x20 + oneWayAddr) ? "found" : "not found", I2CDeviceConnected(&Wire, 0x20 + calAddr) ? "found" : "not found");
	twoWayExpender.begin(twoWayAddr, &Wire);
	//while (!twoWayExpender.isConnected())
	//{
	//	Serial.println("2WayExpander not found");
	//	digitalWrite(LED_BUILTIN, LOW);
	//	delay(500);
	//	digitalWrite(LED_BUILTIN, HIGH);
	//	delay(500);
	//}

	twoWayExpender.writeRegister(MCP23017_IODIRA, 0xFF);   // IO TO INPUT
	twoWayExpender.writeRegister(MCP23017_IODIRB, 0xFF);
	twoWayExpender.writeRegister(MCP23017_GPPUA, 0xFF);	// ENABLE PULLUP
	twoWayExpender.writeRegister(MCP23017_GPPUB, 0xFF);
	twoWayExpender.writeRegister(MCP23017_IPOLA, 0xFF);  // ENABLE REVERSING OF IO. DOES THIS FIX A BUG?
	twoWayExpender.writeRegister(MCP23017_IPOLB, 0xFF);

	oneWayExpender.begin(oneWayAddr, &Wire);
	//while (!oneWayExpender.isConnected())
	//{
	//	Serial.println("1WayExpander not found");
	//	digitalWrite(LED_BUILTIN, LOW);
	//	delay(500);
	//	digitalWrite(LED_BUILTIN, HIGH);
	//	delay(500);
	//}
	oneWayExpender.write8(MCP23008_IODIR, 0xFF);   // IO TO INPUT
	oneWayExpender.write8(MCP23008_GPPU, 0xFF);	// ENABLE PULLUP
	oneWayExpender.write8(MCP23008_IPOL, 0xFF);  // ENABLE REVERSING OF IO. DOES THIS FIX A BUG?

	calButtonExpender.begin(calAddr, &Wire);
	//while (!calButtonExpender.isConnected())
	//{
	//	Serial.println("Calibrate button expander not found");
	//	digitalWrite(LED_BUILTIN, LOW);
	//	delay(500);
	//	digitalWrite(LED_BUILTIN, HIGH);
	//	delay(500);
	//}
	calButtonExpender.setupInterrupts(true, true, LOW);
	calButtonExpender.writeRegister(MCP23017_IODIRA, 0xFF);   // IO TO INPUT.writeRegister(MCP23017_IODIRA, 0xFF);   // IO TO INPUT
	calButtonExpender.writeRegister(MCP23017_IODIRB, 0xFF);
	calButtonExpender.writeRegister(MCP23017_GPPUA, 0xFF);	// ENABLE PULLUP.writeRegister(MCP23017_GPPUA, 0xFF);	// ENABLE PULLUP
	calButtonExpender.writeRegister(MCP23017_GPPUB, 0xFF);
	calButtonExpender.writeRegister(MCP23017_IPOLA, 0xFF);  // ENABLE REVERSING OF IO. DOES THIS FIX A BUG?
	calButtonExpender.writeRegister(MCP23017_IPOLB, 0xFF);
	calButtonExpender.readGPIOAB(); // Clearing any interrupts that may be active
	Serial.println("Started");
}

// the loop function runs over and over again until power down or reset
void loop() {
	readExpenders();
	delay(50);
}
