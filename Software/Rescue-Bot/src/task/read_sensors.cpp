#include <Wire.h>
//#include <I2Cdev.h>

#include "read_sensors.h"

// current task = t_readSensors

void init_sensors()
{
    // Start I2C bus
    Wire.begin();
    imu->init();
    imu->run();
    read_sensors();
    // The next runs of this task will use the read_sensors callback
    t_readSensors.setCallback(&read_sensors);
}

void read_sensors()
{
    if (MotorControl::current_command.type == Command_t::TURN)
    {
        // TODO: only run if we're still turning?
        imu->readData();
    }
    //TODO: set bus using Mux for each color sensor
    //detectColor();

    // update encoder distance if needed
    motors.left->readDistance();
    motors.right->readDistance();
}