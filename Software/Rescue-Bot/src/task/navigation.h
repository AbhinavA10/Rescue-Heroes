#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <Arduino.h>
#include <TaskSchedulerDeclarations.h>

#include "config.h"

#include "motor_control.h"

#include "sensors/colorsensor.h"

#include "actuators/servos.h"

#include "motor_control.h"

extern ColorSensor colorsensor;

extern Task t_navigation;

namespace Navigation
{
    extern int8_t orientation;
    
    enum class State_t: uint8_t {
        NONE = 0,
        FOLLOW_RED_LINE = 1,
        FOUND_BULLSEYE,
        DROP_LEGO_MAN,
        FOUND_SAFE_ZONE,
        RETURN_TO_START,
        TEST_MOVE,
        // TODO: add proper states
    };

    extern State_t state;

    void init();
    void run();

    void do_follow_red_line();
    void do_test_move();
};
#endif