#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int triggerPin, int echoPin) 
    : sonar(triggerPin, echoPin, 200) {
    _triggerPin = triggerPin;
    _echoPin = echoPin;
}

int UltrasonicSensor::getDistance() {
    return sonar.ping_cm();
}
