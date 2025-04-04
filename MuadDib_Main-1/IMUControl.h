#ifndef IMUCONTROL_H
#define IMUCONTROL_H

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_BNO08x.h>

class IMUControl {
public:
    IMUControl();
    void init();
    float getYawCorrection();

private:
    Adafruit_BNO08x bno085;
    sh2_SensorValue_t sensorValue;
};

#endif
