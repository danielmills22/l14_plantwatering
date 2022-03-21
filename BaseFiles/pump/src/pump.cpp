/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/18044/Documents/IoT/l14_plantwatering/BaseFiles/pump/src/pump.ino"
/*
 * Project pump
 * Description: Water Pump
 * Author:
 * Date:
 */

void setup();
void loop();
#line 8 "c:/Users/18044/Documents/IoT/l14_plantwatering/BaseFiles/pump/src/pump.ino"
const int PUMP = D12;

void setup() {
  Serial.begin(9600);
  pinMode(PUMP, OUTPUT);
}

void loop() {
  digitalWrite(PUMP, HIGH);
  delay(3000);
  digitalWrite(PUMP, LOW);
}