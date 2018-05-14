const int buttonPin = 2; 
const int ledPin =  13;
int buttonState = 0; 

int data[5] = {0,0,0,0,0};
int control = 0;

long EsperaInicial = 0, EsperaFinal = 0, EsperaResultante = 0;
long TiempoInicial = 0, TiempoFinal = 0, TiempoResultante = 0;
bool btnPresionado = false, PrimeraVez = true;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if(control < 5){ //guarda las veces que se repiten
    
    if(buttonState == HIGH && !btnPresionado){
      if(PrimeraVez) TiempoInicial = millis();
      btnPresionado = true;
      delay(100);
      PrimeraVez=false;
    }else if(buttonState == LOW && btnPresionado){
      PrimeraVez=true;
      TiempoFinal = millis();
      EsperaInicial = millis();
      btnPresionado = false;
      delay(100);
      data[control] = almacenaValores(data[control]);
      control++;
    }

    EsperaFinal = millis();//asigna el tiempo de espera
    if(TimerSalida(EsperaInicial, EsperaFinal) && control != 0){ //despues de 3 segundos sin ingreso de datos finaliza
      //dador de datos
      Serial.println("LA LETRA ES: " + traductor(data[0],data[1],data[2],data[3],data[4]));
      Serial.println((String)data[0] + ", " +(String)data[1] + ", " +(String)data[2] + ", " +(String)data[3] + ", " +(String)data[4]);
      Serial.println("Finalizacion\n\nEn espera de nuevos valores...");
      control=0; // 5 es el estado de salida
    }
  }
}

bool EsGuion(long tiempoInicial, long tiempoFinal){
  TiempoResultante = tiempoFinal - tiempoInicial;
  if(TiempoResultante <= 500){
    return false;
  }else if(TiempoResultante > 500){
    return true;
  }
}

bool EsPunto(long tiempoInicial, long tiempoFinal){
  TiempoResultante = tiempoFinal - tiempoInicial;
  if(TiempoResultante <= 500){
    return true;
  }else if(TiempoResultante > 500){
    return false;
  }  
}
//data, si data = 1 punto, si data = 2 guion 
int almacenaValores(int data){
  if(EsGuion(TiempoInicial, TiempoFinal)){
    data=2;
    Serial.println("Data " + (String)control + ": " + (String)data);
  }else if(EsPunto(TiempoInicial, TiempoFinal)){
    data=1;
    Serial.println("Data " + (String)control + ": " + (String)data);    
  }
  return data;
}

bool TimerSalida(long esperaIni, long esperaFin){
  EsperaResultante = esperaFin - esperaIni;
  if(EsperaResultante > 3000){
    return true;
  }else if(EsperaResultante <= 3000){
    return false;
  }
}

String traductor(int d1,int d2,int d3,int d4,int d5){
if(d1==1 && d2==2 && d3==0 && d4==0 && d5==0) return "A";
if(d1==1 && d2==0 && d3==0 && d4==0 && d5==0) return "E";
if(d1==1 && d2==1 && d3==0 && d4==0 && d5==0) return "I";
if(d1==2 && d2==2 && d3==2 && d4==0 && d5==0) return "O";
if(d1==1 && d2==1 && d3==2 && d4==0 && d5==0) return "U";
return "No esta definido";
}

void Reinicia(){
  for(int k=0; k<5; k++){
    data[k] = 0;
  }
  control=0;
}


