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


int PWMA = 9;
int AIN2 = 8;
int AIN1 = 7;

int BIN1 = 6;
int BIN2 = 5;
int PWMB = 3;

int switchPin = 2;

const int driveTime = 20;
const int turnTime = 8;

int leftThreshold = 50;
int rightThreshold = 25;

int rightLevel = 0;
int leftLevel = 0;

float distance;
int led = 13;

int button = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  
  pinMode(PWMA, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  pinMode(switchPin, INPUT_PULLUP);

  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);

  calibrate();

  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:

  printLightLevels();
  if(digitalRead(switchPin) == LOW) {
       
        
    if(rightLevel == 0 || leftLevel == 0 || 
    rightLevel == 1023 || leftLevel == 1023) {
      stop();
      digitalWrite(led, HIGH);
      delay(500);
      digitalWrite(led, LOW);
      delay(500);
    }
    
    else if(rightLevel <= rightThreshold && leftLevel >= leftThreshold) {
      stop();
      turnLeft(5);
    }
    else if(rightLevel >= rightThreshold && leftLevel <= leftThreshold) {
      stop();
      turnRight(5);
    }
//    else if(rightLevel <= rightThreshold && leftLevel <= leftThreshold) {
//      turnLeft(45);
//    }
    else{
      backwards(3);
    }
  }
  else {
    stop();
  }
  //delay(20);
}


/********************************************************************************/
void printLightLevels() {
  rightLevel = analogRead(A0);
  leftLevel = analogRead(A1);
  
  Serial.print("Left Photocell: ");
  Serial.print(leftLevel);
  Serial.print(" and threshold ");
  Serial.print(leftThreshold);
  Serial.print(",   Right Photocell: ");
  Serial.print(rightLevel);
  Serial.print(" and threshold ");
  Serial.println(rightThreshold);
}

void calibrate() {
  int lLow;
  int rLow;
  int lHigh;
  int rHigh;

  Serial.println("Begin Calibration...\n");
  Serial.println("Set the robot in the white area");
  while(digitalRead(button)==HIGH) {}
  if(digitalRead(button)==LOW) {
    lHigh = analogRead(A1);
    rHigh = analogRead(A0);

    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
  }
  delay(1000);
  Serial.println("Set the robot in the black area");
  while(digitalRead(button)==HIGH) {}
  if(digitalRead(button)==LOW) {
    lLow = analogRead(A1);
    rLow = analogRead(A0);
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
  }
  leftThreshold = lLow + (lHigh - lLow) / 2;
  rightThreshold = rLow + (rHigh - rLow) / 2;

  printLightLevels();

}
void stop() {
  rightMotor(0);                                  //turn the right motor off
  leftMotor(0);                                   //turn the left motor off
}
void drive(){
  rightMotor(200);                                //drive the right wheel forward
  leftMotor(200);                                 //drive the left wheel forward

}

void driveBackwards(){
  rightMotor(-175);                                //drive the right wheel forward
  leftMotor(-175);                                 //drive the left wheel forward

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
  leftMotor(200);                                 //drive the left wheel forward
  delay(turnTime * degrees);             //drive the motors long enough turn the entered distance
  stop();
}
void turnLeft(int degrees) {
  rightMotor(200);                                //drive the right wheel forward
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
