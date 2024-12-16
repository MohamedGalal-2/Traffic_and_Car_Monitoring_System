// Includes section
#include <AFMotor.h>
#include <SoftwareSerial.h>

// Define pins for the ultrasonic sensor (using analog pins as digital pins)
#define TRIG_PIN A0
#define ECHO_PIN A1

// Define pins for the IR Sensors
#define IR_SENSOR_RIGHT A4
#define IR_SENSOR_LEFT  A3

// Set car speed profiles
const int HIGH_SPEED = 255;
const int MEDIUM_SPEED = 170;
const int LOW_SPEED = 100;
int SPEED = MEDIUM_SPEED;

// Define stopping distances
const int STOP_DISTANCE_HIGH_SPEED = 30; // Stopping distance for high speed
const int STOP_DISTANCE_MEDIUM_SPEED = 20;
const int STOP_DISTANCE_LOW_SPEED = 15;

SoftwareSerial HC05(9, 10); // RX, TX

// Initialize motor pins
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

char command;

void setup() {
  // Initialize pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);

  // Start serial communication for debugging
  Serial.begin(9600);

  // Set the baud rate for Bluetooth module
  HC05.begin(9600);

  //This sets frequecny as 7812.5 hz.
  TCCR0B = (TCCR0B & (B11111000)) | B00000010;
}

void loop() {
  static unsigned long lastCheckTime = 0;
  unsigned long currentTime = millis();

  // Measure distance at regular intervals
  if (currentTime - lastCheckTime >= 50) { // Check every 50ms
    lastCheckTime = currentTime;
    int obstacleDistance = getDistance();
    int stopDistance = getStopDistance();

    if ((obstacleDistance <= stopDistance) && (obstacleDistance != 0)) {
      stop();
      Serial.print("Obstacle detected at: ");
      Serial.println(obstacleDistance);
    }
  }

  // Check for Bluetooth commands
  if (HC05.available() > 0) {
    command = HC05.read();
    stop(); // Initialize with motors stopped

    Serial.print("Command: ");
    Serial.println(command);
    Serial.print("Speed: ");
    Serial.println(SPEED);

    switch (command) 
    {
      case 'H':
        SPEED = HIGH_SPEED;
        break;
      case 'M':
        SPEED = MEDIUM_SPEED;
        break;
      case 'N':
        SPEED = LOW_SPEED;
        break;
      case 'F':
        forward(SPEED);
        break;
      case 'B':
        back(SPEED);
        break;
      case 'L':
        left(SPEED);
        break;
      case 'R':
        right(SPEED);
        break;
      case 'S':
        self_Drive(SPEED);
        break;
     }
  }
}

void forward(int CAR_SPEED) {
  motor1.setSpeed(CAR_SPEED);
  motor1.run(FORWARD);
  motor2.setSpeed(CAR_SPEED);
  motor2.run(FORWARD);
  motor3.setSpeed(CAR_SPEED);
  motor3.run(FORWARD);
  motor4.setSpeed(CAR_SPEED);
  motor4.run(FORWARD);
}

void back(int CAR_SPEED) {
  motor1.setSpeed(CAR_SPEED);
  motor1.run(BACKWARD);
  motor2.setSpeed(CAR_SPEED);
  motor2.run(BACKWARD);
  motor3.setSpeed(CAR_SPEED);
  motor3.run(BACKWARD);
  motor4.setSpeed(CAR_SPEED);
  motor4.run(BACKWARD);
}

void left(int CAR_SPEED) {
  motor1.setSpeed(CAR_SPEED);
  motor1.run(BACKWARD);
  motor2.setSpeed(CAR_SPEED);
  motor2.run(FORWARD);
  motor3.setSpeed(CAR_SPEED);
  motor3.run(BACKWARD);
  motor4.setSpeed(CAR_SPEED);
  motor4.run(FORWARD);
}

void right(int CAR_SPEED) {
  motor1.setSpeed(CAR_SPEED);
  motor1.run(FORWARD);
  motor2.setSpeed(CAR_SPEED);
  motor2.run(BACKWARD);
  motor3.setSpeed(CAR_SPEED);
  motor3.run(FORWARD);
  motor4.setSpeed(CAR_SPEED);
  motor4.run(BACKWARD);
}

void stop() {
  motor1.setSpeed(255);  // Active braking
  motor1.run(RELEASE);
  motor2.setSpeed(255);
  motor2.run(RELEASE);
  motor3.setSpeed(255);
  motor3.run(RELEASE);
  motor4.setSpeed(255);
  motor4.run(RELEASE);
  delay(100); // Ensure full stop
}

int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 20000); // Timeout after 20ms
  if (duration == 0) {
    return 0; // No pulse received
  }
  return duration * 0.034 / 2; // Convert to cm
}

int getStopDistance() {
  if (SPEED == HIGH_SPEED) return STOP_DISTANCE_HIGH_SPEED;
  if (SPEED == MEDIUM_SPEED) return STOP_DISTANCE_MEDIUM_SPEED;
  return STOP_DISTANCE_LOW_SPEED;
}

void self_Drive(int CAR_SPEED) {
  int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
  int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);

  if (rightIRSensorValue == LOW && leftIRSensorValue == LOW) {
    forward(CAR_SPEED);
  } else if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW) {
    right(CAR_SPEED);
  } else if (rightIRSensorValue == LOW && leftIRSensorValue == HIGH) {
    left(CAR_SPEED);
  } else {
    stop();
  }
}