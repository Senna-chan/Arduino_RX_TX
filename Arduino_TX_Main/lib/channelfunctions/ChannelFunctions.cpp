//
//
//

#include <MyHelpers.h>

#include "ChannelFunctions.h"
#ifdef PIO_UNIT_TESTING
#include <unity.h>
#define DEBUGPRINTF TEST_PRINTF
#else
#define DEBUGPRINTF Serial.printf
#endif

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

    returnValue = checkRateLimit(channel_number, rateLimitSettings, channel_settings->centeredStick, adc_values, IO_bits, AUX_Serial_Channels, returnValue);

    if (reverse_channel)
    {
        int16_t tempVal = (returnValue - 3000) * -1;
        returnValue = tempVal;
    }

    if (channel_settings->endPoints.min != 1000 || channel_settings->endPoints.max != 2000)
    {
        returnValue = map(returnValue, 1000, 2000, channel_settings->endPoints.min, channel_settings->endPoints.max);
    }

    return returnValue;
}

uint16_t checkRateLimit(const uint8_t channel_number, const rateLimitConfigStruct *rateLimitSettings, const bool centeredStick, const uint16_t *adc_values, const uint32_t IO_bits, const uint16_t *AUX_Serial_Channels, uint16_t channelValue)
{
    uint16_t returnValue = channelValue;
    if (rateLimitSettings->outputToRateLimit == channel_number)
    {
        auto io1 = rateLimitSettings->input[0].index;
        auto io1t = rateLimitSettings->input[0].type;
        auto io2 = rateLimitSettings->input[1].index;
        auto io2t = rateLimitSettings->input[1].type;
        uint8_t limitScale = 255; /* <! Limit with percentage */
        if (io1t != CTYPE_NONE && io2t == CTYPE_NONE) // Single channel mapped
        {
            switch (io1t)
            {
            case CTYPE_ADC:
            {
                limitScale = (uint8_t)(adc_values[io1] / 10);
            }
            break;

            case CTYPE_IO:
                limitScale = rateLimitSettings->outputValuesMax.b[bitRead(IO_bits, io1) ? 2 : 0];
            break;

            case CTYPE_AUX_IO:

            break;

            case CTYPE_AUX_SERIAL:
            {
                uint16_t aux_value = AUX_Serial_Channels[io1] - 1000;
                if(rateLimitSettings->analogInput)
                {
                    limitScale = (uint8_t)(aux_value / 10);
                }
                else
                {
                    limitScale = rateLimitSettings->outputValuesMax.b[aux_value / 500];
                }
            }
            break;

            default:
                return channelValue;
                break;
            }
        }
        else if (io1t == CTYPE_IO && io2t == CTYPE_IO) // Multi IO mapped
        {
            bool b1 = bitRead(IO_bits, io1);
            bool b2 = bitRead(IO_bits, io2);
            if (!b1 && !b2)
            {
                limitScale = rateLimitSettings->outputValuesMax.b[1];
            }
            else if (b1 && !b2)
            {
                limitScale = rateLimitSettings->outputValuesMax.b[0];
            }
            else if (!b1 && b2)
            {
                limitScale = rateLimitSettings->outputValuesMax.b[2];
            }
            else
            {
                return channelValue;
            }
        }
        else // Invalid config
        {
            return channelValue;
        } // Making percentiale math easier
        if(centeredStick)
        {
            if(channelValue < 1500 && rateLimitSettings->limitSide != LIMIT_UPONLY) // Limit down and updown
            {
                int16_t step1 = (channelValue - 3000) * -1;
                uint16_t step2 = step1 - 1500;
                returnValue = 1500 - (step2 * limitScale / 100);
            }
            else if(channelValue > 1500 && rateLimitSettings->limitSide != LIMIT_DOWNONLY) // Limit updown and up
            {
                returnValue = 1500 + ((channelValue - 1500) * limitScale / 100);
            }
            else
            {
                return channelValue;
            }
        }
        else
        {
            returnValue = 1000 + (channelValue - 1000) * limitScale / 100;
        }
    }
    return returnValue;
}

bool channelNotEnabled(const uint8_t channel_number, const outputEnableStruct *outputEnableSettings, const uint32_t IO_bits, const uint16_t *AUX_Serial_Channels)
{
    bool disableOutput = false;
    if(bitRead(outputEnableSettings->outputsToEnable, channel_number))
    {
        auto oeiType = outputEnableSettings->inputIO.type;
        auto oeiIndex = outputEnableSettings->inputIO.index;
        switch (oeiType)
        {
            case CTYPE_IO:
                disableOutput = bitRead(IO_bits, oeiIndex);
            break;

            case CTYPE_AUX_IO:

            break;

            case CTYPE_AUX_SERIAL:
                disableOutput = AUX_Serial_Channels[oeiIndex] == 1000;
            break;
        }
    }
    return disableOutput;
}
