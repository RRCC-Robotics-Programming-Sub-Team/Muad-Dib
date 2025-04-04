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
