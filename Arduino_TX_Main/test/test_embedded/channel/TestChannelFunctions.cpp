#include "unity.h"
#include "ChannelFunctions.h"
#include "settingsStructs.h"
#include "Config.h"

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
    bitSet(IOExpanderBits, 1);
}

void tearDown(void) {
  // clean stuff up here
}

void test_channelNotEnabledWithIO(void) {
    TEST_ASSERT_TRUE(channelNotEnabled(1, &output_enabled_struct, IOExpanderBits, AUXRXChannels));
}


int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_channelNotEnabledWithIO);
  return UNITY_END();
}

/**
  * For Arduino framework
  */
void setup() {
  // Wait ~2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  runUnityTests();
}
void loop() {}
