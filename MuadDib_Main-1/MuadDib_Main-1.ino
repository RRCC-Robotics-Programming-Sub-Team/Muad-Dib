#include "MotorControl.h"
#include "UltrasonicSensor.h"
#include "IMUControl.h"

// Initialize objects
// MotorControl constructor arguments: (ENA, IN1, IN2, IN3, IN4, ENB)
MotorControl drive(2, 3, 4, 5, 6, 7);

// Ultrasonic sensors: (trigger pin, echo pin)
UltrasonicSensor sonarCenter(8, 9);
UltrasonicSensor sonarRight(10, 11);
UltrasonicSensor sonarLeft(12, 13);

// IMU object
IMUControl imu;

void setup() {
  Serial.begin(115200);
  while (!Serial) {}  // wait for Serial Monitor if needed

  Serial.println("Initializing motor driver...");
  drive.init();  // Set motor pins to OUTPUT

  Serial.println("Initializing IMU...");
  imu.init();  // Initialize the BNO085 IMU (prints a confirmation if successful)
}

void loop() {
  // Read ultrasonic sensor distances
  int centerDist = sonarCenter.getDistance();
  int rightDist  = sonarRight.getDistance();
  int leftDist   = sonarLeft.getDistance();

  // Debug prints for ultrasonic sensors:
  Serial.print("Center Distance: ");
  Serial.println(centerDist);
  Serial.print("Right Distance: ");
  Serial.println(rightDist);
  Serial.print("Left Distance: ");
  Serial.println(leftDist);

  // Get yaw correction from the IMU and print it:
  float yawRate = imu.getYawCorrection();
  Serial.print("Yaw Correction: ");
  Serial.println(yawRate);

  // Apply a stabilization update (this only adjusts PWM speeds, not direction!)
  drive.stabilize(yawRate);

  // Obstacle avoidance logic:
  if (centerDist > 0 && centerDist < 150) {
    Serial.println("Obstacle ahead: backing up then turning right...");
    drive.backward(150, 1000);
    drive.fullStop(); // Brief stop between commands
    drive.turnRight(150, 1000);
  } 
  else if (rightDist > 0 && rightDist < 85) {
    Serial.println("Obstacle on right: turning left...");
    drive.turnLeft(150, 1000);
  } 
  else if (leftDist > 0 && leftDist < 85) {
    Serial.println("Obstacle on left: turning right...");
    drive.turnRight(150, 1000);
  } 
  else {
    Serial.println("Path clear: moving forward...");
    drive.forward(150, 1000);
  }
  
  // Small pause between cycles
  delay(100);
}
