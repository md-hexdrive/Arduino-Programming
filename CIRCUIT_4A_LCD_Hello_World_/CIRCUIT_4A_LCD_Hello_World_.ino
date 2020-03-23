/*
 * LCD "Hello, World!" example
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);

  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);
  lcd.print("Hello, World!");

  lcd.setCursor(0,1);
  lcd.print(millis()/1000);
  delay(1000);
}
