#ifndef _SERIAL_COMMS_H
#define _SERIAL_COMMS_H

#ifdef PIO_UNIT_TESTING
#include <unity.h>
#elif defined __ARDUINO__
#include "Arduino.h"
#endif

#include <functional>

class RobustCommunication
{
public:
    RobustCommunication()
    {
        instanceAmount++;
    }

    ~RobustCommunication()
    {
        instanceAmount--;
        if (instanceAmount == 0)
        {
            for (auto definition : definitions)
            {
                if (definition.dataStringLayout != NULL)
                {
                    //free(definition.sscanfFormat);
                }
            }
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
            uint8_t requestType : 1;    // If 0 then it is a request. If 1 then it is a response
            uint8_t ack : 1;    
            uint8_t internalError : 1;  // Error in the handling of data
            uint8_t unknownModule : 1; 
            uint8_t unknownCommand : 1;
            uint8_t crcFault : 1;
            uint8_t dataSizeFault : 1;
            uint8_t oneshot : 1;    // If set then handle and forget
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
        const char* moduleName;
        uint8_t commandClass;
        const char* commandName;
        std::function<bool(BinaryPacket*)> commandFunction;
        const char* dataStringLayout;
        const char* shortDesc;
        char* sscanfFormat;
        uint16_t expectedDataSize;
    };

    struct HardwareAccess
    {
        std::function<int()> available;
        std::function<int()> read;
        std::function<int()> peek;
        std::function<int(uint8_t)> write;
    };

    static const char charSeperator = '|';

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
    static bool binaryPacketToDataArray(BinaryPacket* packet, uint8_t* buffer, bool ignoreData = false);
    /**
     * Converts a char packet to a data array.
     *
     * \param packet packet to convert
     * \param buffer Pre created data array
     * \return
     */
    static bool charPacketToDataArray(CharPacket* packet, uint8_t* buffer);

    void addCommsDefinition(CommsDefinition* definition);

    void printHelp();

private:


    /**
     * Logic to read a binary packet.
     *
     */
    void readForBinaryPacket();

    /**
     * Logic to read a char packet.
     *
     */
    void readForCharPacket();

    void parseBinaryPacket();

    void parseCharPacket();

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

    void writeBinaryPacket(BinaryPacket* packet);
    void writeCharPacket(CharPacket* packet);

    readState currentReadState = READING_HEADER;
    static const uint16_t definitionSize = 300;
    static CommsDefinition definitions[definitionSize];
    static uint16_t freeDefinitionIndex;
    static uint8_t instanceAmount;

    uint8_t transmittingPacketNumber = 0;
    uint8_t receivedPacketNumber = 0;
    HardwareAccess hardware;
    uint8_t dataReadBuffer[1040] = { 0 }; // Ugly but usefull
    uint16_t dataReadBufferIndex = 0;
};
#endif