int led = 11;
int photoresistor = 0;
int threshold = 750;

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
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }

  delay(100);
}
