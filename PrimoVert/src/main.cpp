/* 
Microscope Zeiss PrimoVert Circuit Board by MIC-BMC

Responsable Research: Profa. Dra. Marilene Hohmuth Lopes - marilenehl@usp.br 
Techinical Developer: Dr. Kelliton Jose Mendonca Francisco - kelliton@usp.br

Hardware: Atmel328
Driver: BTS7960
IDE: Visual Studio Code version 1.96.4 and PlatformIO Core 6.1.16

Developed by the Scientific Maintenance and Instrumentation Division - BMC
*/

#include <Arduino.h>

//Pins declatarions:
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
#define butLightR_Pin 14 //button light ON / OFF
#define butLightL_Pin 15 //button light ON / OFF
#define ris_Pin A5 //read pin for current sensor R channel
#define lis_Pin A6 //read pin for current sensor L channel
#define potLine_Pin A7 //read pin for adjust light

//Variables declarations:
bool lightState = LOW;
bool readButton_L, readButton_R;
bool lastButState_L, lastButState_R = LOW;
long int lis, ris; //Status of Currente from L and R channel
int readButton, adjLamp, adjLampMap;
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
    for (int i=12; i>8; i--){ //Off pins 12, 11, 10, 9
      digitalWrite(i,LOW);
    }
  }
  if (valor > 50 && valor < 102){
     for (int i=12; i>11; i--){ //On pin 12
      digitalWrite(i,HIGH);
    }
    for (int i=11; i>8; i--){ //Off pins 11, 10, 9
      digitalWrite(i,LOW);
    }
  }
  if (valor > 101 && valor < 153){
     for (int i=12; i>10; i--){ //On pins 12, 11
      digitalWrite(i,HIGH);
    }
    for (int i=10; i>8; i--){ //Off pins 10, 9
      digitalWrite(i,LOW);
    }
  }
  if (valor > 152 && valor < 204){
     for (int i=12; i>9; i--){ //On pins 12, 11, 10
      digitalWrite(i,HIGH);
    }
    digitalWrite(9,LOW); //Off pin 9
  }
  if (valor > 203 && valor < 256){
     for (int i=12; i>8; i--){ //On pins 12, 11, 10, 9
      digitalWrite(i,HIGH);
    }
  }
}

//Read buttons Auto
void buttonON(){
  readButton_L = digitalRead(butLightL_Pin);
  readButton_R = digitalRead(butLightR_Pin); 
  if ((readButton_L != lastButState_L) || (readButton_R != lastButState_R)){
    lastButState_L = readButton_L;
    lastButState_R = readButton_R;
    if((lastButState_L == LOW) || (lastButState_R == LOW)){
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

  //Setting of Serial communication
  Serial.begin(9600);

  //Settings pins of Atmel328
  for (int i=3; i<16; i++){
    pinMode(i,OUTPUT);
  }
  pinMode(butLightL_Pin, INPUT);
  pinMode(butLightR_Pin, INPUT);
  pinMode(potLine_Pin,INPUT);

  //Settings of the driver lamp
  for (int i=7; i<16; i++){
    digitalWrite(i,LOW);
  }
  digitalWrite(len_Pin,LOW); //Enable L channel
  digitalWrite(ren_Pin,LOW); //Disable R channel
  analogWrite(rpwm_Pin,0); //R Channel Off from PWM control
  digitalWrite(led0_Pin,HIGH);

  //Read status of Microscope ON
  blinkLed();
}

//Main
void loop() {
  buttonON(); // Read Status of Buttons
  adjustLamp(); // Adjust intensity of Lamp
  currentRead(); // Read Current value
  if(lightState==LOW){ // Blink Led if standby mode on
    standbyBlink();
  }
}