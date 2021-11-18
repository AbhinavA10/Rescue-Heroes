#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <Arduino.h>

#include "config.h"
#include "motor_control.h"

#include "sensors/imu.h"
#include "sensors/colorsensor.h"
#include "actuators/servos.h"

extern ColorSensor color_sensors[4];
extern IMU imu;

namespace Navigation
{
    
    enum class State_t: uint8_t {
        NONE = 0,
        FOLLOW_RED_LINE = 1,
        FOUND_BULLSEYE,
        DROP_LEGO_MAN,
        FOUND_SAFE_ZONE,
        RETURN_TO_START,
        TEST_MOVE,

        MILESTONE4_MOVE_TILL_GREEN,
        MILESTONE5_FOLLOW_RED,
        // TODO: add proper states
    };

    extern State_t state;

    void init();
    void run();

    void do_follow_red_line();
    void do_test_move();
    void do_milestone4_move_till_green();
    void do_milestone5_follow_red();
};
#endif