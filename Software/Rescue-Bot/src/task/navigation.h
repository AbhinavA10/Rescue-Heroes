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

// State management and control flow
namespace Navigation
{

    enum class State_t : uint8_t
    {
        NONE = 0,
        FINDING_LEGO_MAN,  // follow red line till blue
        FOUND_LEGO_MAN,    // reached blue, pickup lego man
        FINDING_SAFE_ZONE, // follow red line till green
        FOUND_SAFE_ZONE,   // reached green, drop off lego man
        RETURN_TO_START,   // follow red line
        // States for testing functionality
        TEST_MOVE,
        TEST_MOVE_DIST,
        TEST_MOVE_SERVO,
        TEST_MOVE_TILL_GREEN,
        TEST_IMU_PT1,
        TEST_IMU_PT2,
        TEST_IMU_PT3,
        TEST_IMU_PT4,
        TEST_IMU_PT5,
        TEST_FOLLOW_RED,
        TEST_MOVE_PID, // the only test with PID
    };

    extern State_t state;

    void init();
    void run();

    void do_follow_red_line();
    void do_find_lego_man();
    void do_pick_up_lego_man();
    void do_pick_up_lego_man_90_turn();
    void do_finding_safe_zone_to_right();
    void do_dropoff_lego_man_to_right();
    void do_finding_safe_zone_to_left();
    void do_dropoff_lego_man_to_left();

    int calculate_required_yaw_right_turn(int right_turn_angle);
    int calculate_required_yaw_left_turn(int right_turn_angle);

    void do_test_move();
    void do_test_move_dist();
    void do_test_move_servo();
    void do_test_move_till_green();
    void do_test_follow_red();
    void do_test_imu_pt1();
    void do_test_imu_pt2();
    void do_test_imu_pt3();
    void do_test_imu_pt4();
    void do_test_imu_pt5();
    void do_test_move_pid();
};
#endif