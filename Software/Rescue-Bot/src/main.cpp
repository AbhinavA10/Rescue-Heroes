#include <Arduino.h>
#include <Wire.h> // I2C
#include <SPI.h>  // Required for Color Sensor library to compile

// Library's TaskScheduler.h was renamed to be a .cpp
#include "TaskSchedulerDeclarations.h"

Scheduler runner; // constructor calls runner.init()

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

// (Task interval, num iterations, callback, scheduler reference, enabled?)
// TaskInterval in milliseconds
// ColorSensors Minimum read time: Integration time
Task t_readSensors(3UL, TASK_FOREVER, &init_sensors, &runner, true);
// Task t_navigation(20UL, TASK_FOREVER, &Navigation::init, &runner, true);
Task t_motorControl(15UL, TASK_FOREVER, &MotorControl::init_motor_control, &runner, true);
// Through the above constructor and parameters, the tasks are created and scheduled & enabled to run
// at the next runner.execute();
// We are using this approach:
// https://github.com/arkhipenko/TaskScheduler/wiki/Full-Document#3-multiple-possible-callbacks-for-task
// The task will initialize during first execution pass and switch to "regular" callback  execution starting with second pass.
// There is a delay between first and second passes of the task (scheduling period, if defined).
bool foundRed = false;
void setup()
{
  playStartupSound();
  Serial.begin(115200);
  Display::init_display(); // Note: not making Display into a task until needed.
  initScoopServo();
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
  runner.startNow(); // Use when there is long running functions in setup()
  // Sets ALL active tasks in the execution chain to start execution immediately.
  // Should be placed at the end of setup() method to prevent task execution race
  // due to long running setup tasks (hardware initialization, etc.)
  // following task activation
}

void loop()
{
  runner.execute();
  // Milestone4: Driving till red:
  if (!foundRed)
  {
    MotorControl::drive_fwd();
    if (color_sensors[COLORSENSOR_FL].getCurrentColor() == ColorClass::RED || color_sensors[COLORSENSOR_FR].getCurrentColor() == ColorClass::RED)
    {
      analogWrite(ENA_PWM, 0);
      analogWrite(ENB_PWM, 0);
      foundRed = true;
      exit(0);
    }
  }
}
