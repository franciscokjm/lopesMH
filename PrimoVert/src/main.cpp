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
#define led0_Pin 8 //Enable Led 1 indicator from intensity of light
#define led4_Pin 9 //Enable Led 5 indicator from intensity of light
#define led3_Pin 10 //Enable Led 4 indicator from intensity of light
#define led2_Pin 11 //Enable Led 3 indicator from intensity of light
#define led1_Pin 12 //Enable Led 2 indicator from intensity of light
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


int readButton;
int lis, ris, adjLamp, adjLampMap;
int dlyLamp = 2000;

//Status of Microscope ON
void blinkLed(){
  for(int i=0; i<2; i++){
    for (int i=8; i<13; i++){
      digitalWrite(i,HIGH);
    }
    delay(3000);
    for (int i=8; i<13; i++){
      digitalWrite(i,LOW);
    }
    delay(3000);
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
      int val = adjLamp;
      if(lightState==LOW){
        do{
          delay(dlyLamp);
          val = val-1;
          analogWrite(lpwm_Pin,val);
        }while (val<1);
        digitalWrite(len_Pin,lightState); //Enable L channel
        digitalWrite(ren_Pin,lightState); //Disable R channel
      }
      if(lightState==HIGH){
        digitalWrite(len_Pin,lightState); //Enable L channel
        digitalWrite(ren_Pin,lightState); //Disable R channel
        do{
          delay(dlyLamp);
          val = val+1;
          analogWrite(lpwm_Pin,val);
        }while (val<1);
      }
    }
  }


  Serial.print("lightState: ");
  Serial.println(lightState);

}

//Current Driver Read
void currentRead(){
  lis = analogRead(lis_Pin);
  ris = analogRead(ris_Pin);
  Serial.print(lis);
  Serial.print(" ");
  Serial.print(ris);
}

void adjustLamp(){
  adjLamp = analogRead(potLine_Pin);
  adjLamp = map(adjLamp,0,1023,255,0);
  analogWrite(lpwm_Pin,adjLamp);
  if (adjLamp < 51) {
    digitalWrite(8,HIGH);
    for (int i=9; i<13; i++){
      digitalWrite(i,LOW);
    }
  }
  if (adjLamp > 50 && adjLamp < 102){
     for (int i=8; i<10; i++){
      digitalWrite(i,HIGH);
    }
    for (int i=10; i<13; i++){
      digitalWrite(i,LOW);
    }
  }
  if (adjLamp > 101 && adjLamp < 153){
     for (int i=8; i<11; i++){
      digitalWrite(i,HIGH);
    }
    for (int i=11; i<13; i++){
      digitalWrite(i,LOW);
    }
  }
  if (adjLamp > 152 && adjLamp < 204){
     for (int i=8; i<12; i++){
      digitalWrite(i,HIGH);
    }
    digitalWrite(12,LOW);
  }
  if (adjLamp > 203 && adjLamp < 256){
     for (int i=8; i<13; i++){
      digitalWrite(i,HIGH);
    }
  }
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
  digitalWrite(len_Pin,HIGH); //Enable L channel
  digitalWrite(ren_Pin,HIGH); //Disable R channel
  analogWrite(rpwm_Pin,0); //R Channel Off from PWM control

  //Status of Microscope ON
  blinkLed();
}


void loop() {
  adjustLamp();
  buttonON();
  //currentRead();
  delay(200); 
}