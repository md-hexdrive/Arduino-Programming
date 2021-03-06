/*
 * This is a kitchen timer emulator program that uses interrupts to stop/play the timer.
 * 
 */
#include <LiquidCrystal.h>

int speakerPin = 2;
int secBut = 5;
int minBut = 4;
int start_stop_button = 3;

int switchPin = 6;

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

int startMinutes = 0;
int startSeconds = 0;

int minsLeft = startMinutes; // the number of minutes left
int secsLeft = startSeconds; // the number of seconds left

int startMillis = millis(); // startMillis holds the time the timer started at

boolean on = true;
boolean running = false;

int debounce = 500; // the amount of time to wait between a button press and the next button press being processed

void setup() {
  // put your setup code here, to run once:
  pinMode(speakerPin, OUTPUT);

  pinMode(secBut, INPUT_PULLUP);
  pinMode(minBut, INPUT_PULLUP);
  pinMode(start_stop_button, INPUT_PULLUP);

  pinMode(switchPin, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.clear();

  Serial.begin(9600);

}

void loop() {
  message("Enter run time:");
  printTime(startMinutes, startSeconds);

  while(true) {
    if(digitalRead(start_stop_button) == LOW) {
      delay(debounce);
      break;
    }
    else if(digitalRead(minBut) == LOW && 
    digitalRead(secBut) == LOW) {
      startMinutes = 0;
      startSeconds = 0;
      printTime(startMinutes, startSeconds);
      delay(debounce);
    }
    else if(digitalRead(minBut) == LOW) {
      incrementMinutes();
    }
    else if(digitalRead(secBut) == LOW) {
      incrementSeconds();
    }
  }
  timer();
  delay(1000);
}

/*
 * incrementMinutes() increases the number of minutes by one,
 * while ensuring that the total # of minutes < 100 (because the
 * lcd printing code won't handle minute numbers with more than 
 * three digits)
 */
void incrementMinutes() {
  startMinutes++;
  if (startMinutes > 99) {
    startMinutes = 0;
  }
  printTime(startMinutes, startSeconds);
  delay(debounce); // button debounce
}

/*
 * incrementSeconds() increases the number of seconds by one,
 * while ensuring that the total # of seconds < 60
 */
void incrementSeconds() {
  startSeconds++;
  if (startSeconds > 59) {
    startMinutes = 0;
  }
  printTime(startMinutes, startSeconds);
  delay(debounce); // button debounce
}
/*
 * timer() runs the entire timing code
 */
void timer() {
  minsLeft = startMinutes;
  secsLeft = startSeconds;
  countdown();
  alarm();
}
/*
 * alarm() plays when the timer is finished
 */
void alarm() {
  message("Done");
  printTime(minsLeft, secsLeft);
  int runLength = 8;
  int delayTime = 500;
  for (int i = 0; i < runLength; i++) {
    tone(speakerPin, 261, delayTime);
    delay(delayTime);
    delay(delayTime);
  }
}
/*
 * countdown() is responsible for running the timer
 */
void countdown() {
  while(true) {
    if(minsLeft == 0 && secsLeft == 0) {
      message("Done.");
      break;
    }
    message("Running...");
    printTime(minsLeft, secsLeft);
    wait(millis(), 1000l);
    //delay(1000);
    decrement();
  }
}

/*
 * wait() allows the timer to be paused while it is running
 * 
 * 
 */
void wait(unsigned long startTime, unsigned long delayTime) {
  unsigned long waitUntil = startTime + delayTime;
  while(millis() < waitUntil) {
    
    if(digitalRead(start_stop_button) == LOW) {
      message("Stopped");
      printTime(minsLeft, secsLeft);
      delay(debounce);
      
      while(digitalRead(start_stop_button) != LOW) {}  // wait in a loop until 
      
      message("Running...");
      delay(debounce);
      break;
    }
  }
}
/*
 * decrement counts down by one second
 */
void decrement() {
  
  if(secsLeft == 0 && minsLeft > 0) {
    secsLeft = 59;
    minsLeft--;
  }
  else if (secsLeft >= 0 && minsLeft >= 0) {
    secsLeft--;
  }
}

/*
 * message() prints a user message to the top of the LCD
 */
void message(String msg) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(msg);
  //printTime(minsLeft, secsLeft);
}
/*
 * print the time in minutes and seconds
 */
void printTime(int mins, int secs) {
  lcd.setCursor(0,1);
  if (mins < 10) {
    lcd.print(0);
    lcd.setCursor(1, 1);
    Serial.print(0);
  }
  lcd.print(mins);
  Serial.print(mins);

  lcd.setCursor(2, 1);
  lcd.print(":");
  Serial.print(":");

  lcd.setCursor(3, 1);
  if (secs < 10) {
    lcd.print(0);
    lcd.setCursor(4, 1);
    Serial.print(0);
  }
  lcd.print(secs);
  Serial.println(secs);

}
