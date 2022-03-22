/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/18044/Documents/IoT/l14_plantwatering/l14_plantwatering_Final/src/l14_plantwatering_Final.ino"
/*
 * Project l14_plantwatering_Final
 * Description: Smart plant watering
 * Author: Daniel Mills
 * Date:03-22-2022
 */

///////////////////////////////
//-----Include and Objects Block
#include "credential.h"                    //creddential for ada fruit dashboard
#include "math.h"
#include <Adafruit_GFX.h>                   //library for graphics
#include <Adafruit_SSD1306.h>               //library for OLED
#include <Adafruit_BME280.h>                //Library for temp
#include <Adafruit_MQTT.h>                  //Library for publishing to Adafruit
#include "Adafruit_MQTT/Adafruit_MQTT.h"
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h"
#include "Air_Quality_Sensor.h"            //Library for Air Quality


//Define OLED
void setup();
void loop();
void MQTT_connect();
void showDisplayValues();
#line 22 "c:/Users/18044/Documents/IoT/l14_plantwatering/l14_plantwatering_Final/src/l14_plantwatering_Final.ino"
#define OLED_RESET D4
Adafruit_SSD1306 display(OLED_RESET);
String DateTime, TimeOnly;

//BME
#define BME_ADDRESS 0x76 //BME Address
Adafruit_BME280 bme; 
float temp;
float press;
float rHumidity;

//Connecting to Adafruit Webservice
/************ Global State (you don't need to change this!) ***   ***************/ 
TCPClient TheClient; 

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details. 
Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY); 

/****************************** Feeds ***************************************/ 
// Setup Feeds to publish or subscribe 
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname> 
Adafruit_MQTT_Publish mqtttemp = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temp");
Adafruit_MQTT_Publish mqttpress = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/press");
Adafruit_MQTT_Publish mqttrHumidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/rHumidity");
Adafruit_MQTT_Publish mqttmoisture = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/moisture");
Adafruit_MQTT_Publish mqttAQ = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/AirQuality");
Adafruit_MQTT_Publish mqttdust = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/dust");
//Adafruit_MQTT_Subscribe mqttSubPumpButton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/pumpButton"); Updated Name
Adafruit_MQTT_Subscribe mqttObj2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/FeedNameB");  

//Set Sensor Pins
const int PUMP = D11;
const int DUSTSENSOR = A2;
const int MOISTURESENSOR = A1;
AirQualitySensor sensor(A3);

bool status;      //sets for sd card

/************Declare Variables*************/
unsigned long last, lastTime;
float value2;  //MQTT Button
int moistureValues;

//DUST SENSOR Variables
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000;//sampe 30s ;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;


/////////////////////////
//-------------Setup Loop
void setup() {
  Serial.begin(9600);  //Starts the Serial monitor
  bme.begin(0x76);
  //*Setup for OLED
  Time.zone(-7);  //Sets the mountain time zone
  Particle.syncTime();  //syncs particle time
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.display(); //show splashscreen (To make sure that the OLED is working)
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.display();
  delay(2000);

  //*Setup for Dust Sensor
  pinMode(DUSTSENSOR,INPUT);
  pinMode(MOISTURESENSOR, INPUT);
  pinMode(PUMP, OUTPUT);

  //Connect to WiFi without going to Particle Cloud
  WiFi.connect();               //connect to wifi
  while(WiFi.connecting()) {    //for connecting to another broker
    Serial.printf(".");
  }

  //mqtt.subscribe(&mqttSubPumpButton);  //subscribe to pump button from Adafruit
  starttime = millis();
}

//////////////////////////////
//--------Start of Main Loop
void loop() { 
  //*Loop for OLED
  DateTime = Time.timeStr(); // Current Date and Time from Particle Time class
  TimeOnly = DateTime.substring(11 ,19) ; // Extract the Time from the DateTime String
  delay(2000); 
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.display();
  delay(2000);
  display.clearDisplay();

  //=====Main Functions=======
  //*MQTT Start
  MQTT_connect();
  // Ping MQTT Broker every 2 minutes to keep connection alive
  if ((millis()-last)>120000) {               //function to ping the broker
      Serial.printf("Pinging MQTT \n");             
      if(! mqtt.ping()) {
        Serial.printf("Disconnecting \n");
        mqtt.disconnect();
      }
      last = millis();
  }

  //*Air Quality
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

  //*Moisture
  moistureValues = analogRead(MOISTURESENSOR);
  Serial.printf("Moisture Values %i", moistureValues);
  delay(2000);

  //*MQTT Subscription
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(100))) {   //looks for receiving signal
     if (subscription == &mqttObj2) {
        value2 = atof((char *)mqttObj2.lastread);  //takes last data and converts it char and converts it to a float
        Serial.printf("Received %0.2f from Adafruit.io feed FeedNameB \n",value2);   //prints to screen
     }
  }

  //*Pump
  if (moistureValues < 2300 || value2 == 1){
    digitalWrite(PUMP, HIGH);
    Serial.printf("Pump is high \n");
    delay(500);
    digitalWrite(PUMP, LOW);
    Serial.printf("Pump is high \n");
    delay(500);
  }

  //*BME
  temp = bme.readTemperature();
  press = bme.readPressure();
  rHumidity = bme.readHumidity();

  //*Dust
  duration = pulseIn(DUSTSENSOR, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;
  if ((millis()-starttime) > sampletime_ms)//if the sampel time == 30s
  {
    ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
    Serial.println(concentration);
    lowpulseoccupancy = 0;
    starttime = millis();
  }
  showDisplayValues(); //prints values to OLED
  
  if((millis()-lastTime > 1000)) {
   if(mqtt.Update()) {
    mqtttemp.publish(temp);
    Serial.printf("Publishing Temp %0.2f \n", temp);
    mqttpress.publish(press); 
    Serial.printf("Publishing Pressure %0.2f \n", press);
    mqttrHumidity.publish(rHumidity); 
    Serial.printf("Publishing RH %0.2f \n", rHumidity);
    mqttmoisture.publish(moistureValues); 
    Serial.printf("Publishing Moisture %i \n", moistureValues);
    mqttAQ.publish(sensor.getValue()); 
    Serial.printf("Publishing AQ %i \n", sensor.getValue());
    mqttdust.publish(concentration); 
    Serial.printf("Publishing Dust Values %0.2f \n", concentration);
   } 
   lastTime = millis();
  }
}

//}

////////////////////////////////
//-----------------Void Function
// Function to connect and reconnect as necessary to the MQTT server.
void MQTT_connect() {  //this function is important to include
  int8_t ret;
  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.printf("%s\n",(char *)mqtt.connectErrorString(ret));
       Serial.printf("Retrying MQTT connection in 5 seconds..\n");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
  }
  Serial.printf("MQTT Connected!\n");   //output for if connection was successful
}

void showDisplayValues(){
  display.setCursor(0,0);
  display.clearDisplay();
  display.printf("Temp %0.1f\n", temp);
  display.printf("Pressure %0.1f\n", press);
  display.printf("Humidity  %0.1f\n", rHumidity);
  display.printf("AQ: %i \n", sensor.getValue());
  display.printf("Moisture: %i \n", moistureValues);
  display.printf("Dust: %0.2f \n", concentration);
  display.display();
}
