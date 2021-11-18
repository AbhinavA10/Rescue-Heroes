#include <Arduino.h>
#include <Wire.h> // I2C
#include <SPI.h>  // Required for Color Sensor library to compile

#include "pin_assignment.h"
#include "buzzer.h"
#include "config.h"

#include "task/motor_control.h"
#include "task/display.h"
#include "task/read_sensors.h"
#include "task/navigation.h"
ColorSensor color_sensors[4] = {ColorSensor(ColorSensorType::ADAFRUIT), // Front left
                                ColorSensor(ColorSensorType::ADAFRUIT), // Front Right
                                ColorSensor(ColorSensorType::EBAY),     // Left
                                ColorSensor(ColorSensorType::EBAY)};    // Right
IMU imu = IMU();

// Each "Task" is a non-blocking grouping of functionality
// Each functionality's init() is called, then its main function called sequentially, directly
// which gives the same behaviour

void setup()
{
  playStartupSound();
  Serial.begin(115200);
  Display::init_display();
  Sensors::init_sensors();
  MotorControl::init();
  Navigation::init();
  // Test if display works
  // Display::test_display();
}

void loop()
{
  Sensors::read_sensors();
  Navigation::run();
  // MotorControl::run();
  delay(3); // integration time of color sensors
  //TODO: see if delay can be removed, using logic analyzer
}
