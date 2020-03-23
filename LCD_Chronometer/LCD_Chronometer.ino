/*
 * LCD "Hello, World!" example
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

int minutes = 0;
int seconds = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);

  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);
  lcd.print("Hello, World!");

  minutes = ((millis()/1000)/60);
  seconds = ((millis()/1000)%60);

  lcd.setCursor(0,1);
  if (minutes < 10) {
    lcd.print(0);
    lcd.setCursor(1,1);
  }
  lcd.print(minutes);

  lcd.setCursor(2, 1);
  lcd.print(":");
  
  lcd.setCursor(3, 1);
  if (seconds < 10) {
    lcd.print(0);
    lcd.setCursor(4,1);
  }
  lcd.print(seconds);
}
