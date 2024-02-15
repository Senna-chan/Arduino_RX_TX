#include "config.h"
#include <nrf24.hpp>

#include "sharedNRF.h"
bool isTransmitter = true;

void common_nRFInit() {
    nRF24_CE_L();
    delay(5);
    if (!nRF24_Check()) {
        Serial.println("NRF Module not found");
        Error_Handler();
    }

    nRF24_Init();

    // Set RF channel
    nRF24_SetRFChannel(40);

    // Set data rate
    nRF24_SetDataRate(nRF24_DR_1Mbps);

    // Set CRC scheme
    nRF24_SetCRCScheme(nRF24_CRC_2byte);

    // Set address width, its common for all pipes (RX and TX)
    nRF24_SetAddrWidth(3);

    // Configure RX PIPE
    if (!isTransmitter) {
        nRF24_SetAddr(nRF24_PIPE0, nrfAddress); 	// Set RX Pipe
    }
    else {
        nRF24_SetAddr(nRF24_PIPE0, nrfAddress); 	// Set RX Pipe
        nRF24_SetAddr(nRF24_PIPETX, nrfAddress);   // Set TX Pipe
        nRF24_SetAutoRetr(nRF24_ARD_250us, 10);
    }
    nRF24_SetRXPipe(nRF24_PIPE0, nRF24_AA_ON, 32); // Auto-ACK: enabled, payload length: 32 bytes

    // Set TX power
    nRF24_SetTXPower(nRF24_TXPWR_0dBm);

    // Enable DPL
    nRF24_SetDynamicPayloadLength(nRF24_DPL_ON);

    nRF24_SetPayloadWithAck(1);


    // Enable Auto-ACK for pipe#0 (for ACK packets)
    nRF24_EnableAA(nRF24_PIPE0);

    if (!isTransmitter) {
        // Set operational mode (PRX == receiver)
        nRF24_SetOperationalMode(nRF24_MODE_RX);
    }
    else {
        nRF24_SetAutoRetr(nRF24_ARD_250us, 3);


        nRF24_SetOperationalMode(nRF24_MODE_TX);
    }
    // Clear any pending IRQ flags
    nRF24_ClearIRQFlags();

    // Wake the transceiver
    nRF24_SetPowerMode(nRF24_PWR_UP);


    //nRF24_DumpConfig();
    if (!isTransmitter) {
        // Put the transceiver to the RX mode
        nRF24_CE_H();
    }
}
