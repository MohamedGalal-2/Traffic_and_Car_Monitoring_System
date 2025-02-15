# Smart Car with ESP32 and STM32

## Table of Contents
- [Project Overview](#Project-Overview)
- [Features](#Features)
- [Components](#Components)
- [System Diagram](#System-Diagram)
- [Functional Flow](#Functional-Flow)
- [Installation & Setup](#Installation-&-Setup)
- [Usage](#Usage)
- [Troubleshooting](#Troubleshooting)
- [Future Enhancements](#Future-Enhancements)
- [Credits](#Credits)
- [Licence](#License)

## Project Overview
This project involves creating a smart car system controlled by a mobile application and integrating various microcontrollers and sensors to achieve functionality. The system comprises the following components:

1. **ESP32**: Connects to Wi-Fi, receives commands from the mobile application, and interacts with a speaker upon receiving signals from the STM32.
2. **STM32 Black Pill**: Serves as a bridge between the ESP32 and the car, managing traffic light signals and controlling a servo motor. It communicates with the ESP32 using UART and with the car via Bluetooth (HC-05 module).
3. **Car**: Controlled based on commands sent from the mobile app through the STM32. It includes obstacle avoidance via an ultrasonic sensor and self-driving capabilities using IR sensors for line following.

---

## Features

### ESP32
- Connects to Wi-Fi and acts as the central communication hub.
- Receives commands from a mobile application to control the car and audio playback.
- Plays audio through a speaker when triggered by signals from the STM32.

### STM32 Black Pill
- Communicates with the ESP32 via UART to coordinate tasks.
- Sends traffic light commands (Red/Yellow/Green) to the car and the ESP32.
- Controls a servo motor for additional actions.
- Interfaces with the car using the Bluetooth module (HC-05).

### Car
- Controlled by commands relayed through the STM32.
- Equipped with:
  - **Ultrasonic Sensor**: Detects and avoids obstacles.
  - **IR Sensors**: Enables line-following functionality for autonomous driving.

---

## Components

### Microcontrollers
- ESP32
- STM32 Black Pill

### Sensors
- Ultrasonic Sensor
- IR Sensors (2)

### Modules
- HC-05 Bluetooth Module

### Others
- Servo Motor
- Speaker

### Additional Software
- PCM arrays generated via NumPy for audio playback.

---

## System Diagram
1. **Mobile App** ➔ Wi-Fi ➔ **ESP32** ➔ UART ➔ **STM32**
2. **STM32** ➔ Bluetooth (HC-05) ➔ **Car**
3. **Car Sensors**:
   - Ultrasonic: Obstacle avoidance.
   - IR: Line-following.

---

## Functional Flow

1. **Mobile App Commands**:
   - User sends commands via a mobile application.
   - Commands are received by the ESP32 over Wi-Fi.

2. **ESP32 Processing**:
   - Forwards relevant commands to the STM32 via UART.
   - Triggers audio playback through the speaker when prompted by STM32 signals.

3. **STM32 Control**:
   - Interprets commands from the ESP32.
   - Sends traffic light signals to the car (Red/Yellow/Green).
   - Activates servo motor for additional car actions.

4. **Car Behavior**:
   - Executes movement commands relayed by the STM32.
   - Uses ultrasonic sensor for obstacle avoidance.
   - Uses IR sensors for line-following.

---

## Installation & Setup

1. **ESP32 Configuration**:
   - Flash the ESP32 with the Wi-Fi and UART communication firmware.
   - Ensure the ESP32 is connected to your Wi-Fi network.

2. **STM32 Configuration**:
   - Flash the STM32 with the firmware for UART communication, Bluetooth control, and servo motor handling.
   - Pair the HC-05 Bluetooth module with the car.

3. **Car Setup**:
   - Connect the ultrasonic sensor and IR sensors to the car’s control board.
   - Calibrate the sensors for accurate obstacle detection and line-following.

4. **Mobile App**:
   - Install the mobile application on your device.
   - Connect the app to the ESP32 via Wi-Fi.

---

## Usage
1. Launch the mobile application and connect to the ESP32.
2. Send control commands for:
   - Car movement (forward, backward, left, right).
   - Traffic light states (Red/Yellow/Green).
   - Audio playback.
3. The car autonomously avoids obstacles and follows lines when enabled.

---

## Troubleshooting
- **Wi-Fi Issues**: Ensure the ESP32 is connected to the correct network.
- **Bluetooth Pairing**: Verify the HC-05 is properly paired with the car.
- **Sensor Malfunctions**: Check wiring and recalibrate the ultrasonic and IR sensors.

---

## Future Enhancements
- Add camera-based object detection.
- Enable real-time video streaming from the car to the mobile app.
- Expand functionality with additional sensors for environmental mapping.

---

## Credits
- Project by [Your Name/Team].

---

### License
This repository is licensed under the MIT License. Please see the LICENSE file for more information

