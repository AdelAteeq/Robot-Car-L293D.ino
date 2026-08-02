# Arduino Robot Car Using L293D

## Project Description

This project is an Arduino-based robotic car simulation developed using Tinkercad.

The system controls four DC motors through an L293D motor driver. An ultrasonic sensor is used to detect obstacles, while a servo motor scans the right and left directions to help the robot avoid obstacles.

## Components

* Arduino Uno R3
* L293D Motor Driver
* 4 × DC Motors
* HC-SR04 Ultrasonic Distance Sensor
* Servo Motor
* Breadboard
* Battery / Motor Power Supply
* Jumper Wires

## Main Functions

### Motor Movement

The robot performs the required movement sequence:

1. Moves forward for 30 seconds.
2. Moves backward for 60 seconds.
3. Alternates between right and left turns for 60 seconds.

### Obstacle Detection

The ultrasonic sensor continuously measures the distance in front of the robot.

When an obstacle is detected at a distance of **10 cm or less**:

1. The motors stop immediately.
2. The servo moves to the right and measures the distance.
3. The servo moves to the left and measures the distance.
4. The servo returns to the center.
5. The robot selects the direction with more available space.
6. The robot turns and continues moving.

## Pin Connections

### L293D

| Arduino | L293D |
| ------- | ----- |
| D5      | EN1,2 |
| D7      | IN1   |
| D8      | IN2   |
| D6      | EN3,4 |
| D9      | IN3   |
| D10     | IN4   |

### Ultrasonic Sensor

| Sensor | Arduino |
| ------ | ------- |
| VCC    | 5V      |
| GND    | GND     |
| TRIG   | D11     |
| ECHO   | D12     |

### Servo Motor

| Servo  | Arduino |
| ------ | ------- |
| Power  | 5V      |
| GND    | GND     |
| Signal | D3      |

## Simulation

The circuit was designed and tested using Tinkercad Circuits.

**Tinkercad Link:**
Add your Tinkercad project link here.

## Author

**Adel Bin Ateeq**

Computer Engineering Student
