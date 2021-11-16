#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include "config.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// extern Task t_Display;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1            // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_SCREEN_ADDRESS 0x3C /// Normally 0x3D is for 128x64 but our's has this address.

// Data positions in string array
#define COLOR_SENSOR_STATUS_INDEX 0
#define IMU_SENSOR_STATUS_INDEX 1
#define YAW_INDEX 2
#define COLOR_CLASS_INDEX 3

namespace Display
{
    extern Adafruit_SSD1306 display;
    extern String text[8];

    void init_display();
    void refresh_display();
    void refresh_display_big(int val);
    void test_display();
    void testdrawchar();
    void testdrawstyles();

};

#endif