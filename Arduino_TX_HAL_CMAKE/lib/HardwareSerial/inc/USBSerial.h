//
// Created by senyaa on 4/22/25.
//

#ifndef USBSERIAL_H
#define USBSERIAL_H

#include "BaseSerial.h"
#include "usb_device.h"
#include "usbd_cdc_acm.h"

#include <map>

class USBSerial : public BaseSerial {
public:
    void create(uint8_t cdc_num);
    void init();

    void waitForNewData();
    static USBSerial* getInstance(uint8_t cdc_num);
    // These functions are not for user use
    void handleISR(EventType eventType, uint8_t *buffer, uint32_t *length);
    uint8_t get_cdc_num(){return cdc_num;};
private:
    void checkForTXPossible() override;
    bool tx_done = true;
    uint8_t cdc_num;
    uint8_t tx_dma_buf[SERIAL_DMA_BUFFER_SIZE] = { 0 };
};

USBSerial* USBSerials[NUMBER_OF_CDC] = {0};

#endif //USBSERIAL_H
