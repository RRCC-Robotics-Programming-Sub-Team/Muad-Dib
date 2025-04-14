#include "MotorControl.h"
#include "UltrasonicSensor.h"
#include "IMUControl.h"
#include "OrientationControl.h"
#include "TiltDetector.h"
#include "RobotController.h"
#include "DirectionControl.h"
#include "ObjectAvoidance.h"

OrientationControl orientation;
bool flipped = false;

// Initialize objects
// MotorControl constructor arguments: (ENA, IN1, IN2, IN3, IN4, ENB)
MotorControl drive(2, 3, 4, 5, 6, 7);
UltrasonicSensor sonarCenter(8, 9);
UltrasonicSensor sonarRight(10, 11);
UltrasonicSensor sonarLeft(12, 13);

IMUControl imu;
TiltDetector tiltDetector;
RobotController robot;
DirectionControl directionControl;
ObjectAvoidance objectAvoidance(sonarCenter, drive, directionControl);

bool isInDitch = false;

bool verifyTurn(float expectedChange) {
  static float lastYaw = 0;
  float currentYaw = imu.getYaw();  // You'd implement getYaw() in IMUControl
  float delta = abs(currentYaw - lastYaw);
  lastYaw = currentYaw;
  return delta >= expectedChange;
}

enum MotionState { IDLE, MOVING_FORWARD, MOVING_BACKWARD, AVOIDING, TURNING };
MotionState motionState = IDLE;
unsigned long motionStart = 0;
unsigned long motionDuration = 1000;

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  Serial.println("Initializing motor driver...");
  drive.init();

  Serial.println("Initializing IMU...");
  imu.init();  // Initialize the BNO085 IMU (prints a confirmation if successful)

  Serial.println("Initializing Tilt Detector...");
if (!tiltDetector.begin()) {
  Serial.println("IMU not detected for tilt detection!");
}

  Serial.println("Initializing Object Avoidance...");
  objectAvoidance.init();

  Serial.println("Initializing Direction Control...");
  directionControl.init(&imu, &drive);

  //while (!imu.isSensorReporting()) {
  //  Serial.println("Waiting for sensor data...");
  //  delay(500);
  //}
  
  Serial.println("Sensor is reporting data.");

    Serial.println("Verifying ultrasonic distances...");
  for (int i = 0; i < 10; i++) {
    Serial.print("Center: ");
    Serial.print(sonarCenter.getDistance());
    Serial.print("  Left: ");
    Serial.print(sonarLeft.getDistance());
    Serial.print("  Right: ");
    Serial.println(sonarRight.getDistance());
    delay(500);
  }

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

  TiltStatus tilt = tiltDetector.getTiltStatus();

  if (tilt == TILT_DOWN && !isInDitch) {
    Serial.println("Ditch detected — moving forward to escape.");
    isInDitch = true;
    robot.moveForward();
    delay(500);
    return;
 
  }else if (tilt == FLAT && isInDitch) {
    Serial.println("Level ground reached. Checking if climbing out...");
    robot.moveForward();
    delay(500);
    if (tiltDetector.checkPitchMovingUp()) {
      Serial.println("Confirmed climb out. Exiting ditch mode.");
      isInDitch = false;
    }
    return;
 
  }else if (tilt == TILT_UP && isInDitch) {
    Serial.println("Climbing incline — continuing.");
    robot.moveForward();
    delay(500);
    return;
  }

  objectAvoidance.checkForObstacles();

  // Read distances
  int centerDist = sonarCenter.getDistance();
  int rightDist = sonarRight.getDistance();
  int leftDist = sonarLeft.getDistance();

  if (centerDist == 0) centerDist = 999;
  if (rightDist == 0) rightDist = 999;
  if (leftDist == 0) leftDist = 999;

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

  // Hill vs. Obstacle Detection
  bool isHill = false;
  int hillTolerance = 15; // Adjust this based on test results

  if ((centerDist - leftDist > hillTolerance && centerDist - rightDist > hillTolerance) || 
      (leftDist < centerDist - hillTolerance && rightDist < centerDist - hillTolerance)) {
    Serial.println("Incline detected — assuming hill. Continuing forward.");
    isHill = true;
  } else if (abs(centerDist - leftDist) < hillTolerance &&
             abs(centerDist - rightDist) < hillTolerance) {
    Serial.println("Flat wall-like surface detected — treating as obstacle.");
    isHill = false;
  }


  // Obstacle avoidance logic
  if (motionState != IDLE && millis() - motionStart >= motionDuration) {
    Serial.println("Stopping motors.");
    drive.fullStop();
    motionState = IDLE;
  }

  if (motionState == IDLE) {
    if (!isHill && centerDist > 0 && centerDist < 75) {
      Serial.println("Obstacle ahead — avoid.");
      if (flipped) drive.forward(150, 0);
      else drive.backward(150, 0);
      motionStart = millis();
      motionDuration = 1000;
      motionState = AVOIDING;

    } else if (centerDist >= 75 && leftDist < 45 && rightDist < 45) {
      Serial.println("Side sensors triggered — move forward.");
      if (flipped) drive.backward(150, 0);
      else drive.forward(150, 0);
      motionStart = millis();
      motionDuration = 1000;
      motionState = MOVING_FORWARD;

    } else if (rightDist > 0 && rightDist < 45) {
      Serial.println("Obstacle right — turn left.");
      drive.turnLeft(150, 0);
      motionStart = millis();
      motionDuration = 1000;
      motionState = TURNING;

    } else if (leftDist > 0 && leftDist < 45) {
      Serial.println("Obstacle left — turn right.");
      drive.turnRight(150, 0);
      motionStart = millis();
      motionDuration = 1000;
      motionState = TURNING;

    } else {
      Serial.println("Clear path — moving forward.");
      if (flipped) drive.backward(150, 0);
      else drive.forward(150, 0);
      motionStart = millis();
      motionDuration = 1000;
      motionState = MOVING_FORWARD;
    }
  }
}
