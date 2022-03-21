/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/18044/Documents/IoT/l14_plantwatering/BaseFiles/PumpNoOLED/src/PumpNoOLED.ino"
/*
 * Project PumpNoOLED
 * Description:
 * Author:
 * Date:
 */

 #include "Air_Quality_Sensor.h"
void setup(void);
void loop(void);
#line 9 "c:/Users/18044/Documents/IoT/l14_plantwatering/BaseFiles/PumpNoOLED/src/PumpNoOLED.ino"
const int PUMP = D11;
const int DUSTSENSOR = A2;

AirQualitySensor sensor(A3);

void setup(void) {
  Serial.begin(9600);

  pinMode(PUMP, OUTPUT);

  Serial.println("Waiting sensor to init...");
  delay(20000);
  if (sensor.init()) {
    Serial.println("Sensor ready.");
  }
  else {
    Serial.println("Sensor ERROR!");
  }
}

void loop(void) {
  int quality = sensor.slope();
  Serial.print("Sensor value: ");
  Serial.println(sensor.getValue());
  
  if (quality == AirQualitySensor::FORCE_SIGNAL) {
    Serial.println("High pollution! Force signal active.");
  }
  else if (quality == AirQualitySensor::HIGH_POLLUTION) {
    Serial.println("High pollution!");
  }
  else if (quality == AirQualitySensor::LOW_POLLUTION) {
    Serial.println("Low pollution!");
  }
  else if (quality == AirQualitySensor::FRESH_AIR) {
    Serial.println("Fresh air.");
  }
  delay(1000);
  digitalWrite(PUMP, HIGH);
  Serial.printf("Pump is high \n");
  delay(3000);
  digitalWrite(PUMP, LOW);
  Serial.printf("Pump is high \n");
  delay(1000);
  
}
