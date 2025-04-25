//
// Created by senyaa on 4/22/25.
//

#ifndef USBSERIAL_H
#define USBSERIAL_H

#include "BaseSerial.h"
#include "usb_device.h"
#include "usbd_cdc_acm.h"

class USBSerial : public BaseSerial {
public:

    void create(uint8_t cdc_num);
    void init();

    void waitForNewData();
    static USBSerial* getInstance(uint8_t cdc_num);
    // These functions are not for user use
    void handleISR(EventType eventType, uint16_t pos);
    uint8_t get_cdc_num(){return cdc_num;};
private:
    uint8_t cdc_num;
};

std::dict<USBSerial> USBSerials;

#endif //USBSERIAL_H
