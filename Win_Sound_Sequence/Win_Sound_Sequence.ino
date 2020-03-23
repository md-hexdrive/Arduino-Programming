int buzzerPin = 10;
void setup() {
  // put your setup code here, to run once:
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int toneSequence[] = {1318, 1567, 2637, 2093, 2349, 3135};

  for(int t : toneSequence) {
    tone(buzzerPin, t, 150);
    delay(175);
  }

  while(true) {}
}
