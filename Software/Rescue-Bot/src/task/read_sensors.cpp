#include <Wire.h>
#include "config.h"

#include "read_sensors.h"

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
    PRINT_DEBUG("start");
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
#define NO_COLOR 0
#define RED 1
#define GREEN 2
#define BLUE 3

int findColor(float R_New, float G_New, float B_New)
{
    float RedDist = sqrt(pow(R_New - COLOR_RED_R_ADAFRUIT, 2) + pow(G_New - COLOR_RED_G_ADAFRUIT, 2) + pow(B_New - COLOR_RED_B_ADAFRUIT, 2));
    float GreenDist = sqrt(pow(R_New - COLOR_GREEN_R_ADAFRUIT, 2) + pow(G_New - COLOR_GREEN_G_ADAFRUIT, 2) + pow(B_New - COLOR_GREEN_B_ADAFRUIT, 2));
    float BlueDist = sqrt(pow(R_New - COLOR_BLUE_R_ADAFRUIT, 2) + pow(G_New - COLOR_BLUE_G_ADAFRUIT, 2) + pow(B_New - COLOR_BLUE_B_ADAFRUIT, 2));
    if (RedDist < COLOR_RED_MAX_DISTANCE_ADAFRUIT)
    {
        return RED;
    }
    else if (GreenDist < COLOR_GREEN_MAX_DISTANCE_ADAFRUIT)
    {
        return GREEN;
    }
    else if (BlueDist < COLOR_BLUE_MAX_DISTANCE_ADAFRUIT)
    {
        return BLUE;
    }
    else
    {
        return NO_COLOR;
    }
}

bool read_red()
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

        if (findColor(red, green, blue) == RED)
        {
            return true;
        }
        else
        {
            continue;
        }
    }
    delay(50); // takes 50ms to read
    return false;

    // update encoder distance if needed
    // motors.left->readDistance();
    // motors.right->readDistance();
}