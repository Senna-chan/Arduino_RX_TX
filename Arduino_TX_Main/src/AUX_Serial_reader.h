#ifndef __AUX_SERIAL_READER_H
#define __AUX_SERIAL_READER_H

#include <Arduino.h>
#include <ibus.h>
#include <PPMReader.h>

#include "STMRTOSIncludes.h"

class Aux_Serial_Reader
{

 public:
    enum AUX_SERIAL_PROTOCOL
    {
        NONE,     // Inactive
        IBUS,     // FLYSKY
        SBUS,     // Industry standard
        PPM,      // Pulse input
        CUSTOM_TX // My own protocol
    };
    void init(uint8_t rx, uint8_t tx);
    void begin();
    void end();
    void readData();
    void setProtocol(AUX_SERIAL_PROTOCOL protocol);
    uint16_t getChannel(uint8_t channel);
    /**
     * @brief Get all the channels. This is a limit of 24 channels
     *
     * @param channelBuf Buffer to hold channel data. Must be 24 big
     */
    void getChannels(uint16_t *channelBuf);

private:
    AUX_SERIAL_PROTOCOL activeProtocol = NONE;
    void processIBUS();
    void processSBUS();
    void processCUSTOM_TX();
    uint8_t aux_rx;
    uint8_t aux_tx;
    HardwareSerial *aux_serial;
    TaskHandle_t auxSerial_taskHandle;
    IBusBM ibus;
    PPMReader *ppm;
};

extern Aux_Serial_Reader AUX_Serial_reader;

#endif
