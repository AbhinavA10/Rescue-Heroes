#ifndef CONFIG_H
#define CONFIG_H

/*
    Flags
*/
#define USE_LOGGING
#define USE_IMU
#define USE_COLOR_SENSORS
#define USE_OLED_DISPLAY

/*
    Configuration Values
*/
#define STARTING_STATE State_t::FOLLOW_RED_LINE

/*
    Macros
*/
#define DEBUG_PRINT(x) Serial.print(millis()); Serial.print(" "); Serial.print(__FILE__); Serial.print(":"); Serial.print(__LINE__); Serial.print(" - "); Serial.println(x);

#endif // CONFIG_H