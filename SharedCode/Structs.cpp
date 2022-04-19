#include "Structs.h"
#include "Arduino.h"
#include <eepromi2c_Anything.h>

transmitTypes transmitData;
receiveTypes receiveData;
Settings settings;

void initStructs()
{

}

void saveSettings() {
	eeWrite(0, settings);
}