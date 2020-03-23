//set pins for button + buzzer
int firstKeyPin = 2;
int secondKeyPin = 3;
int thirdKeyPin = 4;
int fourthKeyPin = 5;

int buzzerPin = 10;

int one = 1;
int two = 2;
int three = 3;
int four = 4;

void setup() {
  // set the button pins as inputs
  pinMode(firstKeyPin, INPUT_PULLUP);
  pinMode(secondKeyPin, INPUT_PULLUP);
  pinMode(thirdKeyPin, INPUT_PULLUP);
  pinMode(fourthKeyPin, INPUT_PULLUP);

  // set the buzzer pin as output
  pinMode(buzzerPin, OUTPUT);
  
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  int frequencies[] = {220, 247, 262, 294, 330, 
  349, 392, 440, 494, 523};

  int note = 0;
  if(digitalRead(firstKeyPin) == LOW) {
    note += one;
  } 
  
  if (digitalRead(secondKeyPin) == LOW) {
    note += two;
  }
  
  if(digitalRead(thirdKeyPin) == LOW) {
    note += three;
  }
  
  if(digitalRead(fourthKeyPin) == LOW) {
    note += four;
  }
  
  if (note > 0) {
    Serial.print("frequencies[");
    Serial.print(note - 1); 
    Serial.print("] = ");
    Serial.println(frequencies[note - 1]);
    delay(100);
    tone(buzzerPin, frequencies[note - 1]);
  }
  else {
    noTone(buzzerPin);
  }
  

  

}

/*
  note  frequency
  c     262 Hz
  d     294 Hz
  e     330 Hz
  f     349 Hz
  g     392 Hz
  a     440 Hz
  b     494 Hz
  C     523 Hz
  */
