#include "IMUControl.h"

IMUControl::IMUControl() {}

void IMUControl::init() {
    Wire.begin();
    if (!bno085.begin_I2C()) {
        Serial.println("IMU not detected!");
        while (1);
    }
    bno085.enableReport(SH2_RAW_GYROSCOPE);
}

float IMUControl::getYawCorrection() {
    if (bno085.getSensorEvent(&sensorValue)) {
        return sensorValue.un.gyroscope.z;
    }
    return 0.0;
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
