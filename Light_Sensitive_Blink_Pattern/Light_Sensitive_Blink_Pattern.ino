int led = 11;
int photoresistor = 0;
int threshold = 750;

int delayLong = 700;
int delayShort = 250;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  Serial.begin(9600);

}


void loop() {
  // put your main code here, to run repeatedly:
    photoresistor = analogRead(A0);

  Serial.println(photoresistor);
  
  if (photoresistor < threshold) {
      dot();
      dot();
      dot();
      
  } else {
    digitalWrite(led, LOW);
  }

  delay(100);

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
