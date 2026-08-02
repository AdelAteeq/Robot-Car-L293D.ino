#include <Servo.h>

// ================= MOTOR PINS =================

// Motors 1 & 2
const int EN12 = 5;
const int IN1 = 7;
const int IN2 = 8;

// Motors 3 & 4
const int EN34 = 6;
const int IN3 = 9;
const int IN4 = 10;


// ================= ULTRASONIC =================

const int TRIG_PIN = 11;
const int ECHO_PIN = 12;


// ================= SERVO =================

const int SERVO_PIN = 3;

Servo myServo;


// ================= VARIABLES =================

const int OBSTACLE_DISTANCE = 10;


// ================= SETUP =================

void setup() {

  // Motor pins
  pinMode(EN12, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(EN34, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Ultrasonic
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Servo
  myServo.attach(SERVO_PIN);
  myServo.write(90);

  Serial.begin(9600);
}


// ================= DISTANCE =================

long getDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    return 999;
  }

  long distance = duration * 0.034 / 2;

  return distance;
}


// ================= STOP =================

void stopMotors() {

  analogWrite(EN12, 0);
  analogWrite(EN34, 0);
}


// ================= FORWARD =================

void moveForward() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(EN12, 255);
  analogWrite(EN34, 255);
}


// ================= BACKWARD =================

void moveBackward() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(EN12, 255);
  analogWrite(EN34, 255);
}


// ================= RIGHT =================

void turnRight() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(EN12, 255);
  analogWrite(EN34, 255);
}


// ================= LEFT =================

void turnLeft() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(EN12, 255);
  analogWrite(EN34, 255);
}


// ================= OBSTACLE AVOIDANCE =================

void avoidObstacle() {

  // Stop immediately
  stopMotors();
  delay(300);

  // Look right
  myServo.write(30);
  delay(500);

  long rightDistance = getDistance();

  // Look left
  myServo.write(150);
  delay(500);

  long leftDistance = getDistance();

  // Return servo to center
  myServo.write(90);
  delay(300);


  Serial.print("Right: ");
  Serial.print(rightDistance);

  Serial.print(" cm | Left: ");
  Serial.print(leftDistance);

  Serial.println(" cm");


  // Choose the direction with more space

  if (rightDistance > leftDistance) {

    turnRight();
    delay(1000);

  } else {

    turnLeft();
    delay(1000);
  }

  stopMotors();
}


// ================= MAIN PROGRAM =================

void loop() {

  // ---------- FORWARD 30 SECONDS ----------

  unsigned long startForward = millis();

  while (millis() - startForward < 30000) {

    long distance = getDistance();

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance <= OBSTACLE_DISTANCE) {

      avoidObstacle();

    } else {

      moveForward();
    }

    delay(100);
  }


  // ---------- BACKWARD 60 SECONDS ----------

  unsigned long startBackward = millis();

  while (millis() - startBackward < 60000) {

    long distance = getDistance();

    if (distance <= OBSTACLE_DISTANCE) {

      avoidObstacle();

    } else {

      moveBackward();
    }

    delay(100);
  }


  // ---------- RIGHT / LEFT 60 SECONDS ----------

  unsigned long startTurning = millis();

  while (millis() - startTurning < 60000) {

    long distance = getDistance();

    if (distance <= OBSTACLE_DISTANCE) {

      avoidObstacle();

    } else {

      turnRight();
      delay(5000);

      distance = getDistance();

      if (distance <= OBSTACLE_DISTANCE) {

        avoidObstacle();

      } else {

        turnLeft();
        delay(5000);
      }
    }
  }


  // ---------- FINISH ----------

  stopMotors();

  delay(2000);
}
