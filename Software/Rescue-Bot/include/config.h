#ifndef CONFIG_H
#define CONFIG_H

/*
    Flags
*/
#define USE_LOGGING
#define USE_IMU
#define USE_COLOR_SENSORS

/*
    Configuration Values
*/
#define STARTING_STATE State_t::FOLLOW_RED_LINE

/*
    Macros
*/
#define PRINT_DEBUG(x) Serial.print(millis()); Serial.print(" "); Serial.print(__FILE__); Serial.print(":"); Serial.print(__LINE__); Serial.print(":"); Serial.println(x);
// Note: MPU6050 libs use DEBUG_PRINT, so might need to overwrite that if there are issues to debug.


#endif // CONFIG_H