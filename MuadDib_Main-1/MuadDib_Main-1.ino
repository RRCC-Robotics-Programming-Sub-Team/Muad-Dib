#include "MotorControl.h"
#include "UltrasonicSensor.h"
#include "IMUControl.h"
#include "OrientationControl.h"

OrientationControl orientation;
bool flipped = false;

// Initialize objects
MotorControl drive(2, 3, 4, 5, 6, 7);
UltrasonicSensor sonarCenter(8, 9);
UltrasonicSensor sonarRight(10, 11);
UltrasonicSensor sonarLeft(12, 13);
IMUControl imu;

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  Serial.println("Initializing motor driver...");
  drive.init();

  // Test motor movement
  Serial.println("Moving forward...");
  drive.forward(150, 1000);  // Move forward for 1 second
  delay(1000); // Wait for a second

  Serial.println("Moving backward...");
  drive.backward(150, 1000);  // Move backward for 1 second
  delay(1000);

  Serial.println("Stopping...");
  drive.fullStop();  // Stop after the movements
}


void loop() {
  flipped = orientation.isFlipped();
  Serial.print("Robot flipped? ");
  Serial.println(flipped ? "Yes" : "No");

  // Read distances
  int centerDist = sonarCenter.getDistance();
  int rightDist = sonarRight.getDistance();
  int leftDist = sonarLeft.getDistance();

  // Debug ultrasonic
  Serial.print("Center Distance: ");
  Serial.println(centerDist);
  Serial.print("Right Distance: ");
  Serial.println(rightDist);
  Serial.print("Left Distance: ");
  Serial.println(leftDist);

  // Yaw correction
  float yawRate = imu.getYawCorrection();
  Serial.print("Yaw Correction: ");
  Serial.println(yawRate);

  drive.stabilize(yawRate);

  // Obstacle avoidance logic
  if (centerDist > 0 && centerDist < 150) {
    Serial.println("Obstacle ahead: avoiding...");
    if (flipped) {
      drive.forward(150, 1000); // Move forward if flipped
    } else {
      drive.backward(150, 1000); // Move backward if not flipped
    }
    drive.fullStop();
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
    if (flipped) {
      drive.backward(150, 1000); // Move backward if flipped
    } else {
      drive.forward(150, 1000); // Move forward if not flipped
    }
  }

  delay(100);
}

