#include <Arduino.h>
#include <Wire.h> // I2C
#include <SPI.h>  // Required for Color Sensor library to compile

#include "pin_assignment.h"
#include "buzzer.h"
#include "config.h"

#include "actuators/servos.h"
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
  initScoopServo();
  init_sensors();
  MotorControl::init();
  Navigation::init();
  // Test if display works
  // Display::test_display();

  // Test basic movement
  // MotorControl::test_motors();

  /*
  // Milestone4: IMU: Manually rotate robot, then let robot rotate back to start position
  delay(10000); // wait 10 seconds for IMU to stabilize
  imu.readData();
  int original_yaw = imu.getYaw(); // save original yaw.
  playStartupSound();
  delay(10000); // wait 10 seconds for robot to be moved and let DMP stabilize
  playShutdownSound();
  imu.readData();
  int yaw = imu.getYaw();
  while (abs(yaw - original_yaw) > 5)
  {
    PRINT_DEBUG("checking");
    if (yaw > original_yaw)
    {
      // turn left
      MotorControl::spin_left();
      PRINT_DEBUG("turning left");
    }
    else
    {
      // turn right
      MotorControl::spin_right();
      PRINT_DEBUG("turning right");
    }

    imu.readData();
    yaw = imu.getYaw();
  }

  playShutdownSound();
  */
}

void loop()
{

  read_sensors();
  Navigation::run();
  // MotorControl::run();
  delay(3); // integration time of color sensors
}
