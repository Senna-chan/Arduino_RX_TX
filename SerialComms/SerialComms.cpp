#include "RobustCommunication.h"
#include <stdarg.h>
#include <stdio.h>

using namespace System;
RobustCommunication rc;
bool packetsHandled = false;
struct TestData
{
    RobustCommunication::BinaryPacket packet;
    RobustCommunication::CharPacket cpacket;
    uint8_t* packetBytes;
    uint16_t packetSize;
};

TestData testData[10];
uint8_t dataToTest = 0;
uint16_t readIndex;

int read();
int write(uint8_t);
int peek();
int available();

int read()
{
    return testData[dataToTest].packetBytes[readIndex++];
}

int write(uint8_t b)
{
    Console::Write(b);
    return 1;
}

int peek()
{
    if (available())
    {
        return testData[dataToTest].packetBytes[readIndex];
    }
    else
    {
        return 0;
    }
}

int available()
{
    if (readIndex < testData[dataToTest].packetSize)
    {
        return testData[dataToTest].packetSize - readIndex;
    }
    dataToTest++;
    readIndex = 0;
    if(testData[dataToTest].packetSize != 0)
    {
        return testData[dataToTest].packetSize - readIndex;
    }
    return 0;
}

RobustCommunication::CharPacket createCharPacket(const char* moduleName, const char* command, const char* data)
{
    RobustCommunication::CharPacket charPacket;
    charPacket.header = '@';
    charPacket.footer = '\n';
    strcpy(charPacket.moduleName, moduleName);
    strcpy(charPacket.commandName, command);
    strcpy(charPacket.data, data);
    return charPacket;
}

void setupSimplePacket()
{
    testData[0] = TestData{};
    testData[0].packet.header = 0xCC44;
    testData[0].packet.moduleClass = 0x01;
    testData[0].packet.command = 0x01;
    testData[0].packet.dataSize = 1;
    testData[0].packet.data = new uint8_t{ 0x01 };
    //SimpleCommand.packetNumber = 1;
    testData[0].packetSize = RobustCommunication::BinaryPacketInformationSize + 1;
    testData[0].packetBytes = (uint8_t*)malloc(testData[0].packetSize);
    RobustCommunication::binaryPacketToDataArray(&testData[0].packet, testData[0].packetBytes);
}

void setupSimplePacket()
{
    testData[2] = TestData{};
    testData[2].packet.header = 0xCC44;
    testData[2].packet.moduleClass = 0x01;
    testData[2].packet.command = 0x01;
    testData[2].packet.dataSize = 1;
    testData[2].packet.data = new uint8_t{ 0x01 };
    //SimpleCommand.packetNumber = 1;
    testData[2].packetSize = RobustCommunication::BinaryPacketInformationSize + 1;
    testData[2].packetBytes = (uint8_t*)malloc(testData[0].packetSize);
    RobustCommunication::binaryPacketToDataArray(&testData[0].packet, testData[0].packetBytes);
}

void setupSimpleCharPacket()
{
    testData[1] = TestData{};
    testData[1].cpacket = createCharPacket("CC", "setchannel", "1,1500");
    testData[1].packetSize = 40;
    testData[1].packetBytes = (uint8_t*)malloc(testData[1].packetSize);
    RobustCommunication::charPacketToDataArray(&testData[1].cpacket, testData[1].packetBytes);    
    testData[1].packetSize = strlen((char*)testData[1].packetBytes);
}

uint16_t channelValue = 0;

bool setChannel(RobustCommunication::BinaryPacket* packet)
{
    Console::WriteLine("Datasize is {0}", packet->dataSize);
    channelValue = packet->data[2] << 8 | packet->data[1];
    Console::WriteLine("set channel {0} to {1}", packet->data[0], channelValue);
    packet->status.ack = 1;
    return true;
}

bool getChannel(RobustCommunication::BinaryPacket* packet)
{
    packet->data[1] = channelValue << 8;
    packet->data[0] = channelValue &= 0xFF;
    packet->status.ack = 1;
    return true;
}

void setupPackets() 
{
    setupSimplePacket();
    setupSimpleCharPacket();
    RobustCommunication::CommsDefinition getChannelPacket = { 0 };
    getChannelPacket.moduleClass = 0x01;
    getChannelPacket.moduleName = "CC";
    getChannelPacket.commandClass = 0x01;
    getChannelPacket.commandName = "setchannel";
    getChannelPacket.dataStringLayout = "u8,u16";
    getChannelPacket.commandFunction = setChannel;
    rc.addCommsDefinition(&getChannelPacket);
}

void setupHardwareAccess()
{
    RobustCommunication::HardwareAccess access;
    access.read = read;
    access.peek = peek;
    access.write = write;
    access.available = available;
    rc.attachHardwareAccess(access);
}

void printUsefullInfo() {
    Console::WriteLine("Definition is {0} bytes big", sizeof(RobustCommunication::CommsDefinition));
}

void testCharToBufConversion()
{
    uint8_t databuffer[2024];
    memset(databuffer, 0, 2024);
    uint8_t* bufPtr = databuffer;
    const char* data = "1,2.5,drie,0x04";
    const char* dataP = data;

    const char* formatStr = "%d,%f,%s,0x%x";
    char* formatStrTok = strdup(formatStr);
    
    char* formatToken;
    formatToken = strtok(formatStrTok, ",");
    while (formatToken != NULL)
    {
        char format[20];
        char* formatP = format;
        if (strcmp(formatToken, "%s") == 0)
        {
            strcpy(formatP, "%[^,]");
            formatP += 5;
        }
        else
        {
            strcpy(formatP, formatToken);
            formatP += strlen(formatToken);
        }
        strcpy(formatP, ", %n");
        printf("%8s %10s\n", formatToken, format);

        int n = 0;
        if (sscanf(dataP, format, bufPtr, &n) != 1) {  // or use strtol()
            break;
        }
        dataP += n; // Advance p to the next part of the buffer
        bufPtr += n;
        formatToken = strtok(NULL, ",");
    }
    printf("Parsed");
    //if (*p != '\0') {
    //    Handle_junk_at_end_of_buffer(); // Add user code here to cope with this error
    //}
}

int main(array<System::String ^> ^args)
{
    printUsefullInfo();
    setupPackets();
    setupHardwareAccess();
    rc.printHelp();
    while (available())
    {
        rc.singleThreadLoop();
    }

    return 0;
}
