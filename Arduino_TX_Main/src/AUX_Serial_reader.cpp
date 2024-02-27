#include "AUX_Serial_reader.h"


void aux_serial_trigger_read(void* parameter){
    Aux_Serial_Reader *serialReader = (Aux_Serial_Reader*)parameter;
    while (true)
    {
        serialReader->readData();
        vTaskDelay(1 / portTICK_RATE_MS);
    }
}

void Aux_Serial_Reader::init(uint8_t rx, uint8_t tx)
{
    aux_serial = new HardwareSerial(rx, tx);
    aux_rx = rx;
    aux_tx = tx;
    xTaskCreate(aux_serial_trigger_read, "check_aux_serial_data", 50, this, 20, &auxSerial_taskHandle);
    vTaskSuspend(auxSerial_taskHandle);
}


void Aux_Serial_Reader::readData()
{
    switch (activeProtocol)
    {
        case NONE:

        break;

        case IBUS:
            ibus.loop();
        break;

        default:

        break;
    }
}

void Aux_Serial_Reader::begin()
{
    vTaskResume(auxSerial_taskHandle);
}

void Aux_Serial_Reader::end()
{
    vTaskSuspend(auxSerial_taskHandle);
}

void Aux_Serial_Reader::setProtocol(AUX_SERIAL_PROTOCOL protocol)
{
    switch (activeProtocol)
    {
        case NONE:
        break;

        case IBUS:
            ibus.end();
        break;

        case PPM:
            ppm = nullptr;
        default:

        break;
    }
    activeProtocol = protocol;
    switch (activeProtocol)
    {
        case NONE:
        break;

        case IBUS:
            ibus.begin(*aux_serial);
        break;

        case PPM:
            ppm = new PPMReader(aux_rx, 10);
        default:

        break;
    }
}

uint16_t Aux_Serial_Reader::getChannel(uint8_t channel)
{

    switch (activeProtocol)
    {

        case IBUS:
            return ibus.readChannel(channel);
        break;

        case PPM:
            return ppm->latestValidChannelValue(channel, 0);
        break;

        default:
            return 0;
        break;
    }
}

void Aux_Serial_Reader::getChannels(uint16_t *channelBuf)
{
    switch (activeProtocol)
    {

        case IBUS:
            for (int i = 0; i < ibus.PROTOCOL_CHANNELS; i++)
            {
                channelBuf[i] = ibus.readChannel(i);
            }
        break;

        case PPM:
            for (int i = 0; i < 10; i++)
            {
                channelBuf[i] = ppm->latestValidChannelValue(i, 0);
            }
        default:

        break;
    }
}

Aux_Serial_Reader AUX_Serial_reader;
