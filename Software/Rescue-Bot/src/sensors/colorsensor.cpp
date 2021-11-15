#include "colorsensor.h"
#include <Arduino.h>

ColorSensor::ColorSensor(ColorSensorType type) : type_(type)
{
    sensor_ = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
    switch (type)
    {
    case ColorSensorType::ADAFRUIT:
        RED_AVG[0] = COLOR_RED_R_ADAFRUIT;
        RED_AVG[1] = COLOR_RED_G_ADAFRUIT;
        RED_AVG[2] = COLOR_RED_B_ADAFRUIT;
        RED_MAX_DIST = COLOR_RED_MAX_DISTANCE_ADAFRUIT;
        GREEN_AVG[0] = COLOR_GREEN_R_ADAFRUIT;
        GREEN_AVG[1] = COLOR_GREEN_G_ADAFRUIT;
        GREEN_AVG[2] = COLOR_GREEN_B_ADAFRUIT;
        GREEN_MAX_DIST = COLOR_GREEN_MAX_DISTANCE_ADAFRUIT;
        BLUE_AVG[0] = COLOR_BLUE_R_ADAFRUIT;
        BLUE_AVG[1] = COLOR_BLUE_G_ADAFRUIT;
        BLUE_AVG[2] = COLOR_BLUE_B_ADAFRUIT;
        BLUE_MAX_DIST = COLOR_BLUE_MAX_DISTANCE_ADAFRUIT;
        break;
    case ColorSensorType::EBAY:
        RED_AVG[0] = COLOR_RED_R_EBAY;
        RED_AVG[1] = COLOR_RED_G_EBAY;
        RED_AVG[2] = COLOR_RED_B_EBAY;
        RED_MAX_DIST = COLOR_RED_MAX_DISTANCE_EBAY;
        GREEN_AVG[0] = COLOR_GREEN_R_EBAY;
        GREEN_AVG[1] = COLOR_GREEN_G_EBAY;
        GREEN_AVG[2] = COLOR_GREEN_B_EBAY;
        GREEN_MAX_DIST = COLOR_GREEN_MAX_DISTANCE_EBAY;
        BLUE_AVG[0] = COLOR_BLUE_R_EBAY;
        BLUE_AVG[1] = COLOR_BLUE_G_EBAY;
        BLUE_AVG[2] = COLOR_BLUE_B_EBAY;
        BLUE_MAX_DIST = COLOR_BLUE_MAX_DISTANCE_EBAY;
        break;
    default:
        break;
    }
}

bool ColorSensor::init()
{
    return sensor_.begin();
}

void ColorSensor::run() {}

// Read new value from color sensor.
void ColorSensor::readColor()
{
    sensor_.getRGB(&red_, &green_, &blue_);
    // Serial.print("R:\t");
    // Serial.print(int(red_));
    // Serial.print("\tG:\t");
    // Serial.print(int(green_));
    // Serial.print("\tB:\t");
    // Serial.print(int(blue_));
    // Serial.print("\n");
    classifyColor();
}
// Classify latest sensor reading and store result
void ColorSensor::classifyColor()
{
    // Compute Euclidean distance of current reading to each color group average
    float RedDist = sqrt(pow(red_ - RED_AVG[0], 2) + pow(green_ - RED_AVG[1], 2) + pow(blue_ - RED_AVG[2], 2));
    float GreenDist = sqrt(pow(red_ - GREEN_AVG[0], 2) + pow(green_ - GREEN_AVG[1], 2) + pow(blue_ - GREEN_AVG[2], 2));
    float BlueDist = sqrt(pow(red_ - BLUE_AVG[0], 2) + pow(green_ - BLUE_AVG[1], 2) + pow(blue_ - BLUE_AVG[2], 2));

    // Compare Euclidean distance to max threshold of each color group
    if (RedDist < RED_MAX_DIST)
    {
        currentColor = ColorClass::RED;
    }
    else if (GreenDist < GREEN_MAX_DIST)
    {
        currentColor = ColorClass::GREEN;
    }
    else if (BlueDist < BLUE_MAX_DIST)
    {
        currentColor = ColorClass::BLUE;
    }
    else
    {
        currentColor = ColorClass::NO_COLOR;
    }
}