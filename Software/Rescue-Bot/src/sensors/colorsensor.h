//Class wrapper for the Adafruit TCS34725 color sensor

#ifndef _COLORSENSOR_H_
#define _COLORSENSOR_H_

#include <Arduino.h>
#include "config.h"

// Define the experimental constants for the color sensor
//TODO: populate real values
#define COLOR_RED_R_ADAFRUIT                        200
#define COLOR_RED_G_ADAFRUIT                        45
#define COLOR_RED_B_ADAFRUIT                        40
#define COLOR_RED_MIN_DISTANCE_ADAFRUIT             12

#define COLOR_GREEN_R_ADAFRUIT                      60
#define COLOR_GREEN_G_ADAFRUIT                      100
#define COLOR_GREEN_B_ADAFRUIT                      110
#define COLOR_GREEN_MIN_DISTANCE_ADAFRUIT           12

#define COLOR_BLUE_R_ADAFRUIT                      110
#define COLOR_BLUE_G_ADAFRUIT                      105
#define COLOR_BLUE_B_ADAFRUIT                      50
#define COLOR_BLUE_MIN_DISTANCE_ADAFRUIT           12

#define COLOR_RED_R_EBAY                            200
#define COLOR_RED_G_EBAY                            45
#define COLOR_RED_B_EBAY                            40
#define COLOR_RED_MIN_DISTANCE_EBAY                 12

#define COLOR_GREEN_R_EBAY                          60
#define COLOR_GREEN_G_EBAY                          100
#define COLOR_GREEN_B_EBAY                          110
#define COLOR_GREEN_MIN_DISTANCE_EBAY               12

#define COLOR_BLUE_R_EBAY                          110
#define COLOR_BLUE_G_EBAY                          105
#define COLOR_BLUE_B_EBAY                          50
#define COLOR_BLUE_MIN_DISTANCE_EBAY               12

class ColorSensor{
    public:
        ColorSensor();
        void init();
        void run();

        void readColor();
        void classifyColor();
    private:
        // Adafruit library object
        uint8_t sensorType; // Ebay or Adafruit
};

#endif