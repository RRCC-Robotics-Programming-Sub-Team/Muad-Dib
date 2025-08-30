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



/* ─────────────────────────────────────────────────────────────────────────────
   RRCC Space Grant Robotics — Muad-Dib

   CREDITS
   Lead Programmer: Bradley T. Harz
   Team:            Merwin Mendoza, Melissa Heng

   © 2025 RRCC Space Grant Robotics Team.
   License (code): Apache-2.0 — see LICENSE
   License (docs/images in repo): CC BY 4.0 — see LICENSE-docs
   ──────────────────────────────────────────────────────────────────────────── */
