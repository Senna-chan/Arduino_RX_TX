#ifdef PIO_UNIT_TESTING
#include <unity.h>
#define DEBUGPRINTF TEST_PRINTF
#else
#define DEBUGPRINTF Serial.printf
#endif

#include "SerialComms.h"


void SerialCommunications::attachHardwareAccess(HardwareAccess access)
{
    if(access.read == nullptr)  Error_Handler();
    if(access.write == nullptr)  Error_Handler();
    if(access.available == nullptr)  Error_Handler();
    memcpy(hardware, access, sizeof(HardwareAccess));
}
