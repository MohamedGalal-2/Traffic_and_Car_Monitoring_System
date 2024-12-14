// Includes section
#include <AFMotor.h>
#include <SoftwareSerial.h>

// Define pins for the ultrasonic sensor (using analog pins as digital pins)
#define TRIG_PIN A0
#define ECHO_PIN A1

// Define pins for the IR Sensors
#define IR_SENSOR_RIGHT A4
#define IR_SENSOR_LEFT  A3

// Set threshold
const int STOP_DISTANCE = 7;    // Distance to stop the car in cm

// Set car speed profiles
int SPEED = 255;
const int HIGH_SPEED = 255;
const int MEDIUM_SPEED = 170;
const int LOW_SPEED = 85;

SoftwareSerial HC05(9, 10); // RX, TX

//initial motors pin
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

char command;

void setup()
{
  // Initialize pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);

  // Start serial communication for debugging
  Serial.begin(9600);

  //Set the baud rate to your Bluetooth module.
  HC05.begin(9600);
}

void loop() 
{
  // Measure distance of the obstacle
  int obstacleDistance = getDistance();

  // Check if there is an obstacle in the road
  if (obstacleDistance <= STOP_DISTANCE) 
  {
    stop();
    Serial.println("Stop");
    Serial.println(obstacleDistance); // Debugging
  }
  else // Debugging
  {
    Serial.println(obstacleDistance); 
  }

  // Check if there is a Bluetooth connection established
  if (HC05.available() > 0) 
  {
    command = HC05.read();

    stop(); //initialize with motors stoped
    Serial.println(command); // Debugging

    switch (command) 
    {
      case 'H'
        SPEED = HIGH_SPEED;
        break;
      case 'M'
        SPEED = MEDIUM_SPEED;
        break;
      case 'N'
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

void forward()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD);  //rotate the motor clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(FORWARD);  //rotate the motor clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(FORWARD);  //rotate the motor clockwise
}

void back(int CAR_SPEED)
{
  motor1.setSpeed(CAR_SPEED); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(CAR_SPEED); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(CAR_SPEED); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(CAR_SPEED); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}

void left(int CAR_SPEED)
{
  motor1.setSpeed(CAR_SPEED); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor clockwise
  motor2.setSpeed(CAR_SPEED); //Define lower velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(CAR_SPEED); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(CAR_SPEED); // Define lower velocity
  motor4.run(FORWARD);  //rotate the motor clockwise
}

void right()
{
  motor1.setSpeed(CAR_SPEED); //Define lower velocity
  motor1.run(FORWARD);  //rotate the motor clockwise
  motor2.setSpeed(CAR_SPEED); //Define maximum velocity
  motor2.run(BACKWARD);  //rotate the motor clockwise
  motor3.setSpeed(CAR_SPEED); //Define lower velocity
  motor3.run(FORWARD); //rotate the motor clockwise
  motor4.setSpeed(CAR_SPEED); //Define maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
}

void stop()
{
  motor1.setSpeed(0);  //Define minimum velocity
  motor1.run(RELEASE); //stop the motor when release the button
  motor2.setSpeed(0);  //Define minimum velocity
  motor2.run(RELEASE); //rotate the motor clockwise
  motor3.setSpeed(0);  //Define minimum velocity
  motor3.run(RELEASE); //stop the motor when release the button
  motor4.setSpeed(0);  //Define minimum velocity
  motor4.run(RELEASE); //stop the motor when release the button
}

// Function to measure the distance of the obstacles
int getDistance() 
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2; // Convert to cm
}

void self_Drive(int CAR_SPEED);
{
  // Search for black line on the road
  int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
  int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);

   //If none of the sensors detects black line, then go straight
  if (rightIRSensorValue == LOW && leftIRSensorValue == LOW)
  {
    Serial.println("Forward");
    forward(CAR_SPEED);
  }
  //If right sensor detects black line, then turn right
  else if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW )
  {
    right(CAR_SPEED);
  }
  //If left sensor detects black line, then turn left  
  else if (rightIRSensorValue == LOW && leftIRSensorValue == HIGH )
  {
    left(CAR_SPEED);
  } 
  //If both the sensors detect black line, then stop 
  else 
  {
    stop();
  }

}