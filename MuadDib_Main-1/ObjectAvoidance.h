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



/* ─────────────────────────────────────────────────────────────────────────────
   RRCC Space Grant Robotics — Muad-Dib

   CREDITS
   Lead Programmer: Bradley T. Harz
   Team:            Merwin Mendoza, Melissa Heng

   © 2025 RRCC Space Grant Robotics Team.
   License (code): Apache-2.0 — see LICENSE
   License (docs/images in repo): CC BY 4.0 — see LICENSE-docs
   ──────────────────────────────────────────────────────────────────────────── */
