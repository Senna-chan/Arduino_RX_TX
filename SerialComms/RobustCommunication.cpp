#if PIO_UNIT_TESTING
#include <unity.h>
#define DEBUGPRINTF TEST_PRINTF
#elif _MANAGED

#include "pch.h"
using namespace System;
#define DEBUGPRINTF Console::WriteLine

#else
#define DEBUGPRINTF Serial.printf
#endif

#include "RobustCommunication.h"

#define IGNORE_CRC

const uint8_t maxReadCyclesPerCall = 20;
uint8_t readCycleCounter = maxReadCyclesPerCall;
bool packetIsBinary = true;
RobustCommunication::BinaryPacket currentBinaryPacket;
RobustCommunication::CharPacket currentCharPacket;
uint16_t dataBytesToRead = 0;
bool RobustCommunication::singleThreadLoop()
{
    while (hardware.available() || currentReadState == READING_DONE)
    {
        if (readCycleCounter == 0)
        {
            readCycleCounter = maxReadCyclesPerCall;
            return false;
        }
        readCycleCounter--;
        switch (currentReadState)
        {
            case READING_HEADER:
            {
                int b = hardware.read();
                if (b == 0xCC)
                {
                    int p = hardware.peek();
                    if (p == 0x44)
                    {
                        p = hardware.read();
                        currentBinaryPacket.header = b << 8 | p;
                        DEBUGPRINTF("Header found");
                        currentReadState = READING_MODULE;
                        packetIsBinary = true;
                    }
                    else
                    {
                        DEBUGPRINTF("Header not found correctly");
                    }
                }
                else if (b == '@')
                {
                    packetIsBinary = false;
                }
                else
                {
                    DEBUGPRINTF("Header not found while in header state");
                }
            }
            break;
            
            case READING_MODULE:
            {
                if (packetIsBinary)
                {
                    currentBinaryPacket.moduleClass = dataReadBuffer[dataReadBufferIndex++] = hardware.read();
                    currentReadState = READING_COMMAND;
                }
            }
            break;
            
            case READING_COMMAND:
            {
                if (packetIsBinary)
                {
                    currentBinaryPacket.command = dataReadBuffer[dataReadBufferIndex++] = hardware.read();
                    currentReadState = READING_STATUS;
                }
            }
            break;

            case READING_STATUS:
            {
                if (packetIsBinary)
                {
                    currentBinaryPacket.status.binary = dataReadBuffer[dataReadBufferIndex++] = hardware.read();
                    currentReadState = READING_DATASIZE;
                }
            }
            break;
            
            case READING_DATASIZE:
            {
                if (packetIsBinary)
                {
                    int b = hardware.read();
                    currentBinaryPacket.dataSize = b << 8;
                    dataReadBuffer[dataReadBufferIndex++] = b;
                    b = hardware.read();
                    currentBinaryPacket.dataSize |= b;
                    dataReadBuffer[dataReadBufferIndex++] = b;
                    dataBytesToRead = currentBinaryPacket.dataSize;
                    currentReadState = READING_CRC;
                }
            }
            break;
            
            case READING_CRC:
            {
                if (packetIsBinary)
                {
                    int b = hardware.read();
                    currentBinaryPacket.crc = b << 8;
                    dataReadBuffer[dataReadBufferIndex++] = b;
                    b = hardware.read();
                    currentBinaryPacket.crc |= b;
                    dataReadBuffer[dataReadBufferIndex++] = b;
                    if (dataBytesToRead > 0)
                    {
                        currentReadState = READING_DATA;
                    }
                    else
                    {
                        currentReadState = READING_DONE;
                    }
                }
            }
            break;
            
            case READING_DATA:
            {
                if (packetIsBinary)
                {   
                    for (int i = 0; i < maxReadCyclesPerCall; i++)
                    {
                        dataReadBuffer[dataReadBufferIndex++] = hardware.read();
                        readCycleCounter--;
                        dataBytesToRead--;
                        if (dataBytesToRead == 0)
                        {
                            currentReadState = READING_DONE;
                            break;
                        }
                    }
                }
            }
            break;

            case READING_DONE:
            {
                bool moduleFound = false;
                bool commandFound = false;
                int defIndex;
                if (packetIsBinary)
                {
                    for (defIndex = 0; defIndex < freeDefinitionIndex; defIndex++)
                    {
                        if (definitions[defIndex].moduleClass == currentBinaryPacket.moduleClass)
                        {
                            moduleFound = true;
                            if (definitions[defIndex].commandClass == currentBinaryPacket.command)
                            {
                                commandFound = true;
                            }
                        }
                        if (moduleFound && commandFound)
                        {
                            break;
                        }
                    }
                }

                if (moduleFound && commandFound)
                {
                    if (packetIsBinary)
                    {
                        definitions[defIndex].commandFunction(currentBinaryPacket.data, currentBinaryPacket.dataSize);
                    }
                }
            }
            break;

        }
    }

    return true;
}

void RobustCommunication::attachHardwareAccess(HardwareAccess access)
{
    //if(access.read == nullptr)  Error_Handler();
    //if(access.write == nullptr)  Error_Handler();
    //if(access.available == nullptr)  Error_Handler();
    hardware = access;
}

bool RobustCommunication::binaryPacketToDataArray(BinaryPacket packet, uint8_t* buffer)
{
    uint16_t bufferIndex = 0;
    buffer[bufferIndex++] = 0xCC;
    buffer[bufferIndex++] = 0x44;
    buffer[bufferIndex++] = packet.moduleClass;
    buffer[bufferIndex++] = packet.command;
    buffer[bufferIndex++] = packet.status.binary;
    buffer[bufferIndex++] = (uint8_t)(packet.dataSize >> 8);
    buffer[bufferIndex++] = (uint8_t)(packet.dataSize & 0xFF);
    buffer[bufferIndex++] = (uint8_t)(packet.crc >> 8);
    buffer[bufferIndex++] = (uint8_t)(packet.crc & 0xFF);
    memcpy(&buffer[bufferIndex], packet.data, packet.dataSize);
    return true;
}

bool RobustCommunication::charPacketToDataArray(CharPacket packet, uint8_t* buffer)
{
    uint16_t bufferIndex = 0;
    buffer[bufferIndex++] = packet.header;
    
}

void RobustCommunication::addCommsDefinition(CommsDefinition definition)
{
    if (freeDefinitionIndex != definitionSize)
    {
        definitions[freeDefinitionIndex++] = definition;
    }
}


RobustCommunication::CommsDefinition RobustCommunication::definitions[definitionSize];
uint16_t RobustCommunication::freeDefinitionIndex = 0;
