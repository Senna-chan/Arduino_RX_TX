// ChannelFunctions.h

#ifndef _CHANNELFUNCTIONS_h
#define _CHANNELFUNCTIONS_h

#include <Arduino.h>

#include <settingsStructs.h>


/**
 * @brief Checks if the channel needs to be rate limited.
 *
 * @param channel_number Channel number
 * @param model_settings Settings to use
 * @param channelValue Mapped_channel value
 * @return uint16_t New channel value
 */
uint16_t checkRateLimit(const uint8_t channel_number, const rateLimitConfigStruct *rateLimitSettings, const bool centeredStick, const uint16_t *adc_values, const uint32_t IO_bits, const uint16_t *AUX_Serial_Channels, uint16_t channelValue);
bool channelNotEnabled(const uint8_t channel_number, const outputEnableStruct *outputEnableSettings, const uint32_t IO_bits, const uint16_t *AUX_Serial_Channels);

uint16_t parseADCChannel(const uint16_t raw_channel, const uint16_t minValue, const uint16_t midValue, const uint16_t maxValue, const uint16_t deadZone, const uint16_t offset);

uint16_t parseRCChannel(const uint8_t channel_number, const channelConfigs *channel_settings, const rateLimitConfigStruct *rateLimitSettings, const outputEnableStruct *outputEnableSettings, const bool reverse_channel, const uint16_t *adc_values, const uint32_t IO_bits, const uint16_t *AUX_Serial_Channels);

#endif
