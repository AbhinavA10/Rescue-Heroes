#ifndef READ_SENSORS_H
#define READ_SENSORS_H

#include <TaskSchedulerDeclarations.h>

#include "task/motor_control.h"
#include "actuators/motors.h"

#include "sensors/imu.h"
#include "sensors/colorsensor.h"

// No need to include IMU here since it is static
extern Motors motors;

extern Task t_readSensors;

void init_sensors();
void read_sensors();

#endif