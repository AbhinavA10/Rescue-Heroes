//Class wrapper for the Adafruit TCS34725 color sensor

#ifndef _COLORSENSOR_H_
#define _COLORSENSOR_H_

#include <Arduino.h>
#include "config.h"

// Define the experimental constants for the color sensor
#define COLOR_RED_R_ADAFRUIT                        164.6f
#define COLOR_RED_G_ADAFRUIT                        44.3
#define COLOR_RED_B_ADAFRUIT                        41.8
#define COLOR_RED_MAX_DISTANCE_ADAFRUIT             9.1

#define COLOR_GREEN_R_ADAFRUIT                      69.22
#define COLOR_GREEN_G_ADAFRUIT                      107.36
#define COLOR_GREEN_B_ADAFRUIT                      50.75
#define COLOR_GREEN_MAX_DISTANCE_ADAFRUIT           14.1

#define COLOR_BLUE_R_ADAFRUIT                      29.11
#define COLOR_BLUE_G_ADAFRUIT                      80.89
#define COLOR_BLUE_B_ADAFRUIT                      132.33
#define COLOR_BLUE_MAX_DISTANCE_ADAFRUIT           12.1

#define COLOR_RED_R_EBAY                            197.57
#define COLOR_RED_G_EBAY                            42.86
#define COLOR_RED_B_EBAY                            40.43
#define COLOR_RED_MAX_DISTANCE_EBAY                 10.7

#define COLOR_GREEN_R_EBAY                          106.41
#define COLOR_GREEN_G_EBAY                          106.35
#define COLOR_GREEN_B_EBAY                          50.35
#define COLOR_GREEN_MAX_DISTANCE_EBAY               21.4

#define COLOR_BLUE_R_EBAY                          63.14
#define COLOR_BLUE_G_EBAY                          98.29
#define COLOR_BLUE_B_EBAY                          109
#define COLOR_BLUE_MAX_DISTANCE_EBAY               7.8

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