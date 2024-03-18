//
//
//

#include <MyHelpers.h>

#include "ChannelFunctions.h"


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

uint16_t parseRCChannel(const uint8_t channel_number, const channelConfigs *channel_settings, const rateLimitConfigStruct *rateLimitSettings, const outputEnableStruct *outputEnableSettings, const bool reverse_channel, const uint16_t *adc_values, const uint32_t IO_bits, const uint16_t *AUX_Serial_Channels)
{
    uint16_t returnValue = 2023; // Make sure that RX will not parse this if nothing changed
    if(channelNotEnabled(channel_number, outputEnableSettings, IO_bits, AUX_Serial_Channels))
    {
        return returnValue;
    }
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
                returnValue = AUX_Serial_Channels[io1];
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
    returnValue = checkRateLimit(channel_number, rateLimitSettings, channel_settings, adc_values, IO_bits, AUX_Serial_Channels, returnValue);
    return returnValue;
}

uint16_t checkRateLimit(const uint8_t channel_number, const rateLimitConfigStruct *rateLimitSettings, const channelConfigs *channel_settings, const uint16_t *adc_values, const uint32_t IO_bits, const uint16_t *AUX_Serial_Channels, uint16_t channelValue)
{
    uint16_t returnValue = channelValue;
    if (rateLimitSettings->outputToRateLimit == channel_number)
    {
        auto io1t = rateLimitSettings->input[0].type;
        auto io2t = rateLimitSettings->input[1].type;
        auto io1 = rateLimitSettings->input[0].index;
        auto io2 = rateLimitSettings->input[1].index;
        int8_t limit;
        if (io1t != CTYPE_NONE && io2t == CTYPE_NONE) // Single channel mapped
        {
            switch (io1t)
            {
            case CTYPE_ADC:
                limit = (int8_t)(adc_values[io1] / 10);
                break;

            case CTYPE_IO:
                limit = bitRead(IO_bits, io1) - 1;
                break;

            case CTYPE_AUX_IO:

                break;

            case CTYPE_AUX_SERIAL:
            {
                uint16_t auxValue = AUX_Serial_Channels[channel_number] / 500;
                limit = auxValue - 2;
            }
            break;

            default:
                return returnValue;
                break;
            }
        }
        else if (io1t == CTYPE_IO && io2t == CTYPE_IO) // Multi IO mapped
        {
            bool b1 = bitRead(IO_bits, io1);
            bool b2 = bitRead(IO_bits, io2);
            if (!b1 && !b2)
            {
                limit = 0;
            }
            else if (b1 && !b2)
            {
                limit = 1;
            }
            else if (!b1 && b2)
            {
                limit = -1;
            }
            else
            {
                return returnValue;
            }
        }
        else // Invalid config
        {
            return returnValue;
        }

        uint16_t channelMinValue = 1000;
        uint16_t channelMaxValue = 2000;
        uint16_t mappedMinValue = 1000;
        uint16_t mappedMaxValue = 2000;

        if(channel_settings->centeredStick)
        {
            if(channelValue < 1500 && rateLimitSettings->limitSide <= 0)
            {
                channelMinValue = 1500;
                channelMaxValue = abs((int16_t)rateLimitSettings->outputValuesMax.b[limit + 1] - 3000);
            }
            else if(channelValue > 1500 && rateLimitSettings->limitSide >= 0)
            {
                channelMinValue = 1500;
                channelMaxValue = rateLimitSettings->outputValuesMax.b[limit + 1];
            }
        }
        else
        {
            mappedMaxValue = rateLimitSettings->outputValuesMax.b[limit + 1];
        }
        returnValue = map(channelValue, channelMinValue, channelMaxValue, mappedMinValue, mappedMaxValue);
    }
    return returnValue;
}

bool channelNotEnabled(const uint8_t channel_number, const outputEnableStruct *outputEnableSettings, const uint32_t IO_bits, const uint16_t *AUX_Serial_Channels)
{
    if(bitRead(outputEnableSettings->outputsToEnable, channel_number))
    {
        auto oeiType = outputEnableSettings->inputIO.type;
        auto oeiIndex = outputEnableSettings->inputIO.index;
        bool disableOutput = false;
        switch (oeiType)
        {
            case CTYPE_IO:
                disableOutput = bitRead(IO_bits, oeiIndex);
            break;

            case CTYPE_AUX_IO:

            break;

            case CTYPE_AUX_SERIAL:
                disableOutput = AUX_Serial_Channels[oeiIndex] == 2000;
            break;
        }
        return disableOutput;
    }
}
