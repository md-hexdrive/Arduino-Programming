/*
 * This program is meant to simulate the movement of the elbow
 * joint with a servo motor.
 * 
 * It takes input from the Serial Monitor or a potentiometer
 * and uses it to specify the angle to move the servo to (from 
 * 20 to 160 degrees).
 * 
 * This code is based on code from SIK Circuits 3A and 5A.
 */

#include <Servo.h> // import Servo library to use it

Servo myServo; // create a servo object

// put the pin numbers used into variables
int servoPin = 9;
int switchPin = 7;
int dialPin = A0;

int position; // holds the position to move to

void setup() {
  pinMode(switchPin, INPUT_PULLUP);
  myServo.attach(servoPin);
  Serial.begin(9600);
  myServo.write(90); // move the servo to 90 degrees

  // give the prompt
  Serial.println("Enter an angle to turn the servo to from 20 to 160 degrees.");
}

void loop() {
  // if the switch is on, read the position from the serial monitor
  if(digitalRead(switchPin) == LOW){
    if(Serial.available() > 0) { // make sure there is user input available
      position = Serial.parseInt();
      if(position <= 160 && position >= 20) {
        writeServo(position);
      }
      else {
        Serial.print("ERROR - only a value between 0 and 180 can be used as input.");
      }
    }
  }
  // otherwise, read the position from the potentiometer
  else {
    position = analogRead(dialPin);
    position = map(position, 0, 1023, 20, 160);
    writeServo(position);
  }
}

/*
 * move the servo to position
 */
void writeServo(int position) {
  myServo.write(position);

  Serial.print("Servo position: ");
  Serial.print(position);
  Serial.println(" degrees.");      
}
