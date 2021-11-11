#include <Wire.h>
//#include <I2Cdev.h>

#include "read_sensors.h"

// current task = t_readSensors

void init_sensors()
{
    // Start I2C bus
    Wire.begin();
    // imu->init();
    // imu->run();
    // read_sensors();
    // The next runs of this task will use the read_sensors callback
    // t_readSensors.setCallback(&read_sensors);
    setup_colors();
}

void chooseBus(uint8_t bus)
{
    Wire.beginTransmission(0x70);
    Wire.write(1 << (bus + 2)); // will be using 2-3 instead of 0-1 SDA/SCL pins because of convience (placed better on the breadboard)
    Wire.endTransmission();
}

void setup_colors()
{
    for (int i = 0; i < numberOfSensors; i++)
    {
        Serial.println(i);
        chooseBus(i);
        if (tcs[i].begin())
        {
            Serial.print("Found sensor ");
            Serial.println(i + 1);
        }
        else
        {
            Serial.println("No Sensor Found");
            while (true)
                ;
        }
    }
    delay(2000);
    Serial.println("start");
}
void read_sensors()
{
    // if (MotorControl::current_command.type == Command_t::TURN)
    // {
    // TODO: only run if we're still turning?
    // imu->readData();
    // }
    //TODO: set bus using Mux for each color sensor
    //detectColor();
    for (int i = 0; i < numberOfSensors; i++)
    {
        chooseBus(i);
        float red, green, blue;
        tcs[i].getRGB(&red, &green, &blue);

        // Comment out this section below if wanting to use with colorviewCollectorPDE!
        Serial.print("Sensor: ");
        Serial.print(i);
        Serial.print("\t");

        Serial.print("R:\t");
        Serial.print(int(red));
        Serial.print("\tG:\t");
        Serial.print(int(green));
        Serial.print("\tB:\t");
        Serial.print(int(blue));
        Serial.print("\n");
    }
    delay(60); // takes 50ms to read

    // update encoder distance if needed
    // motors.left->readDistance();
    // motors.right->readDistance();
}