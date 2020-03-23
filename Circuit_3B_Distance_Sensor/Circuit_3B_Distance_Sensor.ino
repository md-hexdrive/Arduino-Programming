int trigPin = 11;
int echoPin = 10;

int redPin = 9;
int greenPin = 8;
int bluePin = 7;

float distance = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  distance = getDistance();

  Serial.print(distance);
  Serial.println(" in");
  
  if (distance <= 10) {
    //setRed();
  } else if (distance > 10 && distance < 20) {
    //setYellow();
  } else if (distance >= 20 && distance < 30) {
    //setOrange();
  }
  else {
    //setGreen();
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
