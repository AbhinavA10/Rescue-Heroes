#include "navigation.h"
#include "pin_assignment.h" // Color Sensor indicies

namespace Navigation
{

    State_t state = STARTING_STATE;
    int8_t orientation = 0;

    void init()
    {
        t_navigation.setCallback(&run);
    }

    void run()
    {
        switch (state)
        {
        case State_t::FINDING_LEGO_MAN:
            do_find_lego_man();
            break;
        case State_t::FOUND_LEGO_MAN:
            do_pick_up_lego_man();   
            break;
        case State_t::FINDING_SAFE_ZONE:
            do_finding_safe_zone();
            break;
        case State_t::FOUND_SAFE_ZONE:
            do_dropoff_lego_man();
            break;
        case State_t::RETURN_TO_START:
            do_follow_red_line();
            break;
        case State_t::TEST_MOVE:
            do_test_move();
            break;
        default:
            break;
        };
    }
    void do_follow_red_line()
    {
        //TODO
    }

    void do_find_lego_man()
    {
        do_follow_red_line();
        //TODO
    }

    void do_finding_safe_zone()
    {
        do_follow_red_line();
        //TODO
    }

    void do_pick_up_lego_man()
    {
        //TODO
    }

    void do_dropoff_lego_man()
    {
        //TODO
    }

    void do_test_move()
    {
        static bool done_init = false;

        if (!done_init)
        {
            MotorControl::set_command(Command_t::DRIVE, 120);
            MotorControl::set_command(Command_t::TURN, 90);
            MotorControl::set_command(Command_t::DRIVE, 90);
            done_init = true;
        }

        // E.g. Reading IMU Sensor data:
        int yaw = imu.getYaw();
        // E.g. Reading color sensor data:
        if (color_sensors[COLORSENSOR_FL].getCurrentColor() == ColorClass::RED || color_sensors[COLORSENSOR_FR].getCurrentColor() == ColorClass::RED)
        {
            // both front sensors see red
        }
    }
};
