
 const int latchPin = 8;
 const int clockPin = 12;
 const int dataPin = 11;
 
 void setup(){
  
   pinMode(latchPin, OUTPUT);
   pinMode(dataPin, OUTPUT);
   pinMode(clockPin, OUTPUT);
   Serial.begin(9600);
   Serial.println("reset");
 }
 
 void loop(){

  for (int bitsToSet=0; bitsToSet < 14; bitsToSet++) //hasta 14 porque se mueve de 3 en 3 las lucesitas
  {
    if (bitsToSet!=0) //pa evitar mandar LOW al pin -1 (no existe :V)
    {
       registerWrite(bitsToSet-1, LOW); //apagamos el pin de la iteracion anterior
    }   
    
    registerWrite(bitsToSet, HIGH); //encendemos el nuevo pin
    
    delay(30); 
  }
  for (int bitsToSet=13; bitsToSet > 0; bitsToSet--) //ahora vamos hacia atras \:V/
  {
    registerWrite(bitsToSet+1, LOW); //la misma mecanica de apagar anterior encender nuevo
    registerWrite(bitsToSet, HIGH);  
    delay(30); 
  }

}
  
 void registerWrite(int whichPin, int whichState) { //whichpin se refiere a cual led queremos encender, whichstate solo puede ser 0 o 1, osea HIGH o LOW
   byte bitsToSend = 0;   //si no ponemos esto pasan cosas feas alv, Ponemos el estado inicial en 00000000 bits //buffer de los leds rojos
   byte bitsToSendTwo = 0; //buffer de los leds verdes
      
   digitalWrite(latchPin, LOW); //iniciamos el estado de captura de bits
   
   if (whichPin < 6)//de 0 a 6 no hay pedo solo encendemos puros rojos
   {                                                  //bitWrite transforma un numero "int" en sus correspondientes bytes
      bitWrite(bitsToSend, whichPin, whichState);     //segun los bits del numero "int" convierte esas posiciones en 0 o 1, segun lo dicta whichState
      bitWrite(bitsToSend, whichPin+1, whichState);   //por lo tanto, el numero del led que queremos convertir lo convertimos en bits, segun LOW o HIGH, esa conversion se deposita en "bitsToSend"
      bitWrite(bitsToSend, whichPin+2, whichState);   //NOTESE que los 3 leds se esciben en el mismo buffer, esto es para hacer un OR, osea una suma de los bits de los 3 leds que queremos encender
   }
   if(whichPin == 6){ //del 6 al 7 es un cagadero aritmetico, mejor los ponemos con la vieja confiable :V
      bitWrite(bitsToSend, whichPin, whichState);
      bitWrite(bitsToSend, whichPin+1, whichState);
      bitWrite(bitsToSendTwo, 0, whichState);
   }
   if(whichPin == 7){
      bitWrite(bitsToSend, whichPin, whichState);
      bitWrite(bitsToSendTwo, 0, whichState);
      bitWrite(bitsToSendTwo, 1, whichState);
   }
   if (whichPin >= 8) //del 8 al 14 no hay pedo solo son los leds verdes
   { 
      bitWrite(bitsToSendTwo, (whichPin - 8), whichState);
      bitWrite(bitsToSendTwo, (whichPin - 7), whichState);
      bitWrite(bitsToSendTwo, (whichPin - 6), whichState);
   }
      
   shiftOut(dataPin, clockPin, MSBFIRST, bitsToSendTwo);  //Tenemos que depositar ambos buffer para evitar que queden restos de los bits de la operacion anterior
   shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);
   efect(7);  //efecto mamalon de parpadeo pa medio simular la "intensidad" :V
   digitalWrite(latchPin, HIGH);  //arrojamos los bits a los respectivos pines
 }

 void efect(int del){//efecto mamalon, solo reiniciamos el latch para "parpadeo" :V
   delay(del); 
   digitalWrite(latchPin, LOW);
   digitalWrite(latchPin, HIGH);
 }

