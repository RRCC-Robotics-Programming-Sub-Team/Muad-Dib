#ifndef DIRECTIONCONTROL_H
#define DIRECTIONCONTROL_H

#include "Arduino.h"
#include "IMUControl.h"  // For IMU handling

class DirectionControl {
public:    
    DirectionControl();   
    void init(IMUControl* imu, MotorControl* motor); // Initializes the direction control
    void update();  // Called in loop to manage correction logic     
    void memorizeDirection(); // Memorizes the current direction    
    void correctDirection(); // Corrects the direction towards the memorized direction    
    bool isDirectionCorrect(); // Checks if the robot is in the memorized direction
    bool isInitialDirectionSet() const;
    void resetTimer();  // Call after an avoidance to delay correction

private:    
    IMUControl* _imu;
    MotorControl* _motor;
    float initialYaw;
    bool initialDirectionSet;
    unsigned long startTime;
    unsigned long lastCorrectionTime;
    bool hasAvoided;
    unsigned long avoidanceEndTime;

    const unsigned long initDelay = 2000;               // Time before locking direction
    const unsigned long correctionInterval = 5000;      // Time between corrections
    const unsigned long avoidanceRecoveryTime = 3500;   // Pause after avoiding object
};

#endif
