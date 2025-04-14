#ifndef IMUCONTROL_H
#define IMUCONTROL_H

#include "Arduino.h"
#include "MotorControl.h"
#include <Wire.h>
#include <Adafruit_BNO08x.h>

class IMUControl {
public:
    IMUControl();
    void init();
  int getCalibrationStatus();
  float getYawCorrection();
  float getPitchCorrection();
  float getAccelerationMagnitude();
  float getYaw();  // <<-- Add this
  bool isSensorReporting();
   void stabilizeToYaw(float targetYaw, MotorControl& motor); 

private:
    Adafruit_BNO08x bno085;
    sh2_SensorValue_t sensorValue;
};

#endif
