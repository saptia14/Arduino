int LedPin = 10;
char buffer[18];

int DelayPunto = 200;
int DelayGuion = 700;

void setup() {
  Serial.begin(9600);
  Serial.flush();
  pinMode(LedPin, OUTPUT);
}

void loop() {
  if(Serial.available() > 0){
    int index = 0;
    delay(100); 
    int numChar = Serial.available();
    buffer[index] = Serial.read();
    Clasifica(buffer);        
  }else {
  Serial.print("[2J");  
  }
}

void Clasifica(char* data){
  String letra = data;
  letra.toLowerCase();
  Serial.print("Codificando:  ");
  Serial.println(data);
  Serial.println(letra.charAt(0));
  
  switch(letra.charAt(0)){
    // MANEJO DE LETRAS
    case 'a': EscribeLetra(1,2,0,0,0); break;             
    case 'b': EscribeLetra(2,1,1,1,0); break;
    case 'c': EscribeLetra(2,1,2,1,0); break;
    case 'd': EscribeLetra(2,1,1,0,0); break;
    case 'e': EscribeLetra(1,0,0,0,0); break;
    case 'f': EscribeLetra(1,1,2,1,0); break;
    case 'g': EscribeLetra(2,2,1,0,0); break;
    case 'h': EscribeLetra(1,1,1,1,0); break;
    case 'i': EscribeLetra(1,1,0,0,0); break;
    case 'j': EscribeLetra(1,2,2,2,0); break;
    case 'k': EscribeLetra(2,1,2,0,0); break;
    case 'l': EscribeLetra(1,2,1,1,0); break;
    case 'm': EscribeLetra(2,2,0,0,0); break;
    case 'n': EscribeLetra(2,1,0,0,0); break;
    case 'o': EscribeLetra(2,2,2,0,0); break;
    case 'p': EscribeLetra(1,2,2,1,0); break;
    case 'q': EscribeLetra(2,2,1,2,0); break;
    case 'r': EscribeLetra(1,2,1,0,0); break;
    case 's': EscribeLetra(1,1,1,0,0); break;
    case 't': EscribeLetra(2,0,0,0,0); break;
    case 'u': EscribeLetra(1,1,2,0,0); break;
    case 'v': EscribeLetra(1,1,1,2,0); break;
    case 'w': EscribeLetra(1,2,2,0,0); break;
    case 'x': EscribeLetra(2,1,1,2,0); break;
    case 'y': EscribeLetra(2,1,2,2,0); break;
    case 'z': EscribeLetra(2,2,1,1,0); break;
    // MANEJO DE NUMEROS
    case '1': EscribeLetra(1,2,2,2,2); break;
    case '2': EscribeLetra(1,1,2,2,2); break;
    case '3': EscribeLetra(1,1,1,2,2); break;
    case '4': EscribeLetra(1,1,1,1,2); break;
    case '5': EscribeLetra(1,1,1,1,1); break;
    case '6': EscribeLetra(2,1,1,1,1); break;
    case '7': EscribeLetra(2,2,1,1,1); break;
    case '8': EscribeLetra(2,2,2,1,1); break;
    case '9': EscribeLetra(2,2,2,2,1); break;
    case '0': EscribeLetra(2,2,2,2,2); break;
    }
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

void EscribeLetra(int dig1, int dig2, int dig3, int dig4, int dig5){
  Dibuja(dig1);
  if(dig1 != 0) delay(500);
  Dibuja(dig2);
  if(dig2 != 0) delay(500);
  Dibuja(dig3);
  if(dig3 != 0) delay(500);
  Dibuja(dig4);
  if(dig4 != 0) delay(500);
  Dibuja(dig5);
  if(dig5 != 0) delay(500);
  delay(1000);
}

