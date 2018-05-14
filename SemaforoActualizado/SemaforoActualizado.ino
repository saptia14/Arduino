const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;     // the number of the LED pin

const int ledVerde = 8;
const int ledAmarillo = 9;
const int ledRojo = 10;

int tiempoCambio = 2000;
bool GentePasando = false;

int buttonState = LOW;         // variable for reading the pushbutton status

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {

  if(!GentePasando){
     
     if (buttonState == HIGH) {
      GentePasando = true;
      delay(tiempoCambio);
     }else {
      digitalWrite(ledVerde,HIGH);
      buttonState = digitalRead(buttonPin);
     }
     
  }else{
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarillo, HIGH);
    delay(tiempoCambio);
    digitalWrite(ledAmarillo, LOW);
    
    digitalWrite(ledPin, HIGH);
    digitalWrite(ledRojo, HIGH);
    delay(4000);
    digitalWrite(ledPin,LOW);
    digitalWrite(ledRojo,LOW);
    
    GentePasando = false;    
  }  
}
