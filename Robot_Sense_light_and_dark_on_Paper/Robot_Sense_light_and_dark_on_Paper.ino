int led = 13;
int button = 10;

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

boolean rightWhite;
boolean leftWhite;

float distance;


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
  rightWhite = rightSensorOnWhite();
  leftWhite = leftSensorOnWhite();

  if(!leftWhite && rightWhite) {
    forwards(3);
  }
  else if(leftWhite && !rightWhite) {
    turnRight(10);
    forwards(3);
  }
  else if(leftWhite && rightWhite) {
    turnLeft(10);
    forwards(3);
  }
  else if(!leftWhite && !rightWhite) {
    
  }
  else {
    
  }
}

int rPhotocell() {
  return analogRead(A0);
}

int lPhotocell() {
  return analogRead(A1);
}

boolean leftSensorOnWhite() {
  int reading = lPhotocell();
  if(reading <= leftThreshold) {
    return false;
  }
  else {
    return true;
  }
}

boolean rightSensorOnWhite() {
  int reading = rPhotocell();
  if(reading <= rightThreshold) {
    return false;
  }
  else {
    return true;
  }
}
