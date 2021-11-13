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

#include "task/motor_control.h"
#include "task/display.h"
#include "task/read_sensors.h"

void setup()
{
  // playStartupSound();
  Serial.begin(115200);
  init_sensors();
  MotorControl::init_motor_control();
  // Display::init_display();
  // Test if display works
  // Display::test_display();

  // Test basic movement
  // MotorControl::test_motors();

  // Milestone4: Driving till red:
  // bool foundRed = false;
  // while (!foundRed)
  // {
  //   MotorControl::drive_fwd();
  //   foundRed = read_red(); // read color sensors
  // }

  // Milestone4: IMU: Manually rotate robot, then let robot rotate back to start position
  
  delay(10000);                         // wait 10 seconds for IMU to stabilize
  int original_yaw = imu->milestone4(); // save original yaw.
  playStartupSound();
  delay(10000); // wait 10 seconds for robot to be moved and let DMP stabilize
  playShutdownSound();
  int yaw = imu->milestone4();
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
    yaw = imu->milestone4();
  }
  
  playShutdownSound();
}

void loop()
{
  //TODO: Run Task Scheduler
  // read_sensors();
}