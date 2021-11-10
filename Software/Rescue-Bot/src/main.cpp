#include <Arduino.h>
#include <Wire.h> // I2C
#include <SPI.h> // Required for Color Sensor library to compile

// TODO: Include task header files
// TODO: Create global sensor/actuator objects
// TODO: Create Tasks and setup TaskScheduler
// Task t_readSensors
// Task t_navigation
// Task t_motorControl

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop()
{
  //TODO: Run Task Scheduler
}