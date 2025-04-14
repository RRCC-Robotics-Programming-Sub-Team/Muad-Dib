#include "OrientationControl.h"

OrientationControl::OrientationControl() {}

void OrientationControl::init() {
    Wire.begin();
    if (!bno.begin_I2C()) {
        Serial.println("BNO08x not detected!");
        while (1);
    }
    bno.enableReport(SH2_ACCELEROMETER);
}

bool OrientationControl::isFlipped() {
    if (bno.getSensorEvent(&orientation)) {
        float z = orientation.un.accelerometer.z;
        Serial.print("Accelerometer Z: ");
        Serial.println(z);  // Print z value for debugging

        // If the z-value is below a threshold, consider it flipped
        if (z < -4.0) {  // Adjusted threshold for flipping detection
            unsigned long currentMillis = millis();
            if (currentMillis - lastFlipTime > debounceDelay) {
                orientationInverted = !orientationInverted;  // Flip state change
                lastFlipTime = currentMillis;  // Update last flip time
                Serial.println("Orientation flipped! Adjusting control...");
                return true;
            }
        }
    }
    return false;
}

bool OrientationControl::getOrientationInverted() const {
    return orientationInverted;
}
