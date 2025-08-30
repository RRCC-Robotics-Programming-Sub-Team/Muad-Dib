#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include "Arduino.h"

class MotorControl {
public:
    MotorControl(int ena, int in1, int in2, int in3, int in4, int enb);
    void init();
    void forward(int speed, int delay_time);
    void backward(int speed, int delay_time);
    void turnLeft(int speed, int delay_time);
    void turnRight(int speed, int delay_time);
    void fullStop();
    void stabilize(float yawRate);

private:
    int _ENA, _IN1, _IN2, _IN3, _IN4, _ENB;
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
