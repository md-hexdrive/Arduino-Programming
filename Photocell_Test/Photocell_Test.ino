void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int r0 = analogRead(A0);
  int r1 = analogRead(A1);

  Serial.print("Left Photocell: ");
  Serial.print(r1);
  Serial.print(",   Right Photocell: ");
  Serial.println(r0);

  delay(100);

}
