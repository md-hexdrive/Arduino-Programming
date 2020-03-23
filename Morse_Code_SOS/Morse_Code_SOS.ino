
/**
 * blinks a message in morse code
 */

int led = 13;
int delayLong = 700;
int delayShort = 250;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  dot();
  dot();
  dot();
  dash();
  dash();
  dash();
//  dot();
//  dot();
//  dot();
//  delay(1000);
}

void dot() {
  delay(delayShort);
  on();
  delay(delayShort);
  off();
}

void dash() {
  delay(delayLong);
  on();
  delay(delayLong);
  off();
}

void on() {
  digitalWrite(led, HIGH);
}

void off() {
  digitalWrite(led, LOW);
}
