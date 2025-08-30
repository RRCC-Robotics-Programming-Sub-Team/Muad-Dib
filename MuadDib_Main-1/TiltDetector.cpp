#include <Wire.h>
#include <math.h>
#include "TiltDetector.h"

bool TiltDetector::begin() {  
Wire.begin();  
if (!bno085.begin_I2C()) {    
return false;  
}  bno085.enableReport(SH2_ROTATION_VECTOR);  bno085.enableReport(SH2_GYROSCOPE_CALIBRATED);  bno085.enableReport(SH2_ACCELEROMETER);  
return true;
}

TiltStatus TiltDetector::getTiltStatus() {  if (bno085.getSensorEvent(&sensorValue)) {    
if (sensorValue.sensorId == SH2_ROTATION_VECTOR) {      
float qw = sensorValue.un.rotationVector.real;      
float qx = sensorValue.un.rotationVector.i;      
float qy = sensorValue.un.rotationVector.j;      
float qz = sensorValue.un.rotationVector.k;  
    
float sinp = 2.0 * (qw * qy - qz * qx);      
float pitchRad = abs(sinp) >= 1 ? copysign(PI / 2, sinp) : asin(sinp);      
float pitchDeg = pitchRad * 180.0 / PI; 

if (pitchDeg > 25.0) return TILT_UP;      else if (pitchDeg < -25.0) return TILT_DOWN;    
}  
}  
return FLAT;
}

bool TiltDetector::checkPitchMovingUp() {  
if (bno085.getSensorEvent(&sensorValue)) {    
if (sensorValue.sensorId == SH2_ROTATION_VECTOR) {      
float qw = sensorValue.un.rotationVector.real;      
float qx = sensorValue.un.rotationVector.i;      
float qy = sensorValue.un.rotationVector.j;      
float qz = sensorValue.un.rotationVector.k;      

float sinp = 2.0 * (qw * qy - qz * qx);      float pitchRad = abs(sinp) >= 1 ? copysign(PI / 2, sinp) : asin(sinp);      
float pitchDeg = pitchRad * 180.0 / PI;

return pitchDeg > 0;    
}  
}  
return false;
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
