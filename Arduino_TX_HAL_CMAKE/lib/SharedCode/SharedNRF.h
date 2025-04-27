#ifndef SHARED_NRF_H
#define SHARED_NRF_H

#include <nrf24.hpp>

extern nRF24 Main_nRF;

void common_nRFInit(bool isTransmitter);

#endif
