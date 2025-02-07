//Important Functions
 /*drive.forward(speed,time_delay);  drive.full_stop(time_delay);  drive.turn_right(speed,time_delay);  drive.full_stop(time_delay);
  drive.turn_left(speed,time_delay);   drive.full_stop(time_delay);   drive.backward(speed,time_delay);

  sonar.ping_cm();  // Returns distance in cm of obstacle in front
  */
  
//Libraries
#include "Arduino.h"
#include "AutoDriving.h"
#include <NewPing.h>

#define TRIGGER_PIN_C  8  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_C     9  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN_R  10  
#define ECHO_PIN_R     11  
#define TRIGGER_PIN_L  12  
#define ECHO_PIN_L     13  
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

const int ENA = 2;
const int IN1 = 3;
const int IN2 = 4;
const int IN3 = 5;
const int IN4 = 6;
const int ENB = 7;


L298N drive(ENA, IN1, IN2, IN3, IN4, ENB); 
NewPing sonarCenter(TRIGGER_PIN_C, ECHO_PIN_C, MAX_DISTANCE);
NewPing sonarRight(TRIGGER_PIN_R, ECHO_PIN_R, MAX_DISTANCE);
NewPing sonarLeft(TRIGGER_PIN_L, ECHO_PIN_L, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


int centerRange = 150; // Default center range
int sideRange = 85;    // Default side range
int delay_time = 1000;
int delay_mult = 3;
int speed = 150;
bool way_clear = 0;
bool left_clear = 1;       // Left sensor clear status
bool right_clear = 1;      // Right sensor clear status

void setup()
{
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop()
{
  check_center_obstacle();
  check_side_obstacles();
  
  if (way_clear == 0)
  {
	drive.backward(speed, delay_time * delay_mult);
  drive.full_stop(5);
  drive.turn_right(speed, delay_time * delay_mult);
  }
  else if (left_clear == 0) {
    // Left sensor detects an obstacle; turn right
    drive.turn_right(speed, delay_time * delay_mult);
  }
  else if (right_clear == 0) {
    // Right sensor detects an obstacle; turn left
    drive.turn_left(speed, delay_time * delay_mult);
  }
  else
  {
  drive.forward(speed, delay_time);
  }
}

//------------------------------------------------------------------//

void check_center_obstacle() {
  // Check center ultrasonic sensor
  int dist = sonarCenter.ping_cm();
  delay(50);

  Serial.print("Center Distance: ");
  Serial.println(dist);

  if (dist > 0 && dist < centerRange) { // Detect obstacles within 150 cm
    way_clear = 0;
  } else {
    way_clear = 1;
  }
}

void check_side_obstacles() {
  int distRight = sonarRight.ping_cm(); // Check right ultrasonic sensor
  int distLeft = sonarLeft.ping_cm();  // Check left ultrasonic sensor
  delay(50);

  Serial.print("Right Distance: ");
  Serial.println(distRight);
  Serial.print("Left Distance: ");
  Serial.println(distLeft);

  if (distRight > 0 && distRight < sideRange) { // Detect obstacles within 50 cm
    right_clear = 0;
  } else {
    right_clear = 1;
  }

  if (distLeft > 0 && distLeft < sideRange) { // Detect obstacles within 50 cm
    left_clear = 0;
  } else {
    left_clear = 1;
  }
}

void turn(int dir, int angle) {
  switch (dir) {
    case 1:
      drive.turn_left(100, angle);
      break;
    case 2:
      drive.turn_right(100, angle);
      break;
    default:
      break;
  }
}





//servoNose.write(val);                  // sets the servo position according to the scaled value

//#include <Servo.h>

//Servo servoNose;

//Setup
//servoNose.attach(9);  // attaches the servo on pin 9 to the servo object

//Loop
//find_way();

/*
 void find_way()
 {
	 int start_angle = 90; // servo origin position
	 servoNose.write(start_angle);
	 int angle;
	 int dir=1;  //right
	 int obstacle;
	 
	 for (int i=0;i<10;i++)
	 {
		  angle = start_angle + (i*9);		//angle of rotation
		  servoNose.write(angle);
		  delay(2);  // Wait for servo to rotate
		  check_obstacle();
		  if (way_clear == 1)
		  {
			  servoNose.write(start_angle);
			  i=11; // end loop
			  
		  }
		  else {
			  i=0;
			  start_angle = 0;
			  dir = 2; // left
		  }
	 }
	 turn(dir,45); // 
 }
 */