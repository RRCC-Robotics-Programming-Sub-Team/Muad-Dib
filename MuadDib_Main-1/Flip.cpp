#include <FLIP_H>

bool isFlipped = accelZ < -7.0;

// Get distances
int leftDistance = readUltrasonic(leftTrigPin, leftEchoPin);
int rightDistance = readUltrasonic(rightTrigPin, rightEchoPin);
int frontDistance = readUltrasonic(frontTrigPin, frontEchoPin);

// Swap left and right distances if flipped
if (isFlipped) {
  int temp = leftDistance;
  leftDistance = rightDistance;
  rightDistance = temp;
}
