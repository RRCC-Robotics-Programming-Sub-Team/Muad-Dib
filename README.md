# RRCC Space Grant: Robotics Team

This is the official codebase for the Red Rocks Community College Robotics Team, part of the NASA Colorado Space Grant Consortium Challenge.

## 🚗 Robot Overview
A Mars Rover-style autonomous vehicle featuring:
- 2WD / 4-wheel base
- IMU-guided orientation control
- Ultrasonic + LIDAR obstacle detection
- PID-controlled DC motors via L298N driver
- Modular sensor system for terrain navigation

## 💻 Hardware Stack
- Arduino Mega 2560
- Raspberry Pi 4 (Ubuntu 22.04 LTS)
- 4x Ultrasonic Sensors
- 1x LIDAR
- 1x IMU
- 2x DC Motors (GM3506 w/ Encoders)
- 1x SD Card (64GB)
- NRF24L01 (or similar) Radio Module

## 🧠 Software Structure
Each sensor/actuator is modularized in a separate `.cpp` and `.h` file.
Main logic is in `MuadDib_Main-1.ino`.

## 📂 File Layout
- `MotorControl.cpp/.h` – Controls speed/direction via L298N
- `UltrasonicSensor.cpp/.h` – Abstracts distance sensors
- `IMUControl.cpp/.h` – Handles orientation
- `OrientationControl.cpp/.h` – Stability logic
- `Encoder.cpp/.h` – Tracks wheel rotation
- `MuadDib_Main-1.ino` – Main loop with PID & sensor integration

## 📡 Features
- Obstacle detection/avoidance
- Real-time data logging (SD)
- Orientation correction (IMU + PID)
- Remote telemetry (via Radio)
- Modular & expandable architecture

## 🔧 How to Run
1. Flash `MuadDib_Main-1.ino` to Arduino Mega via Arduino IDE
2. Connect sensor modules to appropriate pins (see `HardwareConfig.md`)
3. Monitor output via Serial Monitor or Radio Module

## 🧪 Status
In active development. Please use Git branches for testing features.
