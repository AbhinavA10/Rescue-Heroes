#include <Arduino.h>
#include <Wire.h> // I2C
#include <SPI.h>  // Required for Color Sensor library to compile
#include <TaskScheduler.h>

// TODO: Include task header files
// TODO: Create global sensor/actuator objects
// TODO: Create Tasks and setup TaskScheduler
// Task t_readSensors
// Task t_navigation
// Task t_motorControl
#include "pin_assignment.h"
#include "buzzer.h"
#include "config.h"

#include "task/motor_control.h"
#include "task/display.h"
#include "task/navigation.h"
#include "task/read_sensors.h"

void sensorCallback();
void navigationCallback();
void motorCallback();

Task t_readSensors(1000, 5, &sensorCallback);
Task t_navigation(1000, 5, &navigationCallback);
Task t_motorControl(1000, 0, &motorCallback);

Scheduler runner;

void sensorCallback()
{
  //sensor task stuff
}

void navigationCallback()
{
  //Nav task stuff
}

void motorCallback()
{
  //motor task stuff
  MotorControl::test_motors();
}

void setup()
{
  // playStartupSound();
  Serial.begin(115200);
  // for testing:
  MotorControl::init_motor_control();
  // Display::test_display();
  //init_sensors();
  runner.init();

  runner.addTask(t_motorControl);
  delay(10000);
  t_motorControl.enable();
}

void loop()
{
  //TODO: Run Task Scheduler
  runner.execute();
  //read_sensors(); // read color sensors
}