#define ENCA D5
#define ENCB D4

#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
}

void loop() {
  int a = digitalRead(ENCA);
  int b = digitalRead(ENCB);
  Serial.print(a*5);
  Serial.print(" ");
  Serial.print(b*5);
  Serial.println();
}
