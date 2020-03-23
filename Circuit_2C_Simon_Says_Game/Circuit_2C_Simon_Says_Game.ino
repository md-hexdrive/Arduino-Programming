
int button[] = {2, 4, 6, 8};

int led[] = {3, 5, 7, 9};

int tones[] = {262, 330, 392, 494};

int roundsToWin = 10;

int buttonSequence[16];

int buzzerPin = 10;

int pressedButton = 4;

int roundCounter = 1;


long startTime = 0;
long timeLimit = 5000;
boolean gameStarted = false;


void setup() {
  // put your setup code here, to run once:
  for(int i: button) {
    pinMode(i, INPUT_PULLUP);
  }

  for(int j: led) {
    pinMode(j, OUTPUT);
  }

  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  if (gameStarted == false) {
    startSequence();
    roundCounter = 0;
    delay(1500);
    gameStarted = true;
  }

  for (int i = 0; i <= roundCounter; i++) {
    flashLED(buttonSequence[i]);
    delay(200);
    allLEDoff();
    delay(200);
  }

  for(int i = 0; i <= roundCounter; i++) {
    startTime = millis();

    while (gameStarted == true) {
      pressedButton = buttonCheck();

      if (pressedButton < 4) {
        flashLED(pressedButton);

        if (pressedButton == buttonSequence[i]) {
          delay(250);
          allLEDoff();
          break;
        } else {
          Serial.print("You pressed button ");
          Serial.print(pressedButton);
          Serial.print(" instead of button ");
          Serial.println(buttonSequence[i]);

          loseSequence();
          break;
        }
      } else {
        allLEDoff();
      }

      if (millis() - startTime > timeLimit) {
        Serial.println("You took to long and lost.");

        loseSequence();
        break;
      }
    }
  }

  if (gameStarted == true) {
    roundCounter = roundCounter + 1;

    if (roundCounter >= roundsToWin) {
      winSequence();
    }

    delay(500);
  }

}


void flashLED(int i) {
  tone(buzzerPin, tones[i]);
  digitalWrite(led[i], HIGH);
}


void allLEDoff() {
  for(int l : led) {
    digitalWrite(l, LOW);
  }
  noTone(buzzerPin);
}


int buttonCheck() {
  for (int i = 0; i < 4; i++) {
    if (digitalRead(button[i]) == LOW) {
      return i;
    }
  }
  
  return 4;
  
}


void startSequence() {

  randomSeed(analogRead(A0)); // ensure random #s are really random

  for (int i = 0; i <= roundsToWin; i++) {
    buttonSequence[i] = round(random(0, 4));
  }

  for (int i = 0; i < 3; i++) {

    tone(buzzerPin, tones[i], 200);

    for(int i: led) {
      digitalWrite(i, HIGH);
    }

    delay(100);

    for(int i: led) {
      digitalWrite(i, LOW);
    }

    delay(100);
  }
}


void winSequence() {

  for(int j = 0; j <= 3; j++) {
    digitalWrite(led[j], HIGH);
  }

  int toneSequence[] = {1318, 1567, 2637, 2093, 2349, 3135};

  for(int t : toneSequence) {
    tone(buzzerPin, t, 150);
    delay(175);
  }

  delay(500 - 175);

  waitForButtonPress();

}


void loseSequence() {
  for (int j = 0; j <= 3; j++) {
    digitalWrite(led[j], HIGH);
  }

  tone(buzzerPin, 130, 250);
  delay(275);
  tone(buzzerPin, 73, 250);
  delay(275);
  tone(buzzerPin, 65, 150);
  delay(175);
  tone(buzzerPin, 98, 500);
  delay(500);

  waitForButtonPress();
}

void waitForButtonPress() {
  do {
    pressedButton = buttonCheck();
  } while (pressedButton > 3);
  delay(200);

  gameStarted = false;
}
