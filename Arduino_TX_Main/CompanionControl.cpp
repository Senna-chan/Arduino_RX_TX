// 
// 
// 

#include "CompanionControl.h"
#include "FreeRTOSVars.h"
#include "Structs.h"
#include "settingsHelper.h"

bool stream_adc = false;
bool stream_rc = false;
bool stream_channel = false;
Stream* output;
void handleCompanionControl(void* parameter) {
	Serial.println("HandleCompanionControl");
	output = (Stream*)parameter;
	while (true) {
		if (output->available()) {
			char c = output->read();
			if (c == '\r' || c == '\n' || c == 255) continue;
			Serial.printf("Received '%c' from CompanionConnection.\n", c);
			switch (c) {
				case 'R':{
					int settingsLen = sizeof(Settings);
					uint8_t* settingsPtr = (uint8_t*) &settings;
					int maxWriteAmount = output->availableForWrite();
					int packetAmount = settingsLen / maxWriteAmount;
					int packetsLeft = packetAmount;
					Serial.printf("Transmitting %d bytes in %d packets\n", settingsLen, packetAmount);
					while (settingsLen) {
						maxWriteAmount = output->availableForWrite();
						int transmitSize = min(settingsLen, maxWriteAmount);
						int amountWritten = output->write(settingsPtr, transmitSize);
						if (amountWritten != transmitSize) {
#ifdef USBD_USE_CDC
							if (output == &SerialUSB) {
								if (!SerialUSB.dtr()) {
									Serial.println("Whoopsie, you forgot to set DTR on at the other side. Please do so. Aborting this transmission");
									break;
								}
							}
#endif
							Serial.printf("Failed to transmit. Only transmitted %d of %d bytes\n", amountWritten, transmitSize);
						}
						settingsLen -= amountWritten;
						settingsPtr += amountWritten;
						packetsLeft--;
						if (packetsLeft % 10 == 0) Serial.printf("Packets left %d of %d\n", packetsLeft, packetAmount);

						vTaskDelay(1 / portTICK_RATE_MS); // Make sure that other tasks can run as well
					}
					Serial.println("Transmitting settings done");
				}
				break;

				case 'T': {
					Serial.println("Settings from companion");
					Settings newSettings;
					size_t bytesRead = output->readBytes((char*)&newSettings, sizeof(Settings));
					if (bytesRead != sizeof(Settings)) {
						Serial.printf("WRONG SIZE READ. Got %d bytes of %d\n", bytesRead, sizeof(Settings));
						break;
					}
					memcpy(&settings, &newSettings, sizeof(Settings));
					activeModel = &settings.model[settings.activeModel];
					PrintCalValues(); // Validation
					saveSettings();
				}
				break;

				case 'S': // TODO: Propperly implement this
				{
					while (output->available() < 1) {
						vTaskDelay(1 / portTICK_RATE_MS);
					}
					c = output->read();
					if (c == 'A') stream_adc = !stream_adc;
					if (c == 'R') stream_rc = !stream_rc;
					if (c == 'C') stream_channel = !stream_channel;
				}
				break;

				default:
					break;
			}
		}
		vTaskDelay(10 / portTICK_RATE_MS);
	}
}
