#ifndef ROBOT_CONTROLLER_H
#define ROBOT_CONTROLLER_H

class RobotController {
public:  
void setupMotors();  
void moveForward();  
void moveBackward();  
void turnLeft();  
void turnRight();  
void stopMotors();  
void avoidObstacle();};

#endif