#include "Structs.h"
#include "Arduino.h"
#include <eepromi2c_Anything.h>

transmitTypes transmitterData;
receiveTypes receiverData;
Settings settings;

const char* OUTPUTMODE_STR_TABLE[5] = {
	"RC",
	"IO",
	"PWM",
	"STEPPER",
	"DAC "
};

void initStructs()
{

}

void saveSettings() {
	eeWrite(0, settings);
}