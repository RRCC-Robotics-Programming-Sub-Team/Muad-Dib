// directioncontrol.cpp
#include "DirectionControl.h"
#include "MotorControl.h"

DirectionControl::DirectionControl()
  : _imu(nullptr),
    initialYaw(0),
    initialDirectionSet(false),
    startTime(0),
    lastCorrectionTime(0),
    hasAvoided(false),
    avoidanceEndTime(0) {}
    
void DirectionControl::init(IMUControl* imu, MotorControl* motor) {    
    _imu = imu;
    _motor = motor;    
    startTime = millis();
}

void DirectionControl::update() {    
   unsigned long currentMillis = millis();    

// Memorize initial direction after delay         
if (!initialDirectionSet && currentMillis - startTime >= initDelay) {
    initialYaw = _imu->getYaw();        
    initialDirectionSet = true;        
    lastCorrectionTime = currentMillis;        
    Serial.print("Initial direction memorized: ");        
    Serial.println(initialYaw);    
}    

if (!initialDirectionSet) return;    

// After object avoidance, wait 3.5 seconds before correcting    
if (hasAvoided && currentMillis < avoidanceEndTime) {        
    return;    
} else if (hasAvoided && currentMillis >= avoidanceEndTime) {        
        hasAvoided = false;        
        correctDirection();        
        lastCorrectionTime = currentMillis;    
    }    

// Regular correction every 5 seconds    
    if (!hasAvoided && currentMillis - lastCorrectionTime >= correctionInterval) {        
        correctDirection();        
        lastCorrectionTime = currentMillis;    
    }
}

void DirectionControl::correctDirection() {    
    float currentYaw = _imu->getYaw();    
    float error = initialYaw - currentYaw;    
    Serial.print("Correcting direction. Error: ");    
    Serial.println(error);  
  
    // Apply correction logic using IMUControl methods or motor adjustment    
    // This part depends on your motor stabilization implementation    
    _imu->stabilizeToYaw(initialYaw, *_motor);
}

bool DirectionControl::isInitialDirectionSet() const {    
    return initialDirectionSet;
}

void DirectionControl::resetTimer() {    
    hasAvoided = true;    
    avoidanceEndTime = millis() + avoidanceRecoveryTime;
}
