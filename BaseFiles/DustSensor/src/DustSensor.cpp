/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/18044/Documents/IoT/l14_plantwatering/BaseFiles/DustSensor/src/DustSensor.ino"
/*
 * Project DustSensor
 * Description:
 * Author:
 * Date:
 */

void setup();
void loop();
#line 8 "c:/Users/18044/Documents/IoT/l14_plantwatering/BaseFiles/DustSensor/src/DustSensor.ino"
const int DUSTSENSOR = A3;
float dustValues = 0.0;

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  Serial.begin(9600);
  pinMode(DUSTSENSOR, INPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  dustValues = analogRead(DUSTSENSOR);
  Serial.printf("Dust Values are %.03f \n", dustValues);
}