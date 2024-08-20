// 
// 
// 

#include "CheapLegoHub.h"

void CheapLegoHub::StartScan()
{
	BLE.scan(true);
}

bool CheapLegoHub::Connect()
{
	while (true)
	{
		BLEDevice bleDevice = BLE.available();
		if (!bleDevice) return false;
		//Serial.print("Found: ");
		//Serial.print(bleDevice.address());
		//Serial.print(" '");
		//Serial.print(bleDevice.localName());
		//Serial.print("' ");
		//Serial.print(bleDevice.advertisedServiceUuid());
		//Serial.println();

		if (bleDevice.advertisedServiceUuid().equals(deviceUUID))
		{
			//Serial.println("Found the device we are looking for");
			device = bleDevice;
			BLE.stopScan();
			break;
		}
	}
	// discover peripheral attributes
	device.connect();
	if (!device.discoverAttributes()) {
		Serial.println("Failed to get attributes");
		Disconnect();
		return false;
	}


	// loop the services of the peripheral and explore each
	for (int i = 0; i < device.serviceCount(); i++) {
		BLEService service = device.service(i);
		//Serial.print("\nServiceUUID: ");
		//Serial.print(service.uuid());
		//Serial.print(" characteristics: ");
		for (int i = 0; i < service.characteristicCount(); i++) {
			BLECharacteristic characteristic = service.characteristic(i);
			//Serial.print(characteristic.uuid());
			//Serial.print(", ");
			if (!strcmp(service.uuid(), serviceUUID))
			{
				if(!strcmp(characteristic.uuid(), characteristicUUID))
				{
					//Serial.println("Found where we can write to");
					output = characteristic;
					bleDeviceFound = true;
					return true;
				}
			}
		}
	}
	return false;

}

bool CheapLegoHub::Disconnect()
{
	device.disconnect();
	return false;
}

void CheapLegoHub::Send()
{
	output.writeValue(dataBuffer, dataSize);
}

bool CheapLegoHub::SetValue(int a, int b, int c, int d, int e, int f)
{
	Serial.printf("Entry: a:%d,b:%d,c:%d,d:%d,e:%d,f:%d\n", a, b, c, d, e, f);
	memcpy(dataBuffer, stopCommand, dataSize);
	a = returnClippedValue(a);
	b = returnClippedValue(b);
	c = returnClippedValue(c);
	d = returnClippedValue(d);
	e = returnClippedValue(e);
	f = returnClippedValue(f);
	Serial.printf("Clipped: a:%d,b:%d,c:%d,d:%d,e:%d,f:%d\n", a, b, c, d, e, f);
	if (doDiagonalChange(&a, &b)){}
	if (doDiagonalChange(&c, &d)){}
	Serial.printf("Diag: a:%d,b:%d,c:%d,d:%d,e:%d,f:%d\n", a, b, c, d, e, f);
	if (a > 0)
	{
		dataBuffer[ABDirIndex] |= axis1bit;
	}
	else if (a < 0)
	{
		dataBuffer[ABDirIndex] |= (axis1bit << 1);
	}
	if (b > 0)
	{
		dataBuffer[ABDirIndex] |= axis2bit;
	}
	else if (b < 0)
	{
		dataBuffer[ABDirIndex] |= (axis2bit << 1);
	}

	if (c > 0)
	{
		dataBuffer[CDDirIndex] |= axis1bit;
	}
	else if (c < 0)
	{
		dataBuffer[CDDirIndex] |= (axis1bit << 1);
	}
	if (d > 0)
	{
		dataBuffer[CDDirIndex] |= axis2bit;
	}
	else if (d < 0)
	{
		dataBuffer[CDDirIndex] |= (axis2bit << 1);
	}

	if (e > 0)
	{
		dataBuffer[EFDirIndex] |= axis1bit;
	}
	else if (e < 0)
	{
		dataBuffer[EFDirIndex] |= (axis1bit << 1);
	}
	if (f > 0)
	{
		dataBuffer[EFDirIndex] |= axis2bit;
	}
	else if (f < 0)
	{
		dataBuffer[EFDirIndex] |= (axis2bit << 1);
	}

	if (a != 0 && b != 0)
	{
		dataBuffer[ABValueIndex] = abs(a);
	}
	else
	{
		dataBuffer[ABValueIndex] = a != 0 ? abs(a) : abs(b);
	}
	if (c != 0 && d != 0)
	{
		dataBuffer[CDValueIndex] = abs(c);
	}
	else
	{
		dataBuffer[CDValueIndex] = c != 0 ? abs(c) : abs(d);
	}

	dataBuffer[EValueIndex] = abs(e);
	dataBuffer[FValueIndex] = abs(f);

	for (int i = 0; i < dataSize; i++)
	{
		Serial.printf("%02X ", dataBuffer[i]);
	}
	Serial.println();
	Send();
	return true;
}

void CheapLegoHub::Stop()
{
	memcpy(dataBuffer, stopCommand, dataSize);
	Send();
}

bool CheapLegoHub::IsConnected()
{
	return bleDeviceFound;
}

int CheapLegoHub::returnClippedValue(int val)
{
	if (val > maxValue) return maxValue;
	if (val < -maxValue) return -maxValue;
	return val;
}

bool CheapLegoHub::doDiagonalChange(int* val1, int* val2)
{
	if (*val1 == 0 || *val2 == 0)
	{
		return false; // No change needed
	}
	int val1sign = *val1 > 0 ? 1 : -1;
	int val2sign = *val2 > 0 ? 1 : -1;
	if (abs(*val1) > abs(*val2))
	{
		*val2 = *val1;
		*val2 *= val2sign;
	}
	if (abs(*val2) > abs(*val1))
	{
		*val1 = *val2;
		*val1 *= val1sign;
	}
	return true;
}
