/*
 * Project Plant_Watering_System_Test_File
 * Description: Basic Code for Smart Plant water
 * Author:Daniel
 * Date:21-Mar-2022
 */

//Included Header Files
#include <Adafruit_GFX.h>                      //library for graphics
#include <Adafruit_SSD1306.h>                  //library for OLED
#include <Adafruit_BME280.h>                   //Library for temp
#include <Adafruit_MQTT.h>                     //library for MQTT
#include "Adafruit_MQTT/Adafruit_MQTT.h"       //Library for publishing to Adafruit
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h" //Library for MQTT Adafruit
#include "Grove_Air_quality_Sensor.h"          //library for air quality sensor
#include "credentials.h"                       //creddential for ada fruit dashboard

//Set Variables

//Declaring OLED Object
#define OLED_RESET D4
Adafruit_SSD1306 display(OLED_RESET);

//Declaring Pins
String DateTime, TimeOnly;
const int soilMonitor = A1;


int soilValues;

// setup() runs once, when the device is first turned on.
void setup() {
  Serial.begin(9600);
  Time.zone(-7);
  Particle.syncTime();
  
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  display.display(); // show splashscreen
  delay(2000);
  display.clearDisplay();
  pinMode(soilMonitor, INPUT);

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.printf("Daniel Mills \n");
  display.printf(DateTime.c_str());
  display.printf(TimeOnly.c_str());
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.display();
  delay(2000); 
}

// loop() runs over and over again, as quickly as it can execute.
void loop() { 
  DateTime = Time.timeStr(); // Current Date and Time from Particle Time class
  TimeOnly = DateTime.substring(11 ,19) ; // Extract the Time from the DateTime String

 //%s prints an array of char
 // the . c_str () method converts a String to an array of char
 Serial.printf( DateTime.c_str());
 Serial.printf( TimeOnly.c_str());

 delay(2000); 

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.printf("Daniel Mills \n");
  display.printf(DateTime.c_str());
  display.printf(TimeOnly.c_str());
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.display();
  delay(2000);
  display.clearDisplay();
}