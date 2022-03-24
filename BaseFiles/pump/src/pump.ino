/*
 * Project pump
 * Description: Water Pump
 * Author:
 * Date:
 */

const int PUMP = A4;

void setup() {
  Serial.begin(9600);
  pinMode(PUMP, OUTPUT);
}

void loop() {
  digitalWrite(PUMP, HIGH);
  delay(1000);
  digitalWrite(PUMP, LOW);
}