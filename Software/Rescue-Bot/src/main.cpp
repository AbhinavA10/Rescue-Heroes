#include <Arduino.h>
#include <Wire.h> // I2C
#include <SPI.h>  // Required for Color Sensor library to compile

// TODO: Include task header files
// TODO: Create global sensor/actuator objects
// TODO: Create Tasks and setup TaskScheduler
// Task t_readSensors
// Task t_navigation
// Task t_motorControl

#include "pitches.h"
#include "pin_assignment.h"

void playStartupSound(){
  pinMode(BUZZER,OUTPUT);
  int dur = 1000/8;
  float dur_between = dur * 1.3;
  tone(BUZZER, NOTE_C5, dur);
  delay(dur_between);
  noTone(BUZZER);
  tone(BUZZER, NOTE_E5, dur);
  delay(dur_between);
  noTone(BUZZER);
  tone(BUZZER, NOTE_F5, dur);
  delay(dur_between);
  noTone(BUZZER);
}

void setup()
{
  playStartupSound();
  Serial.begin(115200);
}

void loop()
{
  //TODO: Run Task Scheduler
}