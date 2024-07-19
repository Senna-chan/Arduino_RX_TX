#include "unity.h"
#include "ChannelFunctions.h"
#include "settingsStructs.h"
#include "Config.h"

#define RATELIMITTEST(val, ret) doRateLimitTest(val, ret, __LINE__)

channelConfigs channel_config;
rateLimitConfigStruct rate_limit_config;
outputEnableStruct output_enabled_struct;
uint16_t rawChannels[RC_MAX_CHANNELS];
uint16_t AUXRXChannels[RC_MAX_CHANNELS]; // AUX Serial channels temp capture
uint32_t IOExpanderBits = 0;

/*
uint16_t checkRateLimit(const uint8_t channel_number, const rateLimitConfigStruct *rateLimitSettings, const channelConfigs *channel_settings,
    const uint16_t *adc_values, const uint32_t IO_bits, const uint16_t *AUX_Serial_Channels, uint16_t channelValue);
bool channelNotEnabled(const uint8_t channel_number, const outputEnableStruct *outputEnableSettings, const uint32_t IO_bits, const uint16_t *AUX_Serial_Channels);
uint16_t parseADCChannel(const uint16_t raw_channel, const uint16_t minValue, const uint16_t midValue, const uint16_t maxValue, const uint16_t deadZone, const uint16_t offset);
uint16_t parseRCChannel(const uint8_t channel_number, const channelConfigs *channel_settings, const rateLimitConfigStruct *rateLimitSettings,
    const outputEnableStruct *outputEnableSettings, const bool reverse_channel, const uint16_t *adc_values, const uint32_t IO_bits, const uint16_t *AUX_Serial_Channels);
*/

void setUp(void) {
    output_enabled_struct.inputIO.type = CTYPE_IO;
    output_enabled_struct.inputIO.index = 1;
    bitSet(output_enabled_struct.outputsToEnable, 1);

    rate_limit_config.input[0].type = CTYPE_AUX_SERIAL;
    rate_limit_config.input[0].index = 1;
    rate_limit_config.outputValuesMax.b[0] = 10;
    rate_limit_config.outputValuesMax.b[1] = 50;
    rate_limit_config.outputValuesMax.b[2] = 100;
    rate_limit_config.outputToRateLimit = 1;

    channel_config.channelMapping[0].type = CTYPE_ADC;
    channel_config.adcConfig.min = 0;
    channel_config.adcConfig.mid = 512;
    channel_config.adcConfig.max = 1023;
    channel_config.centeredStick = true;

    AUXRXChannels[1] = 1000;
    rawChannels[1] = 512;

    bitSet(IOExpanderBits, 1);
}

void tearDown(void) {
  // clean stuff up here
}

void test_channelNotEnabledWithIO(void) {
    TEST_ASSERT_TRUE(channelNotEnabled(1, &output_enabled_struct, IOExpanderBits, AUXRXChannels));
}

void test_channelEnabledWithIO(void) {
    TEST_ASSERT_FALSE(channelNotEnabled(2, &output_enabled_struct, IOExpanderBits, AUXRXChannels));
}

void doRateLimitTest(uint16_t channelValue, uint16_t expectedValue, int line)
{
    uint16_t returnedVal = checkRateLimit(1, &rate_limit_config, channel_config.centeredStick, rawChannels, IOExpanderBits, AUXRXChannels, channelValue);
    UNITY_TEST_ASSERT_EQUAL_INT(expectedValue, returnedVal, line, NULL);
}

void test_rate_limit_down_only_with_AUX_input_centered(void)
{
    rate_limit_config.limitSide = LIMIT_DOWNONLY;
    RATELIMITTEST(1250, 1475);
}

void test_rate_limit_up_only_with_AUX_input_centered(void)
{
    rate_limit_config.limitSide = LIMIT_UPONLY;
    RATELIMITTEST(1750, 1525);
}

void test_rate_limit_up_down_with_AUX_input_centered(void)
{
    rate_limit_config.limitSide = LIMIT_UPANDDOWN;
    RATELIMITTEST(1750, 1525);
    RATELIMITTEST(1250, 1475);
}


void test_rate_limit_down_only_with_AUX_input_not_centered(void)
{
    channel_config.centeredStick = false;
    rate_limit_config.limitSide = LIMIT_DOWNONLY;
    RATELIMITTEST(1500, 1050);
}

void test_rate_limit_up_down_with_AUX_input_in_center(void)
{
    rate_limit_config.limitSide = LIMIT_UPANDDOWN;
    RATELIMITTEST(1500, 1500);
}

void test_rate_limit_with_adc_input(void)
{
    channel_config.centeredStick = false;
    rate_limit_config.limitSide = LIMIT_UPANDDOWN;
}

int runUnityTests(void)
{
    UNITY_BEGIN();
    // StickEnabledSettings
    RUN_TEST(test_channelNotEnabledWithIO);
    RUN_TEST(test_channelEnabledWithIO);
    // RateConfigSettings
    RUN_TEST(test_rate_limit_down_only_with_AUX_input_centered);
    RUN_TEST(test_rate_limit_up_only_with_AUX_input_centered);
    RUN_TEST(test_rate_limit_up_down_with_AUX_input_centered);
    RUN_TEST(test_rate_limit_down_only_with_AUX_input_not_centered);
    RUN_TEST(test_rate_limit_up_down_with_AUX_input_in_center);
    // RUN_TEST(test_rate_limit_with_adc_input);
    return UNITY_END();
}

/**
  * For Arduino framework
  */
void setup()
{
    // Wait ~2 seconds before the Unity test runner
    // establishes connection with a board Serial interface
    delay(2000);

    runUnityTests();
}
void loop() {}
