#include "IMUControl.h"
#include <Wire.h>
#include <Adafruit_BNO08x.h>
#include "MotorControl.h"

extern Adafruit_BNO08x bno085;  // Make sure this is defined in your main .ino file

IMUControl::IMUControl() {}

void IMUControl::init() {
    Wire.begin();
    if (!bno085.begin_I2C()) {
        Serial.println("IMU not detected!");
        while (1);
    }

    bno085.enableReport(SH2_RAW_GYROSCOPE);
    bno085.enableReport(SH2_ROTATION_VECTOR);  // Required for yaw angle
    bno085.enableReport(SH2_ACCELEROMETER);    // Required for acceleration magnitude
}

float IMUControl::getYawCorrection() {
    if (bno085.getSensorEvent(&sensorValue)) {
        return sensorValue.un.gyroscope.z;
    }
    return 0.0;
}

float IMUControl::getYaw() {
    if (bno085.getSensorEvent(&sensorValue)) {
        // The yaw angle isn't directly provided as `yaw`, but must be computed from quaternions.
        float qw = sensorValue.un.rotationVector.real;
        float qx = sensorValue.un.rotationVector.i;
        float qy = sensorValue.un.rotationVector.j;
        float qz = sensorValue.un.rotationVector.k;

        // Yaw (Z-axis rotation)
        float siny_cosp = 2.0 * (qw * qz + qx * qy);
        float cosy_cosp = 1.0 - 2.0 * (qy * qy + qz * qz);
        float yawRad = atan2(siny_cosp, cosy_cosp);

        return yawRad * 180.0 / PI;  // Convert to degrees
    }
    return 0.0;
}

float IMUControl::getPitchCorrection() {
    if (bno085.getSensorEvent(&sensorValue)) {
        return sensorValue.un.gyroscope.x;  // X-axis typically represents pitch rotation
    }
    return 0.0;
}

float IMUControl::getAccelerationMagnitude() {
    if (bno085.getSensorEvent(&sensorValue)) {
        return sqrt(
            pow(sensorValue.un.accelerometer.x, 2) +
            pow(sensorValue.un.accelerometer.y, 2) +
            pow(sensorValue.un.accelerometer.z, 2)
        );
    }
    return 0.0;
}

bool IMUControl::isSensorReporting() {
  return bno085.getSensorEvent(&sensorValue);  // Returns true if sensor is streaming data
}

void IMUControl::stabilizeToYaw(float targetYaw, MotorControl& motor) {
    float currentYaw = getYaw();
    float error = targetYaw - currentYaw;

    Serial.print("Stabilizing to Yaw. Target: ");
    Serial.print(targetYaw);
    Serial.print("°, Current: ");
    Serial.print(currentYaw);
    Serial.print("°, Error: ");
    Serial.println(error);

    int correctionSpeed = constrain(error * 3, -100, 100);  // Simple proportional gain

    if (abs(error) > 3) {
        if (correctionSpeed > 0)
            motor.turnRight(abs(correctionSpeed), 200);
        else
            motor.turnLeft(abs(correctionSpeed), 200);
        motor.fullStop();
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
