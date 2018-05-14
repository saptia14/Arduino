// Project 16 - Using an L293D Motor Driver IC
#define switchPin 2 // switch input
#define switchPin2 3 // switch input

#define motorPin11 9 // L293D Input 1
#define motorPin12 10 // L293D Input 2
#define motorPin21 12 // L293D Input 3
#define motorPin22 13 // L293D Input 4
#define speedPin 8 // L293D enable pin 1
#define speedPin2 11
// L293D enable pin 2

#define potPin A0 // Potentiometer on analog Pin 0
#define potPin2 A1 // Potentiometer on analog Pin 1
int Mspeed = 0;  // a variable to hold the current speed value
int Mspeed2 = 0;  // a variable to hold the current speed value

void setup() {
//set switch pin as INPUT
pinMode(switchPin, INPUT);
pinMode(switchPin2, INPUT);

// set remaining pins as outputs
pinMode(motorPin11, OUTPUT);
pinMode(motorPin12, OUTPUT);
pinMode(speedPin, OUTPUT);

pinMode(motorPin21, OUTPUT);
pinMode(motorPin22, OUTPUT);
pinMode(speedPin2, OUTPUT);
}

void loop() {
  Mspeed = analogRead(potPin)/4; // read the speed value from the potentiometer
  Mspeed2 = analogRead(potPin2)/4;
  
  analogWrite(speedPin, Mspeed); // write speed to Enable 1 pin
  analogWrite(speedPin2, Mspeed2);
  
  if (digitalRead(switchPin)) { // If the switch is HIGH, rotate motor clockwise
    digitalWrite(motorPin11, LOW); // set Input 1 of the L293D low
    digitalWrite(motorPin12, HIGH); // set Input 2 of the L293D high
  }
  else {  // if the switch is LOW, rotate motor anti-clockwise
    digitalWrite(motorPin11, HIGH); // set Input 1 of the L293D low
    digitalWrite(motorPin12, LOW); // set Input 2 of the L293D high
  }

  if (digitalRead(switchPin2)) { // If the switch is HIGH, rotate motor clockwise
    digitalWrite(motorPin21, LOW); // set Input 1 of the L293D low
    digitalWrite(motorPin22, HIGH); // set Input 2 of the L293D high
  }
  else {  // if the switch is LOW, rotate motor anti-clockwise
    digitalWrite(motorPin21, HIGH); // set Input 1 of the L293D low
    digitalWrite(motorPin22, LOW); // set Input 2 of the L293D high
  }
  
}
