// OrientationControl.h
#ifndef ORIENTATIONCONTROL_H
#define ORIENTATIONCONTROL_H

#include "Arduino.h"
#include <Adafruit_BNO08x.h>

class OrientationControl {
public:
    OrientationControl();
    void init();
    bool isFlipped();
    bool getOrientationInverted() const;

private:
    Adafruit_BNO08x bno;
    sh2_SensorValue_t orientation;
    bool orientationInverted = false;
};

#endif
