int delayTime = 0;
int potPosition = 0;

int led = 13;
int potmtr;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  potPosition = analogRead(A0);

  delayTime = potPosition * 2;
  
  Serial.println(potPosition);
  digitalWrite(led, HIGH);
  delay(delayTime);
  digitalWrite(led, LOW);
  delay(delayTime);
}
