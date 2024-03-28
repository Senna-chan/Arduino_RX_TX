#include <Arduino.h>

#include "CustomRC.h"
#include <Lpf2Hub.h>
#include <ArduinoTimer.h>


 // create a hub instance
Lpf2Hub hub;
byte steerMotor = (byte)MoveHubPort::C;
byte driveMotor = (byte)MoveHubPort::A;
byte gearMotor  = (byte)MoveHubPort::D;

bool shiftedFrom5to4 = false; // We need this because this shifting is a bit harse

bool tankMode = false;

int currentGear = 1;
int gearOffset = 0;
int driveSpeed = 0;
int steerSpeed = 0;
int steerAngle = 0;
bool autoShifting = false;

int desiredGear = 1;
int desiredGearOffset = 0;
int desiredDriveSpeed = 0;
int desiredSteerSpeed = 0;
bool desiredAutoShifting = false;

const int maxRPMDriveMotor = 300;

double voltage, current, driveCurrent, prevDriveRpm, driveRpm, desiredDriveRpm, steerRpm, gearRpm;
int gearEnc, prevGearEnc, desiredGearEnc, prevDriveEnc, prevSteerEnc, driveEnc, steerEnc, batteryLevel;

ArduinoTimer setDesiredValues;
CustomRC customRC;

// Channels
uint8_t driveChannel = 1;
uint8_t steerChannel = 2;
uint8_t gearChannel = 4;
uint8_t autoGearingChannel = 3;

// Steering
int32_t desiredSteerAngle = 0.0;
const int32_t max_steering_angle = 70;
int32_t steeringOffset = 0;

// Autoshifting
uint32_t rpmInRangeSince = 0;   ///< Tracking for how long it is in range
uint32_t rpmInRangeTime = 500; ///< RPM needs to be in range for x millis
uint32_t rpmOutRangeSince = 0;   ///< Tracking for how long it is in range
uint32_t rpmOutRangeTime = 1500; ///< RPM needs to be in range for x millis
uint32_t autoShiftAllowedAfter = 0;
uint32_t shiftingGracePeriod = 2000; ///<Only shift every x millis
double rpmInRangeValue = 10;    ///<Rpm needs to be in range of this to percentage

void setDriveSpeed() {
    driveSpeed = desiredDriveSpeed;
    hub.setTachoMotorSpeed(driveMotor, driveSpeed);
    switch (currentGear) {
    case 1:
    case 2:
    case 3:
    case 4:
        desiredDriveRpm = (double)map(driveSpeed, -100, 100, -maxRPMDriveMotor, maxRPMDriveMotor);
        break;
    case 5:
        desiredDriveRpm = (double)map(driveSpeed, -100, 100, -260, 260);
        break;
    case 6:
    case 7:
        desiredDriveRpm = (double)map(driveSpeed, -100, 100, -210, 210);
        break;
    case 8:
        desiredDriveRpm = (double)map(driveSpeed, -100, 100, -180, 180);
        break;
    }

}

void setSteerSpeed() {
    if (!tankMode)
    {
        steerAngle = desiredSteerAngle;
        hub.setAbsoluteMotorPosition(steerMotor, 100, desiredSteerAngle);
    }
    else
    {
        steerSpeed = desiredSteerSpeed;
        hub.setTachoMotorSpeed(steerMotor, steerSpeed);
    }
}

void shift() {
    desiredGear = constrain(desiredGear, 1, 8);

    //if (currentGear == 5 && desiredGear == 4 && abs(driveSpeed) > 10) {
    //    hub.stopTachoMotor(driveMotor);
    //}
    currentGear = desiredGear;
    gearOffset = desiredGearOffset;
    desiredGearEnc = (currentGear - 1) * 90 + gearOffset;
    hub.setAbsoluteMotorPosition(gearMotor, 100, desiredGearEnc, 100, BrakingStyle::HOLD);
}

void channelCallback(uint16_t* curChannels, uint16_t* prevChannels) {
    // Serial.println("DATA FROM RX");
    if (curChannels[gearChannel] == 1500 && prevChannels[gearChannel] == CustomRC::defMinValue) {
        desiredGear--;
    }
    else if (curChannels[gearChannel] == 1500 && prevChannels[gearChannel] == CustomRC::defMaxValue) {
        desiredGear++;
    }
    desiredDriveSpeed = map(curChannels[driveChannel], CustomRC::defMinValue, CustomRC::defMaxValue, -100, 100);
    desiredSteerSpeed = map(curChannels[steerChannel], CustomRC::defMinValue, CustomRC::defMaxValue, -100, 100);
    desiredSteerAngle = map(curChannels[steerChannel], CustomRC::defMinValue, CustomRC::defMaxValue, -max_steering_angle, max_steering_angle);

    desiredAutoShifting = curChannels[autoGearingChannel] == 2000;
}

void hubPropertyChangeCallback(void* hub, HubPropertyReference hubProperty, uint8_t* pData)
{
    Lpf2Hub* myHub = (Lpf2Hub*)hub;

    //Serial.print("HubProperty: ");
    //Serial.println((byte)hubProperty, HEX);

    if (hubProperty == HubPropertyReference::BATTERY_VOLTAGE)
    {
        batteryLevel = myHub->parseBatteryLevel(pData);
        return;
    }
}
// callback function to handle updates of sensor values
void portValueChangeCallback(void* hub, byte portNumber, DeviceType deviceType, uint8_t* pData)
{
    Lpf2Hub* myHub = (Lpf2Hub*)hub;

    if (portNumber == driveMotor) {
        if (deviceType == DeviceType::TECHNIC_XLARGE_LINEAR_MOTOR) {
            driveEnc = myHub->parseTachoMotor(pData);
        }
        //if (deviceType == DeviceType::CURRENT_SENSOR)
        //{
        //    driveCurrent = myHub->parseCurrentSensor(pData);
        //}

    }
    else if (portNumber == gearMotor) {
        if (deviceType == DeviceType::TECHNIC_LARGE_LINEAR_MOTOR) {
            gearEnc = myHub->parseTachoMotor(pData);
        }
    }
    else if (portNumber == steerMotor) {
        if (deviceType == DeviceType::TECHNIC_LARGE_LINEAR_MOTOR) {
            steerEnc = myHub->parseTachoMotor(pData);
        }
    } else{
        if (deviceType == DeviceType::VOLTAGE_SENSOR)
        {
            voltage = myHub->parseVoltageSensor(pData);
        }

        if (deviceType == DeviceType::CURRENT_SENSOR)
        {
            current = myHub->parseCurrentSensor(pData);
        }
    }


}

void rpmInRange(double currentRpm, double desiredRpm) {
    double minRange = abs(desiredRpm / rpmInRangeValue);
    double destRpm = abs(desiredRpm);
    double curRpm = abs(currentRpm);


    if (destRpm < 150) { // No autoshifting at low RPM
        rpmOutRangeSince = 0;
        rpmInRangeSince = 0;
        return;
    }

    //if (destRpm - minRange > currentRpm && desiredRpm + minRange < currentRpm) {
    if (curRpm > destRpm - minRange) {
        rpmOutRangeSince = 0;
        if (rpmInRangeSince == 0) rpmInRangeSince = millis();
    }
    else {
        rpmInRangeSince = 0;
        if (rpmOutRangeSince == 0) rpmOutRangeSince = millis();
    }

    if (rpmOutRangeSince != 0 && millis() - rpmOutRangeSince > rpmOutRangeTime) {
        if (currentGear == 1) return; // Cannot downshift
        if (autoShiftAllowedAfter > millis()) return; // We shifted recently
        autoShiftAllowedAfter = millis() + shiftingGracePeriod;
        Serial.println("Autoshift--");
        desiredGear--;
        return;
    }
    if (rpmInRangeSince != 0 && millis() - rpmInRangeSince > rpmInRangeTime) {
        if (currentGear == 8) return; // Cannot upshift
        if (autoShiftAllowedAfter > millis()) return; // We shifted recently
        autoShiftAllowedAfter = millis() + shiftingGracePeriod;
        Serial.println("Autoshift++");
        desiredGear++;
        return;
    }
}


void setup()
{
    setCpuFrequencyMhz(160);
    Serial.begin(115200);
    Serial.setTimeout(50);
    Serial2.begin(115200, SERIAL_8N1, 19, 18);
    customRC.init(&Serial2);
    customRC.configureChannelStreaming(100);
    customRC.attachChannelCallback(channelCallback);
    hub.init(); // initalize the MoveHub instance
    Serial.println("Started Lego tank");
}

// main loop
void loop()
{
    customRC.loop();
    // connect flow. Search for BLE services and try to connect if the uuid of the hub is found
    if (hub.isConnecting())
    {
        hub.connectHub();
        if (hub.isConnected())
        {
            delay(250);
            hub.setLedColor(PINK);
            delay(50);
            hub.activateHubPropertyUpdate(HubPropertyReference::BATTERY_VOLTAGE, hubPropertyChangeCallback);
            delay(50);
            hub.activatePortDevice((byte)MoveHubPort::CURRENT, portValueChangeCallback);
            delay(50);
            hub.activatePortDevice((byte)MoveHubPort::VOLTAGE, portValueChangeCallback);
            delay(50);
            hub.activatePortDevice(driveMotor, (byte)DeviceType::TECHNIC_XLARGE_LINEAR_MOTOR, portValueChangeCallback);
            delay(50);
            hub.activatePortDevice(steerMotor, (byte)DeviceType::TECHNIC_LARGE_ANGULAR_MOTOR, portValueChangeCallback);
            delay(50);
            hub.activatePortDevice(gearMotor, (byte)DeviceType::TECHNIC_LARGE_ANGULAR_MOTOR, portValueChangeCallback);
            delay(50);
            //hub.activatePortDevice(driveMotor, (byte)MoveHubPort::CURRENT, portValueChangeCallback);
            //delay(50);
            //hub.setAccelerationProfile(driveMotor, 250);
            //hub.setAccelerationProfile(steerMotor, 250);
            //hub.setDecelerationProfile(driveMotor, 100);
            //hub.setDecelerationProfile(steerMotor, 100);
            Serial.println("Connected to HUB");
        }
        else
        {
            Serial.println("Failed to connect to HUB");
        }
    }

    if (setDesiredValues.TimePassed_Milliseconds(100)) {
        if (hub.isConnected())
        {
            driveRpm = ((((double)(driveEnc - prevDriveEnc) / (double)100) * 1000) * 60) / (double)360;
            driveRpm += prevDriveRpm;
            driveRpm /= 2; // Filtering
            steerRpm = ((((double)(steerEnc - prevSteerEnc) / (double)100) * 1000) * 60) / (double)360;
            gearRpm = ((((double)(gearEnc - prevGearEnc) / (double)100) * 1000) * 60) / (double)360;
            Serial.printf("Voltage %5.2f, current %8.2f,batterylevel %3d, driveEnc %8d, driveRPM %8.2f(%5.0f), steerEnc %8d, rpmSteer %8.2f, gear %d, gearEnc %5d(%5d)\t",
                voltage, current, batteryLevel, driveEnc, driveRpm,desiredDriveRpm, steerEnc, steerRpm, currentGear, gearEnc, desiredGearEnc);
            if (desiredAutoShifting != autoShifting) {
                autoShifting = desiredAutoShifting;
                Serial.printf("Autoshifting is now %s\r\n", autoShifting ? "on" : "off");
            }
            if (currentGear != desiredGear) {
                Serial.printf("New gear %d ", desiredGear);
                shift();
            }
            if (gearOffset != desiredGearOffset) {
                Serial.printf("new offset %d ", desiredGearOffset);
                shift();
            }
            if (steerSpeed != desiredSteerSpeed) {
                Serial.printf("new steerspeed %d ", desiredSteerSpeed);
                setSteerSpeed();
            }
            if (driveSpeed != desiredDriveSpeed) {
                Serial.printf("new drivespeed %d ", desiredDriveSpeed);
                setDriveSpeed();
            }

            if (autoShifting) {
                rpmInRange(driveRpm, desiredDriveRpm);
            }
            if (abs(desiredGearEnc - gearEnc) > 5) { // Spam setting the correct gear position
                shift();
            }
            Serial.println();
            prevSteerEnc = steerEnc;
            prevDriveEnc = driveEnc;
            prevGearEnc = gearEnc;
        }
    }

    if (Serial.available()) {
        char c = Serial.read();
        if (c == 'D') {
            desiredDriveSpeed = Serial.readStringUntil('\n').toInt();
            Serial.printf("PRE Setting drivespeed to %d\n", desiredDriveSpeed);
        }
        else if (c == 'S') {
            desiredSteerSpeed = Serial.readStringUntil('\n').toInt();
            desiredSteerAngle = desiredSteerSpeed;
            Serial.printf("PRE Setting steerspeed to %d\n", desiredSteerSpeed);
        }
        else if (c == 'G') {
            if (Serial.peek() == '-') {
                Serial.read();
                desiredGear--;
            }
            else if (Serial.peek() == '+') {
                Serial.read();
                desiredGear++;
            }
            else {
                desiredGear = Serial.readStringUntil('\n').toInt();
            }
            Serial.printf("Setting Gear to %d\n", desiredGear);
            shift(); // Shifting here to force the shift
        }
        else if (c == 'O') {
            desiredGearOffset = Serial.readStringUntil('\n').toInt();
            Serial.printf("PRE Setting GearOffset to %d\n", desiredGearOffset);
        }
        else if (c == 'e') {
            desiredDriveSpeed = 0;
            desiredSteerSpeed = 0;
            setDriveSpeed();
            setSteerSpeed();
            Serial.printf("FULLSTOP");
        }
        else if (c == 'E'){
            Serial.println("Shutting down hub");
            desiredDriveSpeed = 0;
            desiredSteerSpeed = 0;
            desiredGear = 1;
            setDriveSpeed();
            setSteerSpeed();
            shift();

            delay(2000);
            hub.shutDownHub();
        }
        else if (c == 'C') {
            Serial.println("(re)connecting to hub");
            hub.init();
        }
        else if (c == 'R') {
            customRC.getChannels();
        }
        else if (c == '*') {
            ESP.restart();
        }
        else if (c == 'A') {
            desiredAutoShifting = !autoShifting;
        }
        else {
            Serial.printf("Command '%c' is not known\n",c);
            while (Serial.available()) Serial.read();
        }
    }
} // End of loop
