#include "I2CHelpers.h"
#include <stdio.h>

bool I2CDeviceConnected(I2C_HandleTypeDef *i2c, uint8_t address) {
    auto hal_status = HAL_I2C_IsDeviceReady(i2c, address << 1, 3, 5);
    return hal_status == HAL_OK;
}

void scanI2C(I2C_HandleTypeDef *i2c) {
	uint8_t error, address;
	int nDevices;

	printf("Scanning I2C Bus\n");

	nDevices = 0;
	printf("     ");
	for (int i = 0; i <= 0x0F; i++) {
		printf("0x%02X ",i);
	}
    printf("\n");
	printf("0x00      ");
	for (address = 1; address <= 0x7F; address++) {
		if (address % 0x10 == 0) {
			printf("\n");
			printf("0x%02X ", address);
		}
		// The i2c_scanner uses the return value of
		// the Write.endTransmisstion to see if
		// a device did acknowledge to the address.
		auto hal_status = HAL_I2C_IsDeviceReady(i2c, address << 1, 3, 5);
		if (hal_status == HAL_OK) {
			printf("0x%02X ", address);
			nDevices++;
		} else if (hal_status != HAL_TIMEOUT){
			printf("ERR  ");
		} else {
			printf("---- ");
		}
		HAL_Delay(1);
	}
	printf("\n");
	if (nDevices == 0) {
		printf("No I2C devices found\n");
    } else {
		printf("Found %d I2C devices\n", nDevices);
	}
}