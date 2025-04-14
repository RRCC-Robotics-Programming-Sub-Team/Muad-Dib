#include <Arduino.h>
#include "RobotController.h"

#define ENA 5
#define IN1 6
#define IN2 7
#define ENB 3
#define IN3 4
#define IN4 2

void RobotController::setupMotors() {  pinMode(ENA, OUTPUT);  
pinMode(IN1, OUTPUT);  
pinMode(IN2, OUTPUT);  
pinMode(ENB, OUTPUT);  
pinMode(IN3, OUTPUT);  
pinMode(IN4, OUTPUT);
}

void RobotController::moveForward() {  analogWrite(ENA, 150);  analogWrite(ENB, 150);  
digitalWrite(IN1, HIGH);  digitalWrite(IN2, LOW);  
digitalWrite(IN3, HIGH);  digitalWrite(IN4, LOW);
}

void RobotController::moveBackward() {  analogWrite(ENA, 150);  analogWrite(ENB, 150);  
digitalWrite(IN1, LOW);  
digitalWrite(IN2, HIGH);  digitalWrite(IN3, LOW);  
digitalWrite(IN4, HIGH);
}

void RobotController::turnLeft() {  analogWrite(ENA, 150);  analogWrite(ENB, 150);  
digitalWrite(IN1, LOW);  
digitalWrite(IN2, HIGH);  digitalWrite(IN3, HIGH);  digitalWrite(IN4, LOW);
}

void RobotController::turnRight() {  analogWrite(ENA, 150);  analogWrite(ENB, 150);  
digitalWrite(IN1, HIGH);  digitalWrite(IN2, LOW);  
digitalWrite(IN3, LOW);  
digitalWrite(IN4, HIGH);
}

void RobotController::stopMotors() {  digitalWrite(IN1, LOW);  
digitalWrite(IN2, LOW);  
digitalWrite(IN3, LOW);  
digitalWrite(IN4, LOW);  analogWrite(ENA, 0);  
analogWrite(ENB, 0);
}

void RobotController::avoidObstacle() {  moveBackward();  
delay(600);  
turnRight();  
delay(500);  
stopMotors();
}