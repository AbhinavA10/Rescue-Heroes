#include <Arduino.h>
#include <Wire.h> // I2C
#include <SPI.h>  // Required for Color Sensor library to compile

// TODO: Include task header files
// TODO: Create global sensor/actuator objects
// TODO: Create Tasks and setup TaskScheduler
// Task t_readSensors
// Task t_navigation
// Task t_motorControl
#include "pin_assignment.h"
#include "buzzer.h"

#include "task/motor_control.h"
#include "task/display.h"
#include "task/read_sensors.h"


void setup()
{
  playStartupSound();
  Serial.begin(115200);
  init_sensors();
  // Test if display works
  // Display::test_display();

  MotorControl::init_motor_control();
  // test basic movement
  // MotorControl::test_motors();  

  // Driving till red:
  bool foundRed=false;
  while(!foundRed){
    MotorControl::drive_fwd();
    foundRed = read_red(); // read color sensors
  }

  
  playShutdownSound();
}

void loop()
{
  //TODO: Run Task Scheduler
  // read_sensors(); // read color sensors
}