//
//
//
#include "Arduino_TX_Main.h"

#include "FreeRTOSVars.h"
#include "Structs.h"
#include "settingsHelper.h"

#include "CompanionControl.h"

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
            switch (c) {
                case 'R':
                {
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

                        vTaskDelay(1 / portTICK_RATE_MS);  // Make sure that other tasks can run as well
                    }
                    Serial.println("Transmitting settings done");
                }
                break;

                case 'T': {
                    Serial.println("Settings from companion");
                    Settings *newSettings = (Settings*)malloc(sizeof(Settings));
                    size_t bytesRead = output->readBytes((uint8_t*)newSettings, sizeof(Settings));
                    if (bytesRead != sizeof(Settings)) {
                        Serial.printf("WRONG SIZE READ. Got %d bytes of %d\n", bytesRead, sizeof(Settings));
                        break;
                    }
                    memcpy(&settings, newSettings, sizeof(Settings));
                    free(newSettings);
                    activeModel = &settings.model[settings.activeModel];
                    PrintCalValues();  // Validation
                    saveSettings();
                }
                break;

                case 'G': // Get
                {
                    while (output->available() < 1) {
                        vTaskDelay(1 / portTICK_RATE_MS);
                    }
                    c = output->read();
                    if (c == 'D') // Detection vars
                    {
                        output->write((uint8_t*)&rawChannels, 2 * RC_MAX_CHANNELS);
                        output->write((uint8_t*)&AUXRXChannels, 2 * RC_MAX_CHANNELS);
                        output->write((uint8_t*)&IOExpanderBits, 4);
                    }
                    if (c == 'S') // AUX SERIAL
                    {
                        output->write((uint8_t*)&AUXRXChannels, 2 * RC_MAX_CHANNELS);
                    }
                    if (c == 'R') // RC Data
                    {
                        output->write((uint8_t*)&mappedChannels, 2 * RC_MAX_CHANNELS);
                    }
                    if (c == 'A') // RC Data
                    {
                        output->write((uint8_t*)&rawChannels, 2 * RC_MAX_CHANNELS);
                        output->write((uint8_t*)&IOExpanderBits, 4);
                    }
                }
                break;

                default:
                    Serial.printf("Received '%c' from CompanionConnection.\n", c);
                    break;
            }
        }
        vTaskDelay(10 / portTICK_RATE_MS);
    }
}
