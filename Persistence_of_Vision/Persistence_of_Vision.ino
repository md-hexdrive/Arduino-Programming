/*
 * blink an led so fast it appears to always be on
 * 
 * A delayTime of 10 or 11 will work good.
 */


int led = 13;
int delayTime = 10;

void setup() {
  pinMode(led, OUTPUT);

}

void loop() {
  digitalWrite(led, HIGH);
  delay(delayTime);
  digitalWrite(led, LOW);
  delay(delayTime);
}
