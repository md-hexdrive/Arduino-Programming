/*
 * The basic programming for the Autonomous robot from the SIK 
 * kit.
 * 
 * This robot will travel straight ahead until the ultrasound
 * distance sensor detects an obstacle less than 30 inches away.
 * 
 * If it detects the obstacle, It will turn to the right and keep
 * on moving foward.
 * 
 * It it detects an obstacle closer than 10 inches away, it will 
 * stop, backup, turn to the right, and then continue driving.
 */

int trigPin = 11;
int echoPin = 10;

int PWMA = 9;
int AIN2 = 8;
int AIN1 = 7;

int BIN1 = 6;
int BIN2 = 5;
int PWMB = 3;

int switchPin = 2;

const int driveTime = 20;
const int turnTime = 8;

const float safeDistance = 10;
const float turnBeforeDistance = 30;

float distance;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  pinMode(switchPin, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(switchPin) == LOW) {
    distance = getDistance();
    Serial.print(distance);
    Serial.println(" in");

    if(distance <= safeDistance) {
        stop();
        delay(250);
        backwards(20);
        delay(250);
        turnRight(45);
        delay(250);
    }
    else if (distance <= turnBeforeDistance && distance >= safeDistance) {
      turnRight(10);
    }
    else{
      drive();
    }
  }
  else {
    stop();
  }
}


/********************************************************************************/
float getDistance() {
  float echoTime;
  float calculatedDistance;

  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);

  calculatedDistance = echoTime / 148.0;

  return calculatedDistance;
}

void stop() {
  rightMotor(0);                                  //turn the right motor off
  leftMotor(0);                                   //turn the left motor off
}
void drive(){
  rightMotor(200);                                //drive the right wheel forward
  leftMotor(200);                                 //drive the left wheel forward

}
void forwards(int distance) {
  rightMotor(200);                                //drive the right wheel forward
  leftMotor(200);                                 //drive the left wheel forward
  delay(driveTime * distance);            //drive the motors long enough travel the entered distance
  stop();
}
void backwards(int distance) {
  rightMotor(-200);                               //drive the right wheel forward
  leftMotor(-200);                                //drive the left wheel forward
  delay(driveTime * distance);            //drive the motors long enough travel the entered distance
  stop();
}
void turnRight(int degrees) {
  rightMotor(-200);                               //drive the right wheel forward
  leftMotor(255);                                 //drive the left wheel forward
  delay(turnTime * degrees);             //drive the motors long enough turn the entered distance
  stop();
}
void turnLeft(int degrees) {
  rightMotor(255);                                //drive the right wheel forward
  leftMotor(-200);                                //drive the left wheel forward
  delay(turnTime * degrees);             //drive the motors long enough turn the entered distance
  stop();
}

void rightMotor(int motorSpeed)                       //function for driving the right motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(AIN1, HIGH);                         //set pin 1 to high
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMA, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

/********************************************************************************/
void leftMotor(int motorSpeed)                        //function for driving the left motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(BIN1, HIGH);                         //set pin 1 to high
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMB, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}
