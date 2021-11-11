#include <Arduino.h>
#include <Wire.h> // I2C
#include <SPI.h>  // Required for Color Sensor library to compile

// TODO: Include task header files
// TODO: Create global sensor/actuator objects
// TODO: Create Tasks and setup TaskScheduler
// Task t_readSensors
// Task t_navigation
// Task t_motorControl

#include "task/motor_control.h"

#include "pin_assignment.h"
#include "buzzer.h"

void setup()
{
  playStartupSound();
  Serial.begin(115200);
  MotorControl::init_motor_control(); // for testing
}

void loop()
{
  //TODO: Run Task Scheduler
}