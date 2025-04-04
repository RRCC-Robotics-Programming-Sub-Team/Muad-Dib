#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

#include "Arduino.h"
#include <NewPing.h>

class UltrasonicSensor {
public:
    UltrasonicSensor(int triggerPin, int echoPin);
    int getDistance();

private:
    int _triggerPin, _echoPin;
    NewPing sonar;
};

#endif
