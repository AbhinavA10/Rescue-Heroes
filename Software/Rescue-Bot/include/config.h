#ifndef CONFIG_H
#define CONFIG_H

/*
    Flags
*/
#define USE_LOGGING
#define USE_IMU

/*
    Configuration Values
*/
#define STARTING_STATE State_t::TEST_MOVE_PID

/*
    Macros
*/
#define PRINT_DEBUG(x) Serial.print(millis()); Serial.print(" "); Serial.print(__FILE__); Serial.print(":"); Serial.print(__LINE__); Serial.print(":"); Serial.println(x);
// Note: MPU6050 libs use DEBUG_PRINT


#endif // CONFIG_H