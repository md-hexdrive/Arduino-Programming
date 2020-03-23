#include <Servo.h>

const int trigPin = 5;
const int echoPin = 6;

int redPin = 9;
int greenPin = 10;
int bluePin = 11;

int speakerPin = 4;
int servoPin = 3;
Servo myServo;

float distance = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(speakerPin, OUTPUT);
  myServo.attach(servoPin);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  distance = getDistance();

  Serial.print(distance);
  Serial.println(" in");
  
  if (distance <= 10) {
    setRed();
    tone(speakerPin, 262);
    myServo.write(45);
    delay(100);
    noTone(speakerPin);
    myServo.write(135);
    delay(100);
    
  } else if (distance > 10 && distance < 20) {
    setYellow();
  } else if (distance >= 20 && distance < 30) {
    setOrange();
  }
  else {
    setGreen();
  }

  delay(50);

}

void setRed() {
  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  
}

void setOrange(){
  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 0);
}
void setYellow() {
  analogWrite(redPin, 255);
  analogWrite(greenPin, 50);
  analogWrite(bluePin, 0);
}

void setGreen() {
  analogWrite(redPin, 0);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 0);
}

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
