//
//
//

#include "CompanionControl.h"

#include <cstdlib>
#include <cstring>

#include "main.h"
#include <ArduMath.hpp>
#include <ChannelFunctions.hpp>

#include "Structs.h"
#include "freertos.h"
#include "settingsHelper.h"

bool stream_adc = false;
bool stream_rc = false;
bool stream_channel = false;

channelConfigs localChannelConfig = { 0 };
bool reverseChannel = false;

void handleCompanionControl(void* parameter) {
    SerialPrint("HandleCompanionControl");
    UART_HandleTypeDef* output = static_cast<UART_HandleTypeDef*>(parameter);
    uint8_t buf[1] = { 0 };
    while (true) {
        if (HAL_UART_Receive(output, buf, 1, 0) == HAL_OK) {
            char c = buf[0];
            if (c == '\r' || c == '\n' || c == 255) {
                continue;
            }
            switch (c) {
            case 'R': {
                int32_t settingsLen = sizeof(Settings);
                // output->write((uint8_t *)settingsLen, sizeof(settingsLen));
                uint8_t* settingsPtr = reinterpret_cast<uint8_t*>(&settings);
                int32_t maxWriteAmount = 256;
                int packetAmount = settingsLen / maxWriteAmount;
                int packetsLeft = packetAmount;
                SerialPrintf("Transmitting %d bytes in %d packets\n", settingsLen, packetAmount);
                while (settingsLen) {
                    int transmitSize = min(settingsLen, maxWriteAmount);
                    int amountWritten = transmitSize;
                    HAL_UART_Transmit(output, settingsPtr, transmitSize, 0xFF);
                    //                        if (amountWritten != transmitSize) {
                    // #ifdef USBD_USE_CDC
                    //                            if (output == &SerialUSB) {
                    //                                if (!SerialUSB.dtr()) {
                    //                                    SerialPrint("Whoopsie, you forgot to set DTR on at the other side. Please do so. Aborting this transmission");
                    //                                    break;
                    //                                }
                    //                            }
                    // #endif
                    //                            SerialPrintf("Failed to transmit. Only transmitted %d of %d bytes\n", amountWritten, transmitSize);
                    //                        }
                    settingsLen -= amountWritten;
                    settingsPtr += amountWritten;
                    packetsLeft--;
                    if (packetsLeft % 10 == 0) {
                        SerialPrintf("Packets left %d of %d\n", packetsLeft, packetAmount);
                    }

                    vTaskDelay(1 / portTICK_PERIOD_MS); // Make sure that other tasks can run as well
                }
                SerialPrint("Transmitting settings done\n");
            } break;

            case 'T': {
                SerialPrint("Settings from companion\n");
                // int32_t settingsSize;
                // output->readBytes((uint8_t *)settingsSize, sizeof(settingsSize));
                // if(sizeof(settings) != settingsSize)
                // {
                //     SerialPrintf("Incorrect size Got %d want %d. Check companionapp\n", settingsSize, sizeof(Settings));
                //     Error_Handler();
                //     break;
                // }
                Settings* newSettings = (Settings*)malloc(sizeof(Settings));

                HAL_StatusTypeDef status = HAL_UART_Receive(output, (uint8_t*)newSettings, sizeof(Settings), 0xFFF);
                if (status == HAL_TIMEOUT) {
                    SerialPrint("Read timed out\n");
                    free(newSettings);
                    Error_Handler();
                    break;
                }
                if (newSettings->version != settings.version) {
                    SerialPrintf("SETTINGS NOT THE SAME VERSION. Got %d, should be %d\n", newSettings->version, settings.version);
                    free(newSettings);
                    Error_Handler();
                    break;
                }
                memcpy(&settings, newSettings, sizeof(Settings));
                free(newSettings);
                activeModel = &settings.model[settings.activeModel];
                PrintCalValues(); // Validation
                saveSettings();
            } break;

            case 'C': // ChannelConfig
            {
                HAL_UART_Receive(output, (uint8_t*)&localChannelConfig, sizeof(channelConfigs), 0xFFF);
                HAL_UART_Receive(output, buf, 1, 5);
                reverseChannel = buf[0] == 1;
                SerialPrint("Channel config");
            } break;

            case 'G': // Get
            {
                while (HAL_UART_Receive(output, buf, 1, 0) == HAL_TIMEOUT) {
                    vTaskDelay(1 / portTICK_PERIOD_MS);
                }
                c = buf[0];
                switch (c) {
                case 'D': // Detection vars
                    HAL_UART_Transmit(output, reinterpret_cast<const uint8_t*>(&rawChannels), 2 * RC_MAX_CHANNELS, 0xFF);
                    HAL_UART_Transmit(output, reinterpret_cast<const uint8_t*>(&AUXRXChannels), 2 * RC_MAX_CHANNELS, 0xFF);
                    HAL_UART_Transmit(output, reinterpret_cast<const uint8_t*>(&IOExpanderBits), 4, 0xFF);

                    break;
                case 'S': // AUX Serial values
                    HAL_UART_Transmit(output, reinterpret_cast<const uint8_t*>(&AUXRXChannels), 2 * RC_MAX_CHANNELS, 0xFF);
                    break;

                case 'R':
                    HAL_UART_Transmit(output, reinterpret_cast<const uint8_t*>(&mappedChannels), 2 * RC_MAX_CHANNELS, 0xFF);
                    break;
                case 'A':
                    HAL_UART_Transmit(output, reinterpret_cast<const uint8_t*>(&rawChannels), 2 * RC_MAX_CHANNELS, 0xFF);
                    HAL_UART_Transmit(output, reinterpret_cast<const uint8_t*>(&IOExpanderBits), 4, 0xFF);
                    break;
                case 'C': {
                    uint16_t rcValue = parseRCChannel(0, &localChannelConfig, &activeModel->rateLimitConfig, &activeModel->outputEnable, reverseChannel, parsedChannels, IOExpanderBits, AUXRXChannels);
                    HAL_UART_Transmit(output, reinterpret_cast<const uint8_t*>(&rcValue), 2, 0xFF);
                } break;
                default:
                    break;
                }
            } break;

            default:
                SerialPrintf("Unknown command. Received '%c' from CompanionConnection.\n", c);
                break;
            }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
