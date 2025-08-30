#ifndef TILT_DETECTOR_H
#define TILT_DETECTOR_H

#include <Adafruit_BNO08x.h>

enum TiltStatus {  
FLAT,  
TILT_UP,  
TILT_DOWN
};

class TiltDetector {
public:  
bool begin();  
TiltStatus getTiltStatus();  
bool checkPitchMovingUp();

private:  
Adafruit_BNO08x bno085;  sh2_SensorValue_t sensorValue;
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
