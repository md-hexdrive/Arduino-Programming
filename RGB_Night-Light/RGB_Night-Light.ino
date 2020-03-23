int photoresistor;
int potentiometer;

int threshold = 700;

int RedPin = 9;
int GreenPin = 10;
int BluePin = 11;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);

  

}

void loop() {
  // put your main code here, to run repeatedly:
  photoresistor = analogRead(A0);
  potentiometer = analogRead(A1);

  Serial.print("Photoresistor value:");
  Serial.print(photoresistor);
  Serial.print(" Potentiometer value:");
  Serial.println(potentiometer);

  if (photoresistor < threshold) {
    if (0 <= potentiometer && potentiometer <= 150) {
      red();
    } else if (150 < potentiometer && potentiometer <= 300){
      orange();
    } else if (300 < potentiometer && potentiometer <= 450){
      yellow();
    } else if (450 < potentiometer && potentiometer <= 600){
      green();
    } else if (600 < potentiometer && potentiometer <= 750){
      cyan();
    } else if (750 < potentiometer && potentiometer <= 900){
      blue();
    } else if (900 < potentiometer){
      magenta();
    } 
  } else {
    turnOff();
  }

  delay(100);
}

void setColour(int red, int green, int blue) {
  analogWrite(RedPin, red);
  analogWrite(GreenPin, green);
  analogWrite(BluePin, blue);
}
void red() {
  setColour(100, 0, 0);
}

void orange() {
  setColour(100, 50, 0);
}
void yellow() {
  setColour(100, 100, 0);
}

void green() {
  setColour(0, 100, 0);
}

void cyan() {
  setColour(0, 100, 100);
}

void blue() {
  setColour(0, 0, 100);
}

void magenta() {
  setColour(100, 0, 100);
}

void turnOff() {
  setColour(0, 0, 0);
}
