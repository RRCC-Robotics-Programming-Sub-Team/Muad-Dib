#ifndef OBJECT_AVOIDANCE_H
#define OBJECT_AVOIDANCE_H

#include "UltrasonicSensor.h"
#include "MotorControl.h"
#include "DirectionControl.h"

class ObjectAvoidance {
public:
    ObjectAvoidance(UltrasonicSensor& sonar, MotorControl& motor, DirectionControl& direction);
    void init();
    void checkForObstacles();

private:
    UltrasonicSensor& _sonar;
    MotorControl& _motor;
    DirectionControl& _direction;
    const int obstacleThreshold = 20;  // centimeters
};

#endif
