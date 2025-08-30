/* SPDX-License-Identifier: Apache-2.0 */
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



/* ─────────────────────────────────────────────────────────────────────────────
   RRCC Space Grant Robotics — Muad-Dib

   CREDITS
   Lead Programmer: Bradley T. Harz
   Team:            Merwin Mendoza, Melissa Heng

   © 2025 RRCC Space Grant Robotics Team.
   License (code): Apache-2.0 — see LICENSE
   License (docs/images in repo): CC BY 4.0 — see LICENSE-docs
   ──────────────────────────────────────────────────────────────────────────── */
