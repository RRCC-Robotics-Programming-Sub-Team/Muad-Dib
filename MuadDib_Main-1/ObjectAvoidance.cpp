#include "ObjectAvoidance.h"
#include "Arduino.h"

ObjectAvoidance::ObjectAvoidance(UltrasonicSensor& sonar, MotorControl& motor, DirectionControl& direction)
    : _sonar(sonar), _motor(motor), _direction(direction) {}

void ObjectAvoidance::init() {
    // Initialization logic if needed
    Serial.println("Object avoidance system ready.");
}

void ObjectAvoidance::checkForObstacles() {
    int distance = _sonar.getDistance();
    Serial.print("Obstacle Check Distance: ");
    Serial.println(distance);

    if (distance > 0 && distance < obstacleThreshold) {
        Serial.println("Obstacle detected! Taking evasive action...");

        _motor.backward(150, 500);    // back up
        _motor.fullStop();
        _motor.turnRight(150, 500);   // turn
        _motor.fullStop();

        _direction.resetTimer();      // delay direction correction briefly
    }
}



/* ─────────────────────────────────────────────────────────────────────────────
   RRCC Space Grant Robotics — Muad-Dib

   CREDITS
   Lead Programmer: Bradley T. Harz
   Team:            Merwin Mendoza, Melissa Heng

   © 2025 RRCC Space Grant Robotics Team.
   License (code): Apache-2.0 — see LICENSE
   License (docs/images in repo): CC BY 4.0 — see LICENSE-docs
   ──────────────────────────────────────────────────────────────────────────── */
