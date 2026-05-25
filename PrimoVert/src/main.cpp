/* 
Manutenção da placa controladora do Microscópio Zeiss Primo Vert.

Responsable Research: Profa. Dra. Marilene Hohmuth Lopes - marilenehl@usp.br 
Techinical Developer: Dr. Kelliton Jose Mendonca Francisco - kelliton@usp.br

Hardware: Atmel328
IDE: Visual Studio Code version 1.96.4 and PlatformIO Core 6.1.16

Developed by the Scientific Maintenance and Instrumentation Division - BMC

*/

#include <Arduino.h>

#define butLight1_Pin PC0 //button light ON / OFF 
#define butLight2_Pin PC1 //button light ON / OFF
#define ris_Pin PC5 //read pin for current sensor R channel
#define lis_Pin A6 //read pin for current sensor L channel
#define potLine_Pin A7 //read pin for adjust light
#define len_Pin PD3 //Enable counter clockwise > Enable in HIGH
#define ren_Pin PD4 //Enable clockwise > Enable in HIGH
#define lpwm_Pin PD5 //Intensity control to L channel
#define rpwm_Pin PD6 //Intensity control to R channel
#define led1_Pin PD7 //Enable Led 1 indicator from intensity of light
#define led2_Pin PB0 //Enable Led 2 indicator from intensity of light
#define led3_Pin PB1 //Enable Led 3 indicator from intensity of light
#define led4_Pin PB2 //Enable Led 4 indicator from intensity of light
#define led5_Pin PB3 //Enable Led 5 indicator from intensity of light
#define aux_Pin PB4 //Enable AUX port (J15)


// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}