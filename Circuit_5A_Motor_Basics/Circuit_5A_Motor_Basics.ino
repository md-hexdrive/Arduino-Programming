int motorSpeed = 0;

int switchPin = 2;

const int AIN1 = 7;
const int AIN2 = 8;
const int PWMA = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(switchPin, INPUT_PULLUP);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  Serial.begin(9600);

  Serial.println("Enter motor speed (0-255)... ");
}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available() > 0) {
    motorSpeed = Serial.parseInt();
    //Serial.readString();
    
    Serial.print("Motor Speed: ");
    Serial.println(motorSpeed);
  }

  if(digitalRead(switchPin) == LOW) {
    spinMotor(motorSpeed);
  } else {
    spinMotor(0);
  }
}

void spinMotor(int motorSpeed) 
{
  if(motorSpeed > 0) 
  {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  } 
  else if (motorSpeed < 0) 
  {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
  }
  else
  {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
  }
  analogWrite(PWMA, abs(motorSpeed));
}
