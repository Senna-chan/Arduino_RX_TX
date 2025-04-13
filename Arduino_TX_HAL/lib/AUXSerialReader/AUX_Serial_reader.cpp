#include "AUX_Serial_reader.h"


void aux_serial_trigger_read(void* parameter){
    Aux_Serial_Reader *serialReader = (Aux_Serial_Reader*)parameter;
    while (true)
    {
//        serialReader->readData();
//        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}

//void aux_tx_done(UART_HandleTypeDef* huart){
//    AUX_Serial_reader.readData();
//}
//
//void aux_rx_done(UART_HandleTypeDef* huart){
//
//}
//
//void aux_error(UART_HandleTypeDef* huart){
//    SerialPrintf("Error '%d' in AUX_Serial.\n", huart->ErrorCode);
//}

void Aux_Serial_Reader::init(UART_HandleTypeDef *serial)
{
    aux_serial = serial;

//    HAL_UART_RegisterCallback(aux_serial, HAL_UART_TX_COMPLETE_CB_ID, aux_tx_done);
//    HAL_UART_RegisterCallback(aux_serial, HAL_UART_RX_COMPLETE_CB_ID, aux_rx_done);
//    HAL_UART_RegisterCallback(aux_serial, HAL_UART_ERROR_CB_ID, aux_error);
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
        break;

        default:

        break;
    }
    activeProtocol = protocol;
    switch (activeProtocol)
    {
        case NONE:
        break;

        case IBUS:
            ibus.begin(aux_serial);
        break;

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

        default:

        break;
    }
}

Aux_Serial_Reader AUX_Serial_reader;
