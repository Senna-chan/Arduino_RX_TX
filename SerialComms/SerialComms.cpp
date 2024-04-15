#include "pch.h"

#include "RobustCommunication.h"

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
    return testData[dataToTest].packetBytes[readIndex];
}

int available()
{
    if (readIndex < testData[dataToTest].packetSize)
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
    testData[0].packet.dataSize = 0;
    //SimpleCommand.packetNumber = 1;
    testData[0].packetBytes = (uint8_t*)malloc(RobustCommunication::BinaryPacketInformationSize);
    testData[0].packetSize = RobustCommunication::BinaryPacketInformationSize;
    RobustCommunication::binaryPacketToDataArray(testData[0].packet, testData[0].packetBytes);
}

void setupSimpleCharPacket()
{
    testData[1] = TestData{};
    testData[1].cpacket = createCharPacket("CC", "getchannel", "1");
}

void setupPackets() 
{
    setupSimplePacket();
    setupSimpleCharPacket();
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

int main(array<System::String ^> ^args)
{
    printUsefullInfo();
    setupPackets();
    setupHardwareAccess();

    while (available())
    {
        rc.singleThreadLoop();
    }

    return 0;
}
