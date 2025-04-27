//
// Created by senyaa on 4/22/25.
//

#include "USBSerial.h"

#include "ArduMath.hpp"
#include "usb_otg.h"
#include "usbd_cdc_acm.h"

#include <usbd_cdc_acm_if.h>

int8_t USBD_CDC_TransmitComplete(uint8_t cdc_ch, uint8_t *Buf, uint32_t *Len, uint8_t epnum){
    USBSerial::getInstance(cdc_ch)->handleISR(BaseSerial::TX_EVENT, Buf, Len);
    return USBD_OK;
}

int8_t USBD_CDC_Receive(uint8_t cdc_ch, uint8_t *Buf, uint32_t *Len) {
    USBSerial::getInstance(cdc_ch)->handleISR(BaseSerial::TX_EVENT, Buf, Len);
    return USBD_OK;
}

void USBSerial::create(uint8_t cdc_num){
    if (USBSerials[cdc_num] != nullptr) {
        Error_Handler();
    }
    USBSerials[cdc_num] = this;
    createBuffers();
}

void USBSerial::init(){
    // Nothing to do
}

void USBSerial::waitForNewData(){

}

USBSerial* USBSerial::getInstance(uint8_t cdc_num){
    if(cdc_num > NUMBER_OF_CDC){
        Error_Handler();
    }
    return USBSerials[cdc_num];
}
// These functions are not for user use
void USBSerial::handleISR(EventType eventType, uint8_t* buffer, uint32_t* length) {
    if (eventType == TX_EVENT) {
        tx_done = true;
        checkForTXPossible();
    }
    if (eventType == RX_EVENT) {
        rx_queue.insert(buffer, *length);
    }
}
void USBSerial::checkForTXPossible() {
    if (!tx_done) return;

    size_t amountToTransmit = min(static_cast<size_t>(SERIAL_DMA_BUFFER_SIZE), tx_queue.space_used());

    if (!amountToTransmit) {
        return;
    }
    tx_queue.retrieve(tx_dma_buf, amountToTransmit);
    CDC_Transmit(cdc_num, tx_dma_buf, amountToTransmit);
    tx_done = false;
}