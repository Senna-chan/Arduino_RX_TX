#ifndef _SERIAL_COMMS_H
#define _SERIAL_COMMS_H

#ifdef PIO_UNIT_TESTING
#include <unity.h>
#define DEBUGPRINTF TEST_PRINTF
#elif defined __ARDUINO__
#include "Arduino.h"
#endif

#include <functional>

class RobustCommunication
{
public:
    RobustCommunication()
    {
        if (freeDefinitionIndex == NULL)
        {

        }
    }

    struct BinaryPacket
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
        //uint8_t packetNumber;
        uint16_t dataSize;
        uint16_t crc;
        uint8_t* data;
    };
    /**
     * Size of all the information bytes used.
     */
    static const uint16_t BinaryPacketInformationSize = 9;

    struct CharPacket
    {
        char header;
        char moduleName[10];
        char commandName[30];
        char data[2024];
        char footer;
    };

    struct CommsDefinition
    {
        uint8_t moduleClass;
        char moduleName[10];
        uint8_t commandClass;
        char commandName[30];
        std::function<bool(uint8_t*, uint16_t)> commandFunction;
        char dataStringLayout[128];
    };

    struct HardwareAccess
    {
        std::function<int()> available;
        std::function<int()> read;
        std::function<int()> peek;
        std::function<int(uint8_t)> write;
    };


    /**
     * @brief When not using a RTOS we use this to get data, process it and run the callback
     *
     * @returns True if packet is handled
     */
    bool singleThreadLoop();

    /**
     * Used to attach the functions to read/write the data.
     *
     * \param access Callback struct
     */
    void attachHardwareAccess(HardwareAccess access);

    /**
     * Converts a binarypacket to a data array.
     *
     * \param packet Packet to parse
     * \param buffer Pre created data array
     * \return
     */
    static bool binaryPacketToDataArray(BinaryPacket packet, uint8_t* buffer);
    /**
     * Converts a char packet to a data array.
     * 
     * \param packet packet to convert
     * \param buffer Pre created data array
     * \return 
     */
    static bool charPacketToDataArray(CharPacket packet, uint8_t* buffer);

    void addCommsDefinition(CommsDefinition definition);
   
private:
    enum readState
    {
        READING_HEADER,
        READING_MODULE,
        READING_COMMAND,
        READING_STATUS,
        READING_DATASIZE,
        READING_CRC,
        READING_DATA,
        READING_FOOTER,
        READING_DONE
    };
    readState currentReadState = READING_HEADER;
    static const uint16_t definitionSize = 300;
    static CommsDefinition definitions[definitionSize];
    static uint16_t freeDefinitionIndex;
    
    uint8_t transmittingPacketNumber;
    uint8_t receivedPacketNumber;
    HardwareAccess hardware;
    uint8_t dataReadBuffer[1040]; // Ugly but usefull
    uint16_t dataReadBufferIndex = 0;
};
#endif