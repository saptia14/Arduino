// Project 19
#include <TimerOne.h>
int latchPin = 8; //Pin connected to Pin 12 of 74HC595 (Latch)
int clockPin = 12; //Pin connected to Pin 11 of 74HC595 (Clock)
int dataPin = 11; //Pin connected to Pin 14 of 74HC595 (Data)
byte ledH[8]; // 8 element unsigned integer array to store the sprite
byte ledP[8];
byte clean[8];
bool HoP=true;
void setup() {
  pinMode(latchPin, OUTPUT); // set the 3 digital pins to outputs
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  ledH[0] = B11000011; // enter the binary representation of the image
  ledH[1] = B11000011; // into the array
  ledH[2] = B11000011;
  ledH[3] = B11111111;
  ledH[4] = B11111111;
  ledH[5] = B11000011;
  ledH[6] = B11000011;
  ledH[7] = B11000011;

  ledP[0] = B00000011; // enter the binary representation of the image
  ledP[1] = B00000011; // into the array
  ledP[2] = B00000011;
  ledP[3] = B00000011;
  ledP[4] = B11111111;
  ledP[5] = B11000011;
  ledP[6] = B11000011;
  ledP[7] = B11111111;
  for(int i = 0; i < 8; i++){
    clean[i]=B00000000;
  }
  
// set a timer of length 10000 microseconds (1/100th of a second)
  Timer1.initialize(10000);
// attach the screenUpdate function to the interrupt timer
}

void loop() {

 delay(500);
 Timer1.attachInterrupt(screenUpdate);
 delay(500);
 Timer1.attachInterrupt(ClearScreen);
 if(HoP) HoP=false;
 else if(!HoP) HoP=true;
 
}

void ClearScreen(){
  byte row = B10000000; // row 1
  for (byte k = 0; k < 9; k++) {
    digitalWrite(latchPin, LOW); // open latch ready to receive data
    shiftIt(~clean[k] ); // shift out the LED array (inverted)
    shiftIt(row); // shift out row binary number
    digitalWrite(latchPin, HIGH);
    row = row >> 1; // bitshift left
  }
}
void screenUpdate() { // function to display image
  byte row = B10000000; // row 1
  
  if(HoP)   for (byte k = 0; k < 9; k++) {
    digitalWrite(latchPin, LOW); // open latch ready to receive data
    shiftIt(~ledH[k] ); // shift out the LED array (inverted)
    shiftIt(row); // shift out row binary number
    digitalWrite(latchPin, HIGH);
    row = row >> 1; // bitshift left
  }else if(!HoP)  for (byte k = 0; k < 9; k++) {
    digitalWrite(latchPin, LOW); // open latch ready to receive data
    shiftIt(~ledP[k] ); // shift out the LED array (inverted)
    shiftIt(row); // shift out row binary number
    digitalWrite(latchPin, HIGH);
    row = row >> 1; // bitshift left
  }
}

void shiftIt(byte dataOut) { // Shift out 8 bits LSB first, on rising edge of clock
  boolean pinState;
  digitalWrite(dataPin, LOW); //clear shift register read for sending data
  for (int i=0; i<8; i++) { // for each bit in dataOut send out a bit
    digitalWrite(clockPin, LOW); //set clockPin to LOW prior to sending bit
    if ( dataOut & (1<<i) ) {
      pinState = LOW;
    }
    else {
      pinState = HIGH;
    }
    //sets dataPin to HIGH or LOW depending on pinState
    digitalWrite(dataPin, pinState);
    digitalWrite(clockPin, HIGH); //send bit out on rising edge of clock
    digitalWrite(dataPin, LOW);
  }
  digitalWrite(clockPin, LOW); //stop shifting
}
