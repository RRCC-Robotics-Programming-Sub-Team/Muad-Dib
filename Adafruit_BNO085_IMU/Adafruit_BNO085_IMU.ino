#include <Wire.h>                  // I2C library for Arduino
#include <Adafruit_BNO08x.h>       // Adafruit's library for BNO085

// Create the IMU object
Adafruit_BNO08x bno085 = Adafruit_BNO08x();

// Variables to store IMU data
sh2_SensorValue_t sensorValue;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);       // Wait for Serial to initialize

  // Initialize I2C communication
  Wire.begin();                    // Starts I2C on Mega (SDA - Pin 20, SCL - Pin 21)
  Serial.println("Adafruit BNO085 IMU Test");

  // Initialize the IMU
  if (!bno085.begin_I2C()) {       // Use I2C communication
    Serial.println("BNO085 not detected. Check wiring!");
    while (1);                     // Halt if IMU is not detected
  }
  Serial.println("BNO085 Connected!");

  // Configure the sensor to output various data
  bno085.enableReport(SH2_ACCELEROMETER);  // Enable Accelerometer Data
  bno085.enableReport(SH2_RAW_GYROSCOPE);      // Enable Gyroscope Data
  bno085.enableReport(SH2_ROTATION_VECTOR);  // Enable Quaternion Data
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    if (command == "start") {
      Serial.println("IMU Streaming Data...");
      while (1) {  // Infinite loop once command is received
  // Check if new sensor data is available
  if (bno085.getSensorEvent(&sensorValue)) {
    // Print quaternion rotation vector data
    Serial.print("Quaternion: ");
    Serial.print(sensorValue.un.rotationVector.real, 4);
    Serial.print(", ");
    Serial.print(sensorValue.un.rotationVector.i, 4);
    Serial.print(", ");
    Serial.print(sensorValue.un.rotationVector.j, 4);
    Serial.print(", ");
    Serial.print(sensorValue.un.rotationVector.k, 4);
    Serial.print("  Accuracy: ");
    Serial.println(sensorValue.un.rotationVector.accuracy);

    Serial.print("Accel X: "); Serial.print(sensorValue.un.accelerometer.x, 4);
    Serial.print(", Y: "); Serial.print(sensorValue.un.accelerometer.y, 4);
    Serial.print(", Z: "); Serial.println(sensorValue.un.accelerometer.z, 4);

    Serial.print("Gyro X: "); Serial.print(sensorValue.un.gyroscope.x, 4);
    Serial.print(", Y: "); Serial.print(sensorValue.un.gyroscope.y, 4);
    Serial.print(", Z: "); Serial.println(sensorValue.un.gyroscope.z, 4);
  }

  delay(100); // Short delay to limit serial output rate
      }
    }
  }
}