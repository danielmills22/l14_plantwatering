/*
 * Project SoilOLED
 * Description:
 * Author:
 * Date:
 */

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
//SYSTEM_MODE(SEMI_AUTOMATIC);

#define OLED_RESET D4
Adafruit_SSD1306 display(OLED_RESET);

String DateTime, TimeOnly;
//const int soilMonitor = A4;

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
  //pinMode(soilMonitor, INPUT);

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
 Serial.printf(" Date and time is %s\n", DateTime.c_str());
 Serial.printf(" Time is %s\n", TimeOnly.c_str());
 //Serial.printf("Soil Monitor Output: %i",soilMonitor);

 delay(2000); 

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Daniel Mills \n");
  display.println("The Date is: %i \n",DateTime.c_str());
  display.println("The time is: %i \n",TimeOnly.c_str());
  //display.println(soilMonitor);
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.display();
  delay(2000);
  display.clear();
}