#ifndef READ_SENSORS_H
#define READ_SENSORS_H

#include "TaskSchedulerDeclarations.h"

#include "task/motor_control.h"
#include "actuators/motors.h"

#include "sensors/imu.h"
#include "sensors/colorsensor.h"

#define NUM_COLOR_SENSORS 4

extern ColorSensor color_sensors[4];
extern IMU imu;
extern Motors motors;

extern Task t_readSensors;

void init_sensors();
void read_sensors();
void setupColorSensors();
bool read_red();

#endif