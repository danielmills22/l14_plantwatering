/*
 * Project pump
 * Description: Water Pump
 * Author:
 * Date:
 */

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