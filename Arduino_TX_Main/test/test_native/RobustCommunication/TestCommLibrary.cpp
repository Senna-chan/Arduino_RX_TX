#include "unity.h"

#include <stdio.h>
#include <string.h>

#include "RobustCommunication.h"

RobustCommunication* rc;
bool packetsHandled = false;
struct TestData
{
    RobustCommunication::BinaryPacket packet;
    RobustCommunication::CharPacket cpacket;
    uint8_t* packetBytes;
    uint16_t packetSize;
};

uint8_t writeBuffer[2024];
uint16_t writeIndex = 0;
TestData dataToTest;
uint16_t readIndex;

int read();
int write(uint8_t);
int peek();
int available();

int read()
{
    return dataToTest.packetBytes[readIndex++];
}

int write(uint8_t b)
{
    writeBuffer[writeIndex] = b;
    writeIndex++;
    return 1;
}

int peek()
{
    if (available())
    {
        return dataToTest.packetBytes[readIndex];
    }
    else
    {
        return 0;
    }
}

int available()
{
    if (readIndex < dataToTest.packetSize)
    {
        return dataToTest.packetSize - readIndex;
    }
    return 0;
}

void setupHardwareAccess()
{
    RobustCommunication::HardwareAccess access;
    access.read = read;
    access.peek = peek;
    access.write = write;
    access.available = available;
    rc->attachHardwareAccess(access);
}


uint8_t channel;
uint16_t channelValue;
bool setChannel(uint8_t* data, uint16_t dataSize)
{
    channel = data[0];
    channelValue = data[2] << 8 | data[1];
    return true;
}

void setUp(void) {
    rc = new RobustCommunication();
    setupHardwareAccess();
    memset(writeBuffer, 0, 2024);
    writeIndex = 0;
}

void tearDown(void){
    delete rc;
}

void readPacket()
{
    while (available())
    {
        rc->singleThreadLoop();
    }
}

void defaultDefinition()
{
    RobustCommunication::CommsDefinition getChannelPacket = { 0 };
    getChannelPacket.moduleClass = 0x01;
    getChannelPacket.moduleName = "CC";
    getChannelPacket.commandClass = 0x01;
    getChannelPacket.commandName = "setchannel";
    getChannelPacket.dataStringLayout = "u8,u16";
    getChannelPacket.commandFunction = setChannel;
    rc->addCommsDefinition(&getChannelPacket);
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

void test_BinaryPacket(){
    dataToTest = TestData{};
    dataToTest.packet.header = 0xCC44;
    dataToTest.packet.moduleClass = 0x01;
    dataToTest.packet.command = 0x01;
    dataToTest.packet.dataSize = 3;
    dataToTest.packet.data = (uint8_t*)malloc(3);
    dataToTest.packet.data[0] = 0x01;
    dataToTest.packet.data[1] = (uint8_t)(1500 >> 8);
    dataToTest.packet.data[2] = (uint8_t)(1500 & 0xFF);
    //SimpleCommand.packetNumber = 1;
    dataToTest.packetSize = RobustCommunication::BinaryPacketInformationSize + 1;
    dataToTest.packetBytes = (uint8_t*)malloc(dataToTest.packetSize);
    RobustCommunication::binaryPacketToDataArray(dataToTest.packet, dataToTest.packetBytes);
    defaultDefinition();
    readPacket();
    TEST_ASSERT(channel == 1);
    TEST_ASSERT(channelValue == 1500);
}

void test_CharPacket(){
    dataToTest = TestData{};
    dataToTest.cpacket = createCharPacket("CC", "setchannel", "1,1500");
    dataToTest.packetSize = 40;
    dataToTest.packetBytes = (uint8_t*)malloc(dataToTest.packetSize);
    RobustCommunication::charPacketToDataArray(dataToTest.cpacket, dataToTest.packetBytes);
    dataToTest.packetSize = strlen((char*)dataToTest.packetBytes);
    defaultDefinition();
    readPacket();
    TEST_ASSERT(channel == 1);
    TEST_ASSERT(channelValue == 1500);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_BinaryPacket);
    RUN_TEST(test_CharPacket);

    UNITY_END();

    return 0;
}
