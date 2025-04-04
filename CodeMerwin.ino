#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BNO08x.h>

// Ultrasonic Sensor
#define trigPin 13
#define echoPin 12

// Infrared Sensors
#define irLeft A0
#define irRight A1

// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

// IMU Sensor
Adafruit_BNO08x bno085;
float initialHeading = 0;
bool imuActive = false;

void setup() {
    Serial.begin(9600);
    
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(irLeft, INPUT);
    pinMode(irRight, INPUT);
    
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    
    Wire.begin();
    if (!bno085.begin_I2C(0x4A)) {
        Serial.println("Failed to initialize IMU!");
        while (1);
    }
    Serial.println("IMU initialized.");

    initialHeading = getHeading();
    Serial.print("Initial Heading: ");
    Serial.println(initialHeading);
    stopMotors();
    delay(5000);
    Serial.println("Starting Movement");
}

float getHeading() {
    sh2_SensorValue_t event;
    if (!bno085.getSensorEvent(&event)) {
        Serial.println("Failed to get IMU event!");
        return initialHeading; // Return the last known heading if the event fails
    }

    if (event.sensorId == SH2_GAME_ROTATION_VECTOR) {
        float qw = event.un.gameRotationVector.real;
        float qx = event.un.gameRotationVector.i;
        float qy = event.un.gameRotationVector.j;
        float qz = event.un.gameRotationVector.k;

        // Convert quaternion to yaw (heading) in degrees
        float yaw = atan2(2.0 * (qw * qz + qx * qy), 1.0 - 2.0 * (qy * qy + qz * qz));
        yaw = yaw * (180.0 / PI); // Convert from radians to degrees

        if (yaw < 0) {
            yaw += 360; // Keep heading in the range [0, 360]
        }

        return yaw;
    }

    Serial.println("IMU event not of expected type.");
    return initialHeading; // Return last known heading if it's not the right event type
}


long getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    return (duration / 2) / 29.1;
}

float getInfraredDistance(int pin) {
    float voltage = analogRead(pin) * (5.0 / 1023.0);
    return 27.86 * pow(voltage, -1.15);
}

void moveForward() {
    analogWrite(enA, 200);
    analogWrite(enB, 200);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}

void moveBackward() {
    analogWrite(enA, 200);
    analogWrite(enB, 200);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void turnLeft() {
    analogWrite(enA, 200);
    analogWrite(enB, 0);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}

void turnRight() {
    analogWrite(enA, 0);
    analogWrite(enB, 200);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}

void stopMotors() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}

void correctDirection(float deviation) {
    if (deviation > 0) {
        turnLeft();
    } else {
        turnRight();
    }
    delay(abs(deviation) * 10);
    moveForward();
}

void loop() {
    long distance = getDistance();
    float leftDistance = getInfraredDistance(irLeft);
    float rightDistance = getInfraredDistance(irRight);
    
    bool frontObstacle = (distance < 30);
    bool leftObstacle = (leftDistance < 30);
    bool rightObstacle = (rightDistance < 30);
    
    if (frontObstacle || leftObstacle || rightObstacle) {
        imuActive = true;
        stopMotors();
        delay(500);

        if (rightObstacle) {
            turnLeft();
        } else if (leftObstacle) {
            turnRight();
        } else {
            moveBackward();
        }
        delay(500);
    } else if (imuActive) {
        float currentHeading = getHeading();
        float deviation = currentHeading - initialHeading;
        correctDirection(deviation);
        imuActive = false;
    } else {
        moveForward();
    }
}
