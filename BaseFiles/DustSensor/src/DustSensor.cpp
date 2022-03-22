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

#include "math.h"

//const int DUSTSENSOR = A2;
void setup();
void loop();
#line 11 "c:/Users/18044/Documents/IoT/l14_plantwatering/BaseFiles/DustSensor/src/DustSensor.ino"
int pin = A2;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 300;//sampe 30s ;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

void setup() 
{
    Serial.begin(9600);
    pinMode(pin,INPUT);
    starttime = millis();//get the current time;
}

void loop() 
{
    duration = pulseIn(pin, LOW);
    lowpulseoccupancy = lowpulseoccupancy+duration;

    if ((millis()-starttime) > sampletime_ms)//if the sampel time == 30s
    {
        ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
        concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
        Serial.print(lowpulseoccupancy);
        Serial.print(",");
        Serial.print(ratio);
        Serial.print(",");
        Serial.println(concentration);
        lowpulseoccupancy = 0;
        starttime = millis();
    }
}
