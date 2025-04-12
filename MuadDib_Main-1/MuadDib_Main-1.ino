#include "MotorControl.h"
#include "UltrasonicSensor.h"
#include "IMUControl.h"
#include "OrientationControl.h"

OrientationControl orientation;
bool flipped = false;

// Initialize objects
// MotorControl constructor arguments: (ENA, IN1, IN2, IN3, IN4, ENB)
MotorControl drive(2, 3, 4, 5, 6, 7);
UltrasonicSensor sonarCenter(8, 9);
UltrasonicSensor sonarRight(10, 11);
UltrasonicSensor sonarLeft(12, 13);

IMUControl imu;

bool verifyTurn(float expectedChange) {
  static float lastYaw = 0;
  float currentYaw = imu.getYaw();  // You'd implement getYaw() in IMUControl
  float delta = abs(currentYaw - lastYaw);
  lastYaw = currentYaw;
  return delta >= expectedChange;
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  Serial.println("Initializing motor driver...");
  drive.init();

  Serial.println("Initializing IMU...");
  imu.init();  // Initialize the BNO085 IMU (prints a confirmation if successful)

  while (!imu.isSensorReporting()) {
    Serial.println("Waiting for sensor data...");
    delay(500);
  }
  Serial.println("Sensor is reporting data.");


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

  // Pitch correction
  float pitchRate = imu.getPitchCorrection();
  Serial.print("Pitch Correction: ");
  Serial.println(pitchRate);
  
  drive.stabilize(pitchRate);

  float accelMag = imu.getAccelerationMagnitude();
if (accelMag > 2.0) {  // You set threshold experimentally
  Serial.println("High impact detected — possible collision or terrain issue.");
}


  // Obstacle avoidance logic
  if (centerDist > 0 && centerDist < 75) {
    Serial.println("Obstacle ahead: avoiding...");
    if (flipped) {
      drive.forward(150, 1000); // Move forward if flipped
    } else {
      drive.backward(150, 1000); // Move backward if not flipped
    }
    drive.fullStop();
    drive.turnRight(150, 1000);

    // Turn verification logic
    if (!verifyTurn(60)) {
     Serial.println("Warning: Turn angle insufficient.");
    }
 
  }else if (rightDist > 0 && rightDist < 45) {
    Serial.println("Obstacle on right: turning left...");
    drive.turnLeft(150, 1000);
  } 
  else if (leftDist > 0 && leftDist < 45) {
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
