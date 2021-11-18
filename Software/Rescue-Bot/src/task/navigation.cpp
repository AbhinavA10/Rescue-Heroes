#include "navigation.h"
#include "pin_assignment.h" // Color Sensor indicies

namespace Navigation
{

    State_t state = STARTING_STATE;

    // Setup Navigation
    void init()
    {
        // put any navigation setup here
    }

    // Runs everytime the navigation task is run.
    void run()
    {
        switch (state)
        {
        case State_t::FOLLOW_RED_LINE:
            do_follow_red_line();
            break;
        case State_t::TEST_MOVE:
            do_test_move();
            break;
        case State_t::MILESTONE4_MOVE_TILL_GREEN:
            do_milestone4_move_till_green();
            break;
        case State_t::MILESTONE5_FOLLOW_RED:
            do_milestone5_follow_red();
            break;
        case State_t::TEST_MOVE_DIST:
            do_test_move_dist();
            break;
        default:
            PRINT_DEBUG("UNKNOWN STATE!")
            break;
        };
    }
    void do_follow_red_line()
    {
        //TODO
    }

    // Milestone4: Driving till green:
    void do_milestone4_move_till_green()
    {
        static bool done_test = false;
        if (!done_test)
        {
            MotorControl::MoveForward();
            if (color_sensors[COLORSENSOR_L].getCurrentColor() == ColorClass::GREEN || color_sensors[COLORSENSOR_R].getCurrentColor() == ColorClass::GREEN)
            {
                MotorControl::StopMotors();
                done_test = true;
            }
        }
    }

    // Milestone5: Follow red line till blue
    void do_milestone5_follow_red()
    {
        if (color_sensors[COLORSENSOR_FL].getCurrentColor() == ColorClass::BLUE || color_sensors[COLORSENSOR_FL].getCurrentColor() == ColorClass::BLUE)
        {
            MotorControl::StopMotors();
        }
        else if (color_sensors[COLORSENSOR_FL].getCurrentColor() == ColorClass::RED)
        {
            MotorControl::SpinLeft();
            Serial.println("Left");
        }
        else if (color_sensors[COLORSENSOR_FR].getCurrentColor() == ColorClass::RED)
        {
            MotorControl::SpinRight();
            Serial.println("Right");
        }
        else
        {
            MotorControl::MoveForward();
        }
    }

    void do_test_move()
    {
        static bool done_init = false;

        if (!done_init)
        {
            done_init = true;
        }
    }
    void do_test_move_dist()
    {
        static bool done_test_move_dist = false;

        if (!done_test_move_dist)
        {
            MotorControl::MoveForward_Distance(20);
            delay(1000);
            // MotorControl::MoveReverse_Distance(10);
            done_test_move_dist = true;
        }
    }
};
