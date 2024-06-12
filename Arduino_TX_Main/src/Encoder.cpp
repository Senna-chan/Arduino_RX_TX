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

bool setupEncoder(){
    if (encoderSetup)
    {
        return true;
    }
    if (!encoder.begin(i2cEncoderLibV2::INT_DATA | i2cEncoderLibV2::WRAP_DISABLE | i2cEncoderLibV2::DIRE_RIGHT | i2cEncoderLibV2::IPUP_DISABLE | i2cEncoderLibV2::RMOD_X1 | i2cEncoderLibV2::STD_ENCODER)) {
        Serial.println("Failed to init encoder");
        return false;
    }
    encoder.writeInterruptConfig(0xff); /* Enable all the interrupt */
    encoder.writeAntibouncingPeriod(20);  /* Set an anti-bouncing */
    encoder.writeDoublePushPeriod(50);  /* Set a period for the double push */

    pinMode(ENCODER_INT_PIN, INPUT_PULLUP);
    attachInterrupt(ENCODER_INT_PIN, setEncoderIRQFlag, FALLING);

    encoderSetup = true;
}

void setEncoderValues(encoderStruct* values);
{
    encoder.writeCounter(values->curValue); /* Reset the counter value */
    encoder.writeMax(values->maxValue); /* Set the maximum threshold */
    encoder.writeMin(values->minValue); /* Set the minimum threshold */
    encoder.writeStep(values->steps); /* Set the step increment */
}

void processEncoder(void* parameter) {
    while (true) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        xSemaphoreTake(i2c_mutex, portMAX_DELAY);
        if (encoder.updateStatus()) {
            #if DEBUG_ENCODER
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
            #endif
        }
        xSemaphoreGive(i2c_mutex);
    }
}
