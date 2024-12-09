// HMI_Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <GUISlice_HMI_Lib.h>
#include "Arduino_TX_Display_Linux_hmi.h"

void HMI_Loop() {
	HMI.loop(hmiObjects);
	if (HMI.getCurrentPageId() == HMIPageElems::calibrations) { // CalibratePage
		calDispObjs[sendChannel][0]->setValue(rawChannels[sendChannel]);
		calDispObjs[sendChannel][1]->setValue(parsedChannels[sendChannel]);
		sendChannel++;
		if (sendChannel == ADCCHANNELNUMBERS) {
			sendChannel = 0;
		}
	}
	if (HMI.getCurrentPageId() == HMIPageElems::setupChannel) {
		if (detectingIO != 0 && !detectingChannelsSet) {
			detectingChannelsSet = true;
			memcpy(detectingRawChannels, rawChannels, ADCCHANNELNUMBERS * 2);
		}
		if (detectingIO != 0) {
			for (int8_t i = 0; i < 12; i++) {
				if (abs((int16_t)detectingRawChannels[i] - (int16_t)rawChannels[i]) > 200) {
					auto str = String("Detected ADC ");
					str.concat(i);
					Serial.printf("ADCDETECT: %s\n", str.c_str());
					if (detectingIO == 1) {
						detectedIO1.type = CTYPE_ADC;
						detectedIO1.index = i;
						e_detectIO1.setValue(str.c_str());
					}
					else if (detectingIO == 2) {
						Serial.printf("INVALID");
						e_detectIO2.setValue("INVALID");
					}
					detectingChannelsSet = false;
					detectingIO = 0;
				}
			}
		}
		if (settings.model[settings.activeModel].channel_settings[channelToEditIdx].channelMapping[0].type != CTYPE_NONE ||
			settings.model[settings.activeModel].channel_settings[channelToEditIdx].channelMapping[1].type != CTYPE_NONE) {
			e_channelval.setValue(mappedChannels[channelToEditIdx]);
		}
	}
	if (HMI.getCurrentPageId() == HMIPageElems::DisplayRcValues) {
		DispDispObjs[sendChannel]->setValue(mappedChannels[sendChannel]);
		sendChannel++;
		if (sendChannel == 24) {
			sendChannel = 0;
		}
	}
	if (HMI.getCurrentPageId() == HMIPageElems::DisplayRawValues) {
		if (sendChannel < 10) {
			rawDispObjs[sendChannel]->setValue(rawChannels[sendChannel]);
		}
		else if (sendChannel == 10) {
			char buffer[33];
			for (int i = 0; i < 32; i++) buffer[31 - i] = '0' + ((prevIOExpanderBits & (1 << i)) > 0);
			buffer[32] = '\0';
			rawDispObjs[sendChannel]->setValue(buffer);
		}
		else if (sendChannel == 11) {
			char buffer[33];
			for (int i = 0; i < 32; i++) buffer[31 - i] = '0' + ((IOExpanderBits & (1 << i)) > 0);
			buffer[32] = '\0';
			rawDispObjs[sendChannel]->setValue(buffer);
		}
		sendChannel++;
		if (sendChannel == 12) {
			sendChannel = 0;
		}
	}
	if (millis() - lastHMIRefresh > 5000) {

		switch (HMI.getCurrentPageId()) {
		case HMIPageElems::calibrations:
		case HMIPageElems::DisplayRawValues:
		case HMIPageElems::DisplayRcValues:
			HMI.refreshDisplay();
			break;
		}
		lastHMIRefresh = millis();
	}
}

int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
