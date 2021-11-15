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
#include "config.h"

#include "actuators/servos.h"
#include "task/motor_control.h"
#include "task/display.h"
#include "task/read_sensors.h"
ColorSensor color_sensors[4] = {ColorSensor(ColorSensorType::ADAFRUIT), // Front left
                                ColorSensor(ColorSensorType::ADAFRUIT), // Front Right
                                ColorSensor(ColorSensorType::EBAY),     // Left
                                ColorSensor(ColorSensorType::EBAY)};    // Right

void setup()
{
  playStartupSound();
  Serial.begin(115200);
  Display::init_display();
  init_sensors();
  initScoopServo();
  raiseScoopServo();
  MotorControl::init_motor_control();
  // Test if display works
  // Display::test_display();

  // Test basic movement
  // MotorControl::test_motors();

  // Milestone4: Driving till red:
  bool foundRed = false;
  while (!foundRed)
  {
    MotorControl::drive_fwd();
    read_sensors();
    if (color_sensors[COLORSENSOR_FL].currentColor == ColorClass::RED || color_sensors[COLORSENSOR_FR].currentColor == ColorClass::RED)
    {
      foundRed = true;
      // PRINT_DEBUG(i);
      // Serial.println("RED");
    }
  }

  // Milestone4: IMU: Manually rotate robot, then let robot rotate back to start position

  // delay(10000);                         // wait 10 seconds for IMU to stabilize
  // int original_yaw = imu->milestone4(); // save original yaw.
  // playStartupSound();
  // delay(10000); // wait 10 seconds for robot to be moved and let DMP stabilize
  // playShutdownSound();
  // int yaw = imu->milestone4();
  // while (abs(yaw - original_yaw) > 5)
  // {
  //   PRINT_DEBUG("checking");
  //   if (yaw > original_yaw)
  //   {
  //     // turn left
  //     MotorControl::spin_left();
  //     PRINT_DEBUG("turning left");
  //   }
  //   else
  //   {
  //     // turn right
  //     MotorControl::spin_right();
  //     PRINT_DEBUG("turning right");
  //   }
  //   yaw = imu->milestone4();
  // }

  playShutdownSound();
}

void loop()
{
  //TODO: Run Task Scheduler
  // read_sensors();
}