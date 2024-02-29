//
//
//

#include <MyHelpers.h>

#include "ChannelFunctions.h"
#include "AUX_Serial_reader.h"

uint16_t parseADCChannel(const uint16_t raw_channel, const uint16_t minValue, const uint16_t midValue, const uint16_t maxValue, const uint16_t deadZone, const uint16_t offset)
{
    uint16_t result = 0;
    if (midValue != 0) {
        if (between(raw_channel, midValue - deadZone, midValue + deadZone))
        {
            result = 1500;
        }
        else
        {
            if (raw_channel < midValue)
            {
                result = map(raw_channel, minValue, midValue - deadZone, 1000, 1500);
            }
            else
            {
                result = map(raw_channel, midValue + deadZone, maxValue, 1500, 2000);
            }
        }
    }
    else
    {
        if (raw_channel > minValue + deadZone)
        {
            result = map(raw_channel, minValue, maxValue - deadZone, 1000, 2000);
        }
    }
    result += offset;
    result = constrain(result, 1000, 2000);
    return result;
}

uint16_t parseRCChannel(const uint8_t channel_number, const channelConfigs* channel_settings, bool reverse_channel, const uint16_t *adc_values, uint32_t IO_bits, uint16_t* AUX_Serial_Channels)
{
    uint16_t returnValue = 2023; // Make sure that RX will not parse this if nothing changed
    auto io1t = channel_settings->channelMapping[0].type;
    auto io2t = channel_settings->channelMapping[1].type;
    auto io1 = channel_settings->channelMapping[0].index;
    auto io2 = channel_settings->channelMapping[1].index;
    //auto outputMode = chSettings.outputMode;
    if (io1t == CTYPE_NONE && io2t == CTYPE_NONE) // Not mapped
    {
        return returnValue;
    }
    if (io1t != CTYPE_NONE && io2t == CTYPE_NONE)  // Single channel mapped
    {
        switch (io1t)
        {
            case CTYPE_ADC:
                returnValue = adc_values[io1];
            break;

            case CTYPE_IO:
                returnValue = bitRead(IO_bits, io1) ? 2000 : 1000;
            break;

            case CTYPE_AUX_IO:

            break;

            case CTYPE_AUX_SERIAL:
                returnValue = AUX_Serial_reader.getChannel(io1);
            break;

            default:
                Error_Handler();
            break;
        }
    }
    else if (io1t == CTYPE_IO && io2t == CTYPE_IO) // Multi IO mapped
    {
        bool b1 = bitRead(IO_bits, io1);
        bool b2 = bitRead(IO_bits, io2);
        if (!b1 && !b2)
        {
            returnValue = 1500;
        }
        else if (b1 && !b2)
        {
            returnValue = 2000;
        }
        else if (!b1 && b2)
        {
            returnValue = 1000;
        }
        else
        {
            Serial.printf("CH%d invalid config. IO1 and IO2 both high", channel_number);
        }
    }
    else // Invalid config
    {
        Serial.printf("CH Mapping for %d invalid. IOType1 %s Type2 %s\n", channel_number, channel_types_str[io1t], channel_types_str[io2t]); // SPAM
    }
    if (channel_settings->endPoints.min != 1000 || channel_settings->endPoints.max != 2000)
    {
        returnValue = map(returnValue, 1000, 2000, channel_settings->endPoints.min, channel_settings->endPoints.max);
    }

    if (reverse_channel)
    {
        int16_t tempVal = (returnValue - 3000) * -1;
        returnValue = tempVal;
    }
    return returnValue;
}
