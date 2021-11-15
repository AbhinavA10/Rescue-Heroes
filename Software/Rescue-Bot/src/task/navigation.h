#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <Arduino.h>
#include <TaskSchedulerDeclarations.h>

#include "config.h"
#include "motor_control.h"

#include "sensors/imu.h"
#include "sensors/colorsensor.h"
#include "actuators/servos.h"

extern ColorSensor color_sensors[4];
extern IMU imu;

extern Task t_navigation;

namespace Navigation
{
    extern int8_t orientation;
    
    enum class State_t: uint8_t {
        NONE = 0,
        FINDING_LEGO_MAN = 1,
        FOUND_LEGO_MAN,
        FINDING_SAFE_ZONE,
        FOUND_SAFE_ZONE,
        RETURN_TO_START,
        TEST_MOVE,
        // TODO: add proper states
    };

    extern State_t state;

    void init();
    void run();

    void do_follow_red_line();
    void do_find_lego_man();
    void do_finding_safe_zone();
    void do_pick_up_lego_man();  
    void do_dropoff_lego_man();
    void do_test_move();
};
#endif