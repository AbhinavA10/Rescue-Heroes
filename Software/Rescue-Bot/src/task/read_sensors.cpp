#include <Wire.h>
#include "config.h"

#include "read_sensors.h"
#include "task/display.h"

// current task = t_readSensors

void init_sensors()
{
    // Start I2C bus
    Wire.begin();
#ifdef USE_IMU
    imu->init();
    imu->run();
#endif
    // read_sensors();
    // The next runs of this task will use the read_sensors callback
    // t_readSensors.setCallback(&read_sensors);
    setupColorSensors();
    Display::refresh_display(); // TODO: move to its own task
}

// set mux bus
void chooseBus(uint8_t bus)
{
    Wire.beginTransmission(0x70);
    Wire.write(1 << (bus + 2)); // will be using Mux busses 2,3,4,5.
    Wire.endTransmission();
}

// Initialize color sensors
void setupColorSensors()
{
    bool found[NUM_COLOR_SENSORS] = {false, false, false, false};
    for (int i = 0; i < NUM_COLOR_SENSORS; i++)
    {
        chooseBus(i);
        if (color_sensors[i].init())
        {
            Serial.print("Found sensor ");
            Serial.println(i + 1);
            found[i] = true;
        }
        else
        {
            Serial.println("No Sensor Found");
        }
    }
    Display::text[COLOR_SENSOR_STATUS_INDEX] = "ColorSensors ";
    for (int i = 0; i < NUM_COLOR_SENSORS; i++)
    {
        Display::text[COLOR_SENSOR_STATUS_INDEX] += String(i);
        Display::text[COLOR_SENSOR_STATUS_INDEX] += (found[i]) ? F("Y") : F("N");
    }
}

void read_sensors()
{
    // if (MotorControl::current_command.type == Command_t::TURN)
    // {
    // TODO: only run if we're still turning?
    // imu->readData();
    // }
    for (int i = 0; i < NUM_COLOR_SENSORS; i++)
    {
        chooseBus(i);
        // Serial.print("Sensor: ");
        // Serial.print(i);
        color_sensors[i].readColor();
    }
    delay(60); // takes 50ms to read + some margin

    // update encoder distance if needed
    // motors.left->readDistance();
    // motors.right->readDistance();
}