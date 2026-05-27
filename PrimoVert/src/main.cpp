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
#define butLight1_Pin 15 //button light ON / OFF 
#define butLight2_Pin 14 //button light ON / OFF
#define ris_Pin PC5 //read pin for current sensor R channel
#define lis_Pin A6 //read pin for current sensor L channel
#define potLine_Pin A7 //read pin for adjust light
#define len_Pin PD3 //Enable counter clockwise > Enable in HIGH
#define ren_Pin PD4 //Enable clockwise > Enable in HIGH
#define lpwm_Pin PD5 //Intensity control to L channel
#define rpwm_Pin PD6 //Intensity control to R channel
#define led0_Pin 8 //Enable Led 1 indicator from intensity of light
#define led1_Pin 12 //Enable Led 2 indicator from intensity of light
#define led2_Pin 11 //Enable Led 3 indicator from intensity of light
#define led3_Pin 10 //Enable Led 4 indicator from intensity of light
#define led4_Pin 9 //Enable Led 5 indicator from intensity of light
#define aux1_Pin 7 //Enable AUX port 8 (J15-P2)
#define aux2_Pin 13 //Enable AUX port 7 (J15-P1)

//Variables declarations:
boolean flagLight = false;
byte buttonON_1;
byte buttonON_2;
int flag = 0;

//Status of Microscope ON
void blinkLed(){
digitalWrite(led0_Pin,HIGH);
digitalWrite(led1_Pin,HIGH);
digitalWrite(led2_Pin,HIGH);
digitalWrite(led3_Pin,HIGH);
digitalWrite(led4_Pin,HIGH);
delay(3000);
digitalWrite(led0_Pin,LOW);
digitalWrite(led1_Pin,LOW);
digitalWrite(led2_Pin,LOW);
digitalWrite(led3_Pin,LOW);
digitalWrite(led4_Pin,LOW);
}

//Read buttons Auto
bool buttonON(){
  buttonON_1 = digitalRead(butLight1_Pin);
  buttonON_2 = digitalRead(butLight2_Pin); 
  if((buttonON_1 == 0) || (buttonON_2 == 0)) return true;
  else return false;
}

void setup() {

  Serial.begin(9600);
  pinMode(butLight1_Pin, INPUT_PULLUP);
  pinMode(butLight2_Pin, INPUT_PULLUP);
  pinMode(ris_Pin,INPUT);
  pinMode(lis_Pin,INPUT);
  pinMode(potLine_Pin,INPUT);
  pinMode(len_Pin,OUTPUT);
  pinMode(ren_Pin,OUTPUT);
  pinMode(lpwm_Pin,OUTPUT);
  pinMode(rpwm_Pin,OUTPUT);
  pinMode(led0_Pin,OUTPUT);
  pinMode(led1_Pin,OUTPUT);
  pinMode(led2_Pin,OUTPUT);
  pinMode(led3_Pin,OUTPUT);
  pinMode(led4_Pin,OUTPUT);
  pinMode(aux1_Pin,OUTPUT);
  pinMode(aux2_Pin,OUTPUT);

 //Status of Microscope ON
  blinkLed();
}


void loop() {

Serial.println (buttonON());



  delay(500);

}