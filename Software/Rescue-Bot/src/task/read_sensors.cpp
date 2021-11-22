#include <Wire.h>
#include "config.h"

#include "read_sensors.h"
#include "task/display.h"
namespace Sensors
{
    static bool all_sensors_init = true;
    // Setup sensors
    void init_sensors()
    {
        setupColorSensors();
        Display::refresh_display();
#ifdef USE_IMU
        imu.init();
        imu.init_hardware();
#endif
        if (all_sensors_init)
        {
            PRINT_DEBUG("Found all Sensors")
        }
        else
        {
            PRINT_DEBUG("Missing some Sensors!!")
        }
        Display::refresh_display();
        read_sensors(); // get initial sensor values
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
                all_sensors_init = false;
            }
        }
        Display::text[COLOR_SENSOR_STATUS_INDEX] = "ColorSensors ";
        for (int i = 0; i < NUM_COLOR_SENSORS; i++)
        {
            Display::text[COLOR_SENSOR_STATUS_INDEX] += String(i);
            Display::text[COLOR_SENSOR_STATUS_INDEX] += (found[i]) ? F("Y") : F("N");
        }
    }

    // Main method for reading sensors
    void read_sensors()
    {
        for (int i = 0; i < NUM_COLOR_SENSORS; i++)
        {
            chooseBus(i);
            // Serial.print("Sensor: ");
            // Serial.print(i);
            color_sensors[i].readColor();
        }
        if (Navigation::state == Navigation::State_t::TEST_IMU_PT1 ||
            Navigation::state == Navigation::State_t::TEST_IMU_PT2 ||
            Navigation::state == Navigation::State_t::TEST_IMU_PT3 ||
            Navigation::state == Navigation::State_t::TEST_IMU_PT4 ||
            Navigation::state == Navigation::State_t::TEST_IMU_PT5 ||
            Navigation::state == Navigation::State_t::FOUND_LEGO_MAN ||
            Navigation::state == Navigation::State_t::FOUND_SAFE_ZONE)
        {
            // only read from IMU when needed
            imu.readData();
        }
    }
}