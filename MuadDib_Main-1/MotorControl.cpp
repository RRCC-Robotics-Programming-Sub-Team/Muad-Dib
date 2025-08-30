#include "MotorControl.h"

MotorControl::MotorControl(int ena, int in1, int in2, int in3, int in4, int enb) {
    _ENA = ena; _IN1 = in1; _IN2 = in2;
    _IN3 = in3; _IN4 = in4; _ENB = enb;
}

void MotorControl::init() {
    pinMode(_ENA, OUTPUT);
    pinMode(_ENB, OUTPUT);
    pinMode(_IN1, OUTPUT);
    pinMode(_IN2, OUTPUT);
    pinMode(_IN3, OUTPUT);
    pinMode(_IN4, OUTPUT);
}

void MotorControl::forward(int speed, int delay_time) {
    digitalWrite(_IN1, HIGH);
    digitalWrite(_IN2, LOW);
    digitalWrite(_IN3, HIGH);
    digitalWrite(_IN4, LOW);
    analogWrite(_ENA, speed);
    analogWrite(_ENB, speed);
    delay(delay_time);
}

void MotorControl::backward(int speed, int delay_time) {
    digitalWrite(_IN1, LOW);
    digitalWrite(_IN2, HIGH);
    digitalWrite(_IN3, LOW);
    digitalWrite(_IN4, HIGH);
    analogWrite(_ENA, speed);
    analogWrite(_ENB, speed);
    delay(delay_time);
}

void MotorControl::turnLeft(int speed, int delay_time) {
    digitalWrite(_IN1, HIGH);
    digitalWrite(_IN2, LOW);
    digitalWrite(_IN3, LOW);
    digitalWrite(_IN4, HIGH);
    analogWrite(_ENA, speed);
    analogWrite(_ENB, speed);
    delay(delay_time);
}

void MotorControl::turnRight(int speed, int delay_time) {
    digitalWrite(_IN1, LOW);
    digitalWrite(_IN2, HIGH);
    digitalWrite(_IN3, HIGH);
    digitalWrite(_IN4, LOW);
    analogWrite(_ENA, speed);
    analogWrite(_ENB, speed);
    delay(delay_time);
}

void MotorControl::fullStop() {
    digitalWrite(_IN1, LOW);
    digitalWrite(_IN2, LOW);
    digitalWrite(_IN3, LOW);
    digitalWrite(_IN4, LOW);
    analogWrite(_ENA, 0);
    analogWrite(_ENB, 0);
}

void MotorControl::stabilize(float yawRate) {
    int leftSpeed = 150 + (yawRate * 50);
    int rightSpeed = 150 - (yawRate * 50);
    analogWrite(_ENA, constrain(leftSpeed, 0, 255));
    analogWrite(_ENB, constrain(rightSpeed, 0, 255));
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
