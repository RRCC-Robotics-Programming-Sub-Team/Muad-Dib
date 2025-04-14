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