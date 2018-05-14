int LedPin = 10;
int DelayPunto = 200;
int DelayGuion = 700;

void setup() {
pinMode(LedPin, OUTPUT);
}

void loop() {
  
EscribeLetra(1,2,0,0); // A = . -
EscribeLetra(2,2,0,0); // M = - -
EscribeLetra(1,2,0,0); // A = . -
EscribeLetra(1,1,2,0); // U = . . -
EscribeLetra(1,2,1,0); // R = . - .
EscribeLetra(2,1,2,2); // Y = - . - -
delay(5000);

}

//sistema funcion si es 1 = punto, si es 2 = guion
void Dibuja(int digito){
  switch(digito){
    case 1: digitalWrite(LedPin, HIGH);
            delay(DelayPunto);
            digitalWrite(LedPin, LOW); 
    break;
    case 2: digitalWrite(LedPin, HIGH);
            delay(DelayGuion); 
            digitalWrite(LedPin, LOW);
    break;
    default: // no dibuja nada y da skip al siguiente punto o guion
    break;
  }
}

void EscribeLetra(int dig1, int dig2, int dig3, int dig4){
  Dibuja(dig1);
  delay(500);
  Dibuja(dig2);
  delay(500);
  Dibuja(dig3);
  delay(500);
  Dibuja(dig4);
  delay(500);
}

