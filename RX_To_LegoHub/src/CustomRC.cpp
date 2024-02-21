// 
// 
// 

#include "CustomRC.h"

uint8_t CustomRC::calculateCRC(uint8_t* data, uint8_t length)
{
    uint8_t crc = 0xff;
    size_t i, j;
    for (i = 0; i < length; i++) {
        crc ^= data[i];
        for (j = 0; j < 8; j++) {
            if ((crc & 0x80) != 0)
                crc = (uint8_t)((crc << 1) ^ 0x31);
            else
                crc <<= 1;
        }
    }
    return crc;
}

void CustomRC::writePacket(uint8_t command, uint8_t* data, uint8_t dataSize)
{
    _serial->write(headerByte);
    _serial->write(command);
    _serial->write(dataSize);
    delayMicroseconds(500);
    if (dataSize != 0) {
        _serial->write(data, dataSize);
    }
    _serial->write(calculateCRC(data, dataSize));
    _serial->write(footerByte);
}

void CustomRC::parsePacket()
{
    uint8_t cmd = uartBuffer[1];
    switch (cmd) {
        case CHANNELS:
            uint16_t channels[25] = { 0 };
            memcpy(channels+1, uartBuffer + 3, 24 * 2);
            channelCallback(channels, prevChannels);
            memcpy(prevChannels, channels, 25 * 2);
            break;
    }
}

void CustomRC::loop()
{
    int dataInBuffer = _serial->available();
    if (dataInBuffer >= serialDataToRead) {
        uint8_t b = (uint8_t)_serial->peek();
        //Serial.printf("Enough data. Got %d want %d. First byte 0x%02X. Headerbyte found %d\r\n", dataInBuffer, serialDataToRead, b, headerFound);
        if (b == headerByte && !headerFound) {
            //Serial.println("Header found");
            headerFound = true;
            uartBuffer[currentBufferIndex++] = _serial->read(); // Header
            uartBuffer[currentBufferIndex++] = _serial->read(); // Command
            dataSize = _serial->read();
            uartBuffer[currentBufferIndex++] = dataSize; // DataSize
            serialDataToRead = footerSize + dataSize;
            //Serial.printf("IDX = %d cmd = %d size = %d. DataSize to read %d\r\n", currentBufferIndex, uartBuffer[2], dataInBuffer, serialDataToRead);
        }
        else if(headerFound){
            //Serial.println("Reading data");
            _serial->readBytes(uartBuffer + currentBufferIndex, dataSize);
            currentBufferIndex += dataSize;
            uint8_t crc = _serial->read();
            uartBuffer[currentBufferIndex++] = crc; // CRC
            uint8_t fb = _serial->read();
            uartBuffer[currentBufferIndex++] = fb; // FOOTER
            if (fb == footerByte) {
                uint8_t calculatedCRC = calculateCRC(uartBuffer + footerSize, dataSize);
                //if (calculatedCRC != crc) {
                //    Serial.printf("CRC Is not correct. Calculated %d, received %d\r\n", calculatedCRC, crc);
                //}
                //else {
                    parsePacket();
                //}
            }
            headerFound = false;
            currentBufferIndex = 0;
        }
        else {
            _serial->read(); // Read invalid header byte
        }
    }
}

void CustomRC::init(HardwareSerial* serial)
{
    _serial = serial;
}

void CustomRC::configureChannelStreaming(uint16_t millis)
{
    uint8_t data[2] = { highByte(millis), lowByte(millis) };
    writePacket(commands::STREAM_CHANNELS, data, 2);
}

void CustomRC::getChannels()
{
    writePacket(commands::CHANNELS, NULL, 0);
}

void CustomRC::attachChannelCallback(channelDataCallback cb)
{
    channelCallback = cb;
}
