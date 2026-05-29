/* 
Manutenção da placa controladora do Microscópio Zeiss Primo Vert.

Responsable Research: Profa. Dra. Marilene Hohmuth Lopes - marilenehl@usp.br 
Techinical Developer: Dr. Kelliton Jose Mendonca Francisco - kelliton@usp.br

Hardware: Atmel328
IDE: Visual Studio Code version 1.96.4 and PlatformIO Core 6.1.16

Developed by the Scientific Maintenance and Instrumentation Division - BMC

*/

#include <Arduino.h>

//pins declatarions:
#define len_Pin 3 //Enable counter clockwise > Enable in HIGH
#define ren_Pin 4 //Enable clockwise > Enable in HIGH
#define lpwm_Pin 5 //Intensity control to L channel
#define rpwm_Pin 6 //Intensity control to R channel
#define aux1_Pin 7 //Enable AUX port 8 (J15-P2)
#define led0_Pin 8 //Enable Led 1 indicator of Microscope ON
#define led1_Pin 9 //Enable Led 2 indicator from intensity of light
#define led2_Pin 10 //Enable Led 3 indicator from intensity of light
#define led3_Pin 11 //Enable Led 4 indicator from intensity of light
#define led4_Pin 12 //Enable Led 5 indicator from intensity of light
#define aux2_Pin 13 //Enable AUX port 7 (J15-P1)
#define butLight2_Pin 14 //button light ON / OFF
#define butLight1_Pin 15 //button light ON / OFF
#define ris_Pin A5 //read pin for current sensor R channel
#define lis_Pin A6 //read pin for current sensor L channel
#define potLine_Pin A7 //read pin for adjust light

//Variables declarations:
bool lightState = LOW;
bool readButton_1, readButton_2;
bool lastButState_1, lastButState_2 = LOW;

long int lis, ris;
int readButton;
int adjLamp, adjLampMap;
int dlyLamp = 1;

//Status of Microscope ON
void blinkLed(){
  for (int i=8; i<13; i++){
    digitalWrite(i,HIGH);
    delay(10);
  }
  delay(3000);
  for (int i=9; i<13; i++){
    digitalWrite(i,LOW);
    delay(10);
  }
  delay(3000);
}

void standbyBlink(){
  digitalWrite(led0_Pin,LOW);
  delay(500);
  digitalWrite(led0_Pin,HIGH);
  delay(500);
}
void currentLed(int valor){
  if (valor < 51) {
    for (int i=12; i>8; i--){ //desliga 12, 11, 10, 9
      digitalWrite(i,LOW);
    }
  }
  if (valor > 50 && valor < 102){
     for (int i=12; i>11; i--){ //Liga 12
      digitalWrite(i,HIGH);
    }
    for (int i=11; i>8; i--){ //desliga 11, 10, 9
      digitalWrite(i,LOW);
    }
  }
  if (valor > 101 && valor < 153){
     for (int i=12; i>10; i--){ //Liga 12, 11
      digitalWrite(i,HIGH);
    }
    for (int i=10; i>8; i--){ //desliga 10, 9
      digitalWrite(i,LOW);
    }
  }
  if (valor > 152 && valor < 204){
     for (int i=12; i>9; i--){ //Liga 12, 11, 10
      digitalWrite(i,HIGH);
    }
    digitalWrite(9,LOW); //desliga 9
  }
  if (valor > 203 && valor < 256){
     for (int i=12; i>8; i--){ //Liga 12, 11, 10, 9
      digitalWrite(i,HIGH);
    }
  }
}
//Read buttons Auto
void buttonON(){
  readButton_1 = digitalRead(butLight1_Pin);
  readButton_2 = digitalRead(butLight2_Pin); 
  if ((readButton_1 != lastButState_1) || (readButton_2 != lastButState_2)){
    lastButState_1 = readButton_1;
    lastButState_2 = readButton_2;
    if((lastButState_1 == LOW) || (lastButState_2 == LOW)){
      lightState = !lightState;
      if(lightState==LOW){
        digitalWrite(len_Pin,lightState); //Disable L channel
        digitalWrite(ren_Pin,lightState); //Disable R channel
      }
      if(lightState==HIGH){
        digitalWrite(len_Pin,lightState); //Enable L channel
        digitalWrite(ren_Pin,lightState); //Enable R channel
      }
    }
  }
}

//Current Driver Read
void currentRead(){
  lis = analogRead(lis_Pin);
  ris = analogRead(ris_Pin);
  Serial.print(lis);
  Serial.print(" ");
  Serial.println(ris);
}

void adjustLamp(){
  adjLamp = analogRead(potLine_Pin);
  adjLamp = map(adjLamp,0,1023,255,0);
  analogWrite(lpwm_Pin,adjLamp);
  currentLed(adjLamp);
}

void setup() {

  Serial.begin(9600);
  for (int i=3; i<16; i++){
    pinMode(i,OUTPUT);
  }
  pinMode(butLight1_Pin, INPUT);
  pinMode(butLight2_Pin, INPUT);
  pinMode(potLine_Pin,INPUT);

  //Settings of the driver lamp
  for (int i=7; i<16; i++){
    digitalWrite(i,LOW);
  }
  digitalWrite(len_Pin,LOW); //Enable L channel
  digitalWrite(ren_Pin,LOW); //Disable R channel
  analogWrite(rpwm_Pin,0); //R Channel Off from PWM control
  digitalWrite(led0_Pin,HIGH);

  //Status of Microscope ON
  blinkLed();
}


void loop() {
  buttonON();
  adjustLamp();
  currentRead();
  //delay(100); 
  if(lightState==LOW){
    standbyBlink();
  }
}