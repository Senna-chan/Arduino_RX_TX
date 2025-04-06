// 
// 
// 

#include "Encoder.h"
#include <Structs.h>
#include "i2c.h"

I2CEncoder encoder(&hi2c2, ENCODER_ADDR);

uint8_t encoderSettingsIndex = 0;
bool encoderSetup = false;

void configureEncoder()
{
	if (!encoderSetup) {
		if (!encoder.begin(I2CEncoder::INT_DATA | I2CEncoder::WRAP_DISABLE | I2CEncoder::DIRE_RIGHT | I2CEncoder::IPUP_DISABLE | I2CEncoder::RMOD_X1 | I2CEncoder::STD_ENCODER)) {
			printf("Failed to init encoder\n");
		}
		xTaskCreate(processEncoder, "encoder", 50, NULL, 10, &encoder_taskHandle);
	}
	encoder.writeCounter(settings.model[settings.activeModel].encoderSettings[encoderSettingsIndex].curValue); /* Reset the counter value */
	encoder.writeMax(settings.model[settings.activeModel].encoderSettings[encoderSettingsIndex].maxValue); /* Set the maximum threshold*/
	encoder.writeMin(settings.model[settings.activeModel].encoderSettings[encoderSettingsIndex].minValue); /* Set the minimum threshold */
	encoder.writeStep(settings.model[settings.activeModel].encoderSettings[encoderSettingsIndex].steps); /* Set the step to 1*/
	encoder.writeInterruptConfig(0xff); /* Enable all the interrupt */
	encoder.writeAntibouncingPeriod(20);  /* Set an anti-bouncing */
	encoder.writeDoublePushPeriod(50);  /* Set a period for the double push */
	encoderSetup = true;
}

void processEncoder(void* parameter) {
	while (true) {
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		xSemaphoreTake(i2c_mutex, portMAX_DELAY);
		if (encoder.updateStatus()) {
			if (encoder.readStatus(I2CEncoder::RMAX)) {
				printf("Maximum threshold: %d\n", encoder.readCounterInt());

				/* Write here your code */
			}
			else if (encoder.readStatus(I2CEncoder::RINC)) {
				printf("Increment: %d\n",encoder.readCounterInt());

				/* Write here your code */
			}

			if (encoder.readStatus(I2CEncoder::RMIN)) {
				printf("Minimum threshold: %d\n", encoder.readCounterInt());

				/* Write here your code */
			}
			else if (encoder.readStatus(I2CEncoder::RDEC)) {
				printf("Decrement: %d\n",encoder.readCounterInt());
				/* Write here your code */
			}

			if (encoder.readStatus(I2CEncoder::PUSHR)) {
				printf("Push button Released\n");

				/* Write here your code */
			}

			if (encoder.readStatus(I2CEncoder::PUSHP)) {
				printf("Push button Pressed\n");

				/* Write here your code */
			}

			if (encoder.readStatus(I2CEncoder::PUSHD)) {
				printf("Double push!\n");

				/* Write here your code */

			}
		}
		xSemaphoreGive(i2c_mutex);
	}
}
