//
//
//

#include "settingsHelper.h"
#include "SharedVars.h"
#include <eepromi2c_Anything.h>

void PrintCalValues()
{
    Serial.println("ch\tmin\tmid\tmax\toffset\tfailsafe\tstartup\tendmin\tendmax\tIO1\tIO2");
    for (int i = 0; i < 24; i++)
    {
        auto chSetting = activeModel->channel_settings[i];
        Serial.printf("ch%d\t%04d\t%04d\t%04d\t%04d\t%04d\t\t%04d\t%04d\t%04d\t%6s%02d\t%6s%02d\r\n",
                      i + 1, chSetting.adcConfig.min, chSetting.adcConfig.mid, chSetting.adcConfig.max,
                      chSetting.trim, chSetting.failsafe, chSetting.startupVal,
                      chSetting.endPoints.min, chSetting.endPoints.max,
                      channel_types_str[chSetting.channelMapping[0].type], chSetting.channelMapping[0].index,
                      channel_types_str[chSetting.channelMapping[1].type], chSetting.channelMapping[1].index);
    }
    Serial.println();
}

/**
 * Abstraction to be able to check if the EEPROM is there and if not then just don't read and always generate default settings.
 *
 */
bool readSettings()
{
#if ENABLE_EEPROM
    if (!eepromFound)
    {
        return false;
    }
    eeRead(0, settings);
    return true;
#else
    return false;
#endif
}

void saveSettings()
{
#if ENABLE_EEPROM
    if (!eepromFound)
    {
        return;
    }
    eeWrite(0, settings);
#endif
}

void loadSettings(bool forceReset)
{
    Serial.print("Settings size is ");
    Serial.println(sizeof(Settings));
    if (!readSettings())
    {
        Serial.println("Failed to read settings. Using default settings. Send config via ControllerCompanion");
        generateDefaultSettings();
        activeModel = &settings.model[settings.activeModel];
        return;
    }
    if (settings.version != SETTINGSVERSION)
    {
        Serial.printf("Incorrect version. Current %d, expected %d\r\n", settings.version, SETTINGSVERSION);
        bool reset = forceReset;

        if (!forceReset)
        {
            Serial.println("Do you want to reset the settings? y/N\r\n");
            int oriTimeout = Serial.getTimeout();
            Serial.setTimeout(5000); // 5 seconds timeout
            char buffer[2];
            size_t bytesRead = Serial.readBytesUntil('\n', buffer, 2);
            Serial.setTimeout(oriTimeout);
            Serial.printf("Read '%s'\r\n", buffer);
            reset = buffer[0] == 'y';
        }
        else
        {
            Serial.println("Forcereset == true");
        }
        if (reset)
        {
            generateDefaultSettings();
            saveSettings();
        }
    }
    activeModel = &settings.model[settings.activeModel];
}

void generateDefaultSettings()
{
    Serial.println("(Re)creating default settings");

    settings.version = SETTINGSVERSION;
    settings.activeModel = 0;

    settings.model[0].nameSize = 0;
    memset(settings.model[0].name, 0, 20); // Blank name
    for (int i = 0; i < 24; i++)
    {
        settings.model[0].channel_settings[i].adcConfig.min = 0;
        settings.model[0].channel_settings[i].adcConfig.mid = 0;
        settings.model[0].channel_settings[i].adcConfig.max = 1023;
        settings.model[0].channel_settings[i].trim = 0;
        settings.model[0].channel_settings[i].failsafe = 0;
        settings.model[0].channel_settings[i].startupVal = 0;
        settings.model[0].channel_settings[i].outputMode = 0;
        settings.model[0].channel_settings[i].centeredStick = 0;
        settings.model[0].channel_settings[i].pwmConfig.frequency = 0;
        settings.model[0].channel_settings[i].stepperConfig.minFrequency = 0;
        settings.model[0].channel_settings[i].stepperConfig.maxFrequency = 0;
        settings.model[0].channel_settings[i].channelMapping[0].type = 0;
        settings.model[0].channel_settings[i].channelMapping[0].index = 0;
        settings.model[0].channel_settings[i].channelMapping[1].type = 0;
        settings.model[0].channel_settings[i].channelMapping[1].index = 0;
        settings.model[0].channel_settings[i].endPoints.min = 1000;
        settings.model[0].channel_settings[i].endPoints.mid = 0;
        settings.model[0].channel_settings[i].endPoints.max = 2000;
    }

    settings.model[0].deadzone = 20;
    settings.model[0].channelReversed = 0;

    for (int i = 0; i < 8; i++)
    {
        settings.model[0].channelMixing[i].source1 = 0;
        settings.model[0].channelMixing[i].source2 = 0;
        settings.model[0].channelMixing[i].dest1 = 0;
        settings.model[0].channelMixing[i].dest2 = 0;
        settings.model[0].channelMixing[i].type = 0;
    }

    settings.model[0].encoderSettings[0].minValue = 0;
    settings.model[0].encoderSettings[0].maxValue = 10;
    settings.model[0].encoderSettings[0].steps = 1;
    settings.model[0].encoderSettings[0].curValue = 1;
    settings.model[0].encoderSettings[0].division = 1;

    settings.model[0].encoderSettings[1].minValue = -105;
    settings.model[0].encoderSettings[1].maxValue = 105;
    settings.model[0].encoderSettings[1].steps = 1;
    settings.model[0].encoderSettings[1].curValue = 5;
    settings.model[0].encoderSettings[1].division = 10;

    for (int i = 1; i < 8; i++)
    {
        settings.model[i] = settings.model[0];
    }
}
