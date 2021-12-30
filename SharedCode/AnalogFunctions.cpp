#include "AnalogFunctions.h"

void AnalogFunctions::init()
{
	for (int i = 0; i < CHANNELNUMBERS; i++) // Setup channel(analog) pins
	{
		pinMode(chPins[i], INPUT_ANALOG);
	}
}

void AnalogFunctions::initADC()
{
}

void AnalogFunctions::readChannels()
{
	uint32_t microsStart = micros();
	for(int i = 0; i < CHANNELNUMBERS; i++)
	{
		oldChannelData[i] = channelData[i];
		channelData[i] = analogRead(chPins[i]);
	}
	uint32_t totalMicrosReading = micros() - microsStart;
	uint32_t breakHere = 0;
}

void AnalogFunctions::readChannelsADC()
{
}

void AnalogFunctions::printChangedChannels()
{
	bool changedValue = false;
	for (int i = 0; i < CHANNELNUMBERS; i++)
	{
		if (oldChannelData[i] != channelData[i]) {
			if (abs(oldChannelData[i] - channelData[i]) < 20) continue; // Small deadzone
			if (!changedValue) {
				changedValue = true;
				Serial.print("Changed values: ");
			}
			Serial.printf("CH%02d O%04d N%04d ",i, oldChannelData[i], channelData[i]);
		}
	}
	if (changedValue) Serial.println();
}

