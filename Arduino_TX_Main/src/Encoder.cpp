// 
// 
// 

#include "Encoder.h"
#include "Structs.h"

TaskHandle_t encoder_taskHandle;

i2cEncoderLibV2 encoder(&Wire, ENCODER_ADDR);

uint8_t encoderSettingsIndex = 0;
bool encoderSetup = false;
static void setEncoderIRQFlag()
{
	vTaskNotifyGiveFromISR(encoder_taskHandle, NULL);
}

void configureEncoder()
{
	if (!encoderSetup) {
		if (!encoder.begin(i2cEncoderLibV2::INT_DATA | i2cEncoderLibV2::WRAP_DISABLE | i2cEncoderLibV2::DIRE_RIGHT | i2cEncoderLibV2::IPUP_DISABLE | i2cEncoderLibV2::RMOD_X1 | i2cEncoderLibV2::STD_ENCODER)) {
			Serial.println("Failed to init encoder");
		}
	}
	encoder.writeCounter(settings.model[settings.activeModel].encoderSettings[encoderSettingsIndex].curValue); /* Reset the counter value */
	encoder.writeMax(settings.model[settings.activeModel].encoderSettings[encoderSettingsIndex].maxValue); /* Set the maximum threshold*/
	encoder.writeMin(settings.model[settings.activeModel].encoderSettings[encoderSettingsIndex].minValue); /* Set the minimum threshold */
	encoder.writeStep(settings.model[settings.activeModel].encoderSettings[encoderSettingsIndex].steps); /* Set the step to 1*/
	encoder.writeInterruptConfig(0xff); /* Enable all the interrupt */
	encoder.writeAntibouncingPeriod(20);  /* Set an anti-bouncing */
	encoder.writeDoublePushPeriod(50);  /* Set a period for the double push */
	if (!encoderSetup) {
		pinMode(ENCODER_INT_PIN, INPUT_PULLUP);
		attachInterrupt(ENCODER_INT_PIN, setEncoderIRQFlag, FALLING);
	}
	encoderSetup = true;
}

void processEncoder(void* parameter) {
	while (true) {
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		xSemaphoreTake(i2c_mutex, portMAX_DELAY);
		if (encoder.updateStatus()) {
			if (encoder.readStatus(i2cEncoderLibV2::RMAX)) {
				Serial.print("Maximum threshold: ");
				Serial.println(encoder.readCounterInt());

				/* Write here your code */
			}
			else if (encoder.readStatus(i2cEncoderLibV2::RINC)) {
				Serial.print("Increment: ");
				Serial.println(encoder.readCounterInt());

				/* Write here your code */
			}

			if (encoder.readStatus(i2cEncoderLibV2::RMIN)) {
				Serial.print("Minimum threshold: ");
				Serial.println(encoder.readCounterInt());

				/* Write here your code */
			}
			else if (encoder.readStatus(i2cEncoderLibV2::RDEC)) {
				Serial.print("Decrement: ");
				Serial.println(encoder.readCounterInt());

				/* Write here your code */
			}

			if (encoder.readStatus(i2cEncoderLibV2::PUSHR)) {
				Serial.println("Push button Released");

				/* Write here your code */
			}

			if (encoder.readStatus(i2cEncoderLibV2::PUSHP)) {
				Serial.println("Push button Pressed");

				/* Write here your code */
			}

			if (encoder.readStatus(i2cEncoderLibV2::PUSHD)) {
				Serial.println("Double push!");

				/* Write here your code */

			}
		}
		xSemaphoreGive(i2c_mutex);
	}
}
