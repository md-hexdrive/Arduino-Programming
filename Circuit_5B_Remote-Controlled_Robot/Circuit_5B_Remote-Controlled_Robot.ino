
int switchPin = 2;

const int AIN1 = 7;
const int AIN2 = 8;
const int PWMA = 9;

const int BIN1 = 6;
const int BIN2 = 5;
const int PWMB = 3;

const int driveTime = 20;

const int turnTime = 8;

String botDirection;
int distance;

void setup() {
  // put your setup code here, to run once:
  pinMode(switchPin, INPUT_PULLUP);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  Serial.begin(9600);

  Serial.println("Enter a direction followed by a distance.");
  Serial.println("f = forward, b = backward, r = turn right, l = turn left");
  Serial.println("Example command: f 50");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(switchPin) == LOW) {
    if (Serial.available() > 0)
    {
      botDirection = Serial.readStringUntil(' ');
      distance = Serial.readStringUntil(' ').toInt();

      Serial.print(botDirection);
      Serial.print(" ");
      Serial.println(distance);

      if(botDirection == "f")
      {
        rightMotor(200);
        leftMotor(200);
        delay(driveTime * distance);
        rightMotor(0);
        leftMotor(0);
      }
      else if(botDirection = "b")
      {
        rightMotor(-200);
        leftMotor(-200);
        delay(driveTime * distance);
        rightMotor(0);
        leftMotor(0);
      }
      else if(botDirection = "r")
      {
        rightMotor(-200);
        leftMotor(255);
        delay(turnTime * distance);
        rightMotor(0);
        leftMotor(0);
      }
      else if(botDirection == "l")
      {
        rightMotor(255);
        leftMotor(-200);
        delay(turnTime * distance);
        rightMotor(0);
        leftMotor(0);
      }
    }
  }
  else {
    rightMotor(0);
    leftMotor(0);
    
  }
}

void rightMotor(int motorSpeed)
{
  if (motorSpeed > 0) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    
  } else if (motorSpeed < 0) {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
  } else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
  }
  analogWrite(PWMA, abs(motorSpeed));
}

void leftMotor(int motorSpeed)
{
  if (motorSpeed > 0) {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    
  } else if (motorSpeed < 0) {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
  } else {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
  }
  analogWrite(PWMB, abs(motorSpeed));
}
