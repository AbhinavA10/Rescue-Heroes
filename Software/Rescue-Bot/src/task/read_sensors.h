#ifndef READ_SENSORS_H
#define READ_SENSORS_H

#include "task/motor_control.h"
#include "actuators/motors.h"

#include "sensors/imu.h"
#include "sensors/colorsensor.h"

#define NUM_COLOR_SENSORS 4

extern ColorSensor color_sensors[4];
extern IMU imu;
extern Motors motors;

// State management and control flow
namespace Sensors
{
    void init_sensors();
    void read_sensors();
    void setupColorSensors();
}

#endif