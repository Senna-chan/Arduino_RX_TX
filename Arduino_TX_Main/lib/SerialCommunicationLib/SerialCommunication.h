#ifndef _SERIAL_COMMS_H
#define _SERIAL_COMMS_H

#ifdef PIO_UNIT_TESTING
#include <unity.h>
#define DEBUGPRINTF TEST_PRINTF
#else
#include "Arduino.h"
#endif

#include <functional>

class SerialCommunications
{
    public:

    struct SerialBinaryPacket
    {
        uint16_t header;
        uint8_t moduleClass;
        uint8_t command;
        union
        {
            uint8_t binary;
            uint8_t requestType : 1;
            uint8_t ack : 1;
            uint8_t internalError : 1;
            uint8_t unknownModule : 1;
            uint8_t unknownCommand : 1;
            uint8_t crcFault : 1;
            uint8_t dataSizeFault : 1;
            uint8_t freeBit : 1;
        } status;
        uint8_t packetNumber;
        uint16_t size;
        uint16_t crc;
        uint8_t *data;
    };

    struct SerialStrPacket
    {
        char header;
        char *moduleName;
        char *commandName;
        char *data;
        char footer;
    };

    struct SerialCommsDefinition
    {
        uint8_t moduleClass;
        char moduleName[10];
        uint8_t commandClass;
        char commandName[30];
        std::function commandFunction;
        char dataStringLayout[128];
    };

    struct HardwareAccess
    {
        std::function<int()> read;
        std::function<int()> write;
        std::function<int()> available;
    };


/**
 * @brief When not using a RTOS we use this to get data, process it and run the callback
 *
 */
    void singleThreadLoop()
    void attachHardwareAccess(HardwareAccess access);

private:
    uint8_t transmittingPacketNumber;
    uint8_t receivedPacketNumber;
    HardwareAccess hardware;
}

#endif
