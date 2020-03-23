#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 12, 11, 10, 9, 8);

int speakerPin = 5;
int buttonPin = 2;
int buttonPressTime = 0;

long timeLimit = 15000;
long startTime = 0;
int roundNumber = 0;
const int arraySize = 25;

const char* words [arraySize] = {"moose", "beaver", "bear",
"goose", "dog", "cat", "squirrel", "bird", "elephant", "horse",
"bull", "giraffe", "seal", "bat", "skunk", "turtle", "whale", 
"rhino", "lion", "monkey", "frog", "alligator", "kangaroo", 
"hippo", "rabbit"};

int sequence[arraySize];

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.clear();
  
  pinMode(speakerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  for(int i = 0; i < arraySize; i++) {
    sequence[i] = 0;
  }

  generateRandomOrder();

  showStartSequence();
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < arraySize; i++) {
    lcd.clear();

    roundNumber = i+1;
    lcd.print(roundNumber);
    lcd.print(": ");
    lcd.print(words[sequence[i]]);

    startTime = millis();

    while(digitalRead(buttonPin) == HIGH){
      int roundedTime = round((timeLimit - (millis() - startTime))/1000);
      lcd.setCursor(14, 1);
      lcd.print("  ");
      lcd.setCursor(14, 1);
      lcd.print(roundedTime);
      delay(15);

      if(millis() - startTime > timeLimit) {
        gameOver();
      }

      if(digitalRead(buttonPin) == LOW) {
        tone(speakerPin, 272, 1);
      }
    }

    delay(500);
  }
  winner();
}

//-----------------------FUNCTIONS-------------------------------------------

void showStartSequence() {
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Category:");
  lcd.setCursor(0,1);
  lcd.print("Animals");

  delay(2000);

  lcd.clear();
  lcd.print("Get ready");
  delay(1000);

  for(int i = 3; i > 0; i--) {
    lcd.clear();
    lcd.print(i);
    delay(1000);
  }
}

void generateRandomOrder(){
  randomSeed(analogRead(0));

  for(int i=0; i<arraySize - 1; i++){
    int currentNumber = 0;
    boolean match = false;

    do {
      currentNumber = random(0, arraySize);
      match = false;

      for(int i = 0; i < arraySize; i++) {
        if(currentNumber == sequence[i]){
          match = true;
        }
      }
    } while(match == true);
    sequence[i] = currentNumber;
  }
}

void gameOver() {
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Game Over");

  lcd.setCursor(0, 1);
  lcd.print("Score: ");
  lcd.print(roundNumber);

  tone(speakerPin, 130, 250);
  delay(275);
  tone(speakerPin, 73, 250);
  delay(275);
  tone(speakerPin, 65, 150);
  delay(175);
  tone(speakerPin, 98, 500);
  delay(500);

  while(true){}
}

void winner(){
  lcd.clear();
  
  lcd.setCursor(7, 0);
  lcd.print("YOU");

  lcd.setCursor(7,1);
  lcd.print("WIN");

  tone(speakerPin, 1318, 150);
  delay(175);
  tone(speakerPin, 1567, 150);
  delay(175);
  tone(speakerPin, 2637, 150);
  delay(175);
  tone(speakerPin, 2093, 150);
  delay(175);
  tone(speakerPin, 2349, 150);
  delay(175);
  tone(speakerPin, 3135, 500);
  delay(500);

  while(true){}
}
