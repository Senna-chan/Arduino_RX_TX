#include "Structs.h"
#include "Arduino.h"
#include <eepromi2c_Anything.h>

transmitTypes transmitterData;
receiveTypes receiverData;
Settings settings;
Model* activeModel;

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