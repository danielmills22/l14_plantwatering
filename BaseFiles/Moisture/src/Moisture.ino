/*
 * Project Moisture
 * Description:
 * Author:
 * Date:
 */

SYSTEM_MODE(SEMI_AUTOMATIC);

const int MOISTURESENSOR = A1;
int moistureValues;

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  pinMode(MOISTURESENSOR, INPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  moistureValues = analogRead(MOISTURESENSOR);
  Serial.printf("Moisture Values %i", moistureValues);
  delay(2000);
}
