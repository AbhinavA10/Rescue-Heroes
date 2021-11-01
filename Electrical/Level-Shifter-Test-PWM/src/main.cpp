#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(D12,OUTPUT);
  // D12 is pin 12. PA_6 is D12, but shows value as pin 6...
  pinMode(D10,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(D10,255/5); // 20% duty cycle

  // mimic a servo.
  digitalWrite(D12,HIGH);
  delayMicroseconds(1500);
  digitalWrite(D12,LOW);
  delayMicroseconds(20000-1500);
}