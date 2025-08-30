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



/* ─────────────────────────────────────────────────────────────────────────────
   RRCC Space Grant Robotics — Muad-Dib

   CREDITS
   Lead Programmer: Bradley T. Harz
   Team:            Merwin Mendoza, Melissa Heng

   © 2025 RRCC Space Grant Robotics Team.
   License (code): Apache-2.0 — see LICENSE
   License (docs/images in repo): CC BY 4.0 — see LICENSE-docs
   ──────────────────────────────────────────────────────────────────────────── */
