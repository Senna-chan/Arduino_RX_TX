#include "CheapLegoHub.h"
#include <ArduinoBLE.h>

bool demo = false;
CheapLegoHub lh;
void setup() {
    Serial.begin(115200);
    while (!Serial);

    // begin initialization
    if (!BLE.begin()) {
        Serial.println("starting Bluetooth� Low Energy module failed!");

        while (1);
    }

    Serial.println("Bluetooth� Low Energy Central - Peripheral Explorer");
    if (demo)
    {
        // start scanning for peripherals
        BLE.scan();
    }
    else
    {
        lh.StartScan();
    }
}

void loop() {
    if (!demo)
    {
        if (lh.IsConnected())
        {
            if (Serial.available())
            {
                String str = Serial.readStringUntil('\n');
                if (str.startsWith("s"))
                {
                    lh.Stop();
                }
                else 
                {
                    int16_t a = 0;
                    int16_t b = 0;
                    int16_t c = 0;
                    int16_t d = 0;
                    int16_t e = 0;
                    int16_t f = 0;
                    sscanf(str.c_str(), "%hd,%hd,%hd,%hd,%hd,%hd", &a, &b, &c, &d, &e, &f);
                    lh.SetValue(a, b, c, d, e, f);
                }
            }
        }
        else
        {
            lh.Connect();
        }
        return;
    }
    // check if a peripheral has been discovered
    BLEDevice peripheral = BLE.available();

    if (peripheral) {
        // discovered a peripheral, print out address, local name, and advertised service
        Serial.print("Found ");
        Serial.print(peripheral.address());
        Serial.print(" '");
        Serial.print(peripheral.localName());
        Serial.print("' ");
        Serial.print(peripheral.advertisedServiceUuid());
        Serial.println();

        // see if peripheral is a LED
        if (peripheral.localName().startsWith("JG_JMC-5334")) {
            // stop scanning
            BLE.stopScan();
            explorerPeripheral(peripheral);

            // peripheral disconnected, we are done
            while (1) {
                // do nothing
            }
        }
    }
}

void explorerPeripheral(BLEDevice peripheral) {
    // connect to the peripheral
    Serial.println("Connecting ...");

    if (peripheral.connect()) {
        Serial.println("Connected");
    }
    else {
        Serial.println("Failed to connect!");
        return;
    }

    // discover peripheral attributes
    Serial.println("Discovering attributes ...");
    if (peripheral.discoverAttributes()) {
        Serial.println("Attributes discovered");
    }
    else {
        Serial.println("Attribute discovery failed!");
        peripheral.disconnect();
        return;
    }

    // read and print device name of peripheral
    Serial.println();
    Serial.print("Device name: ");
    Serial.println(peripheral.deviceName());
    Serial.print("Appearance: 0x");
    Serial.println(peripheral.appearance(), HEX);
    Serial.println();

    // loop the services of the peripheral and explore each
    for (int i = 0; i < peripheral.serviceCount(); i++) {
        BLEService service = peripheral.service(i);

        exploreService(service);
    }

    Serial.println();

    // we are done exploring, disconnect
    Serial.println("Disconnecting ...");
    peripheral.disconnect();
    Serial.println("Disconnected");
}

void exploreService(BLEService service) {
    // print the UUID of the service
    Serial.print("Service ");
    Serial.println(service.uuid());

    // loop the characteristics of the service and explore each
    for (int i = 0; i < service.characteristicCount(); i++) {
        BLECharacteristic characteristic = service.characteristic(i);
        if (!strcmp(service.uuid(), "fff0") && !strcmp(characteristic.uuid(), "fff2"))
        {
            Serial.println("We found what we want to write to");
        }
        exploreCharacteristic(characteristic);
    }
}

void exploreCharacteristic(BLECharacteristic characteristic) {
    // print the UUID and properties of the characteristic
    Serial.print("\tCharacteristic ");
    Serial.print(characteristic.uuid());
    Serial.print(", properties 0x");
    Serial.print(characteristic.properties(), HEX);

    // check if the characteristic is readable
    if (characteristic.canRead()) {
        // read the characteristic value
        characteristic.read();

        if (characteristic.valueLength() > 0) {
            // print out the value of the characteristic
            Serial.print(", value 0x");
            printData(characteristic.value(), characteristic.valueLength());
        }
    }
    if (characteristic.canWrite())
    {
        Serial.print(", writable");
    }
    Serial.println();

    // loop the descriptors of the characteristic and explore each
    for (int i = 0; i < characteristic.descriptorCount(); i++) {
        BLEDescriptor descriptor = characteristic.descriptor(i);

        exploreDescriptor(descriptor);
    }
}

void exploreDescriptor(BLEDescriptor descriptor) {
    // print the UUID of the descriptor
    Serial.print("\t\tDescriptor ");
    Serial.print(descriptor.uuid());

    // read the descriptor value
    descriptor.read();

    // print out the value of the descriptor
    Serial.print(", value 0x");
    printData(descriptor.value(), descriptor.valueLength());

    Serial.println();
}

void printData(const unsigned char data[], int length) {
    for (int i = 0; i < length; i++) {
        unsigned char b = data[i];

        if (b < 16) {
            Serial.print("0");
        }

        Serial.print(b, HEX);
    }
}
