#ifndef READ_SENSORS_H
#define READ_SENSORS_H

#include <TaskSchedulerDeclarations.h>

#include "task/motor_control.h"
#include "actuators/motors.h"

#include "sensors/imu.h"
#include "sensors/colorsensor.h"
#include "Adafruit_TCS34725.h"

#define numberOfSensors 4 // Put the number of color sensors you have here!

static Adafruit_TCS34725 tcs[] = {Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X)};


// No need to include IMU here since it is static
extern Motors motors;

extern Task t_readSensors;

void init_sensors();
void read_sensors();
void setup_colors();
bool read_red();

#endif