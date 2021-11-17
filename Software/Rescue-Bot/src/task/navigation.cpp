#include "navigation.h"
#include "pin_assignment.h" // Color Sensor indicies

namespace Navigation
{

    State_t state = STARTING_STATE;
    int8_t orientation = 0;

    // Setup Navigation
    void init()
    {
        // The next runs of this task will use the run callback
        // t_navigation.setCallback(&run);
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
        case State_t::MILESTONE4_MOVE_TILL_RED:
            do_milestone4_move_till_red();
            break;
        default:
            break;
        };
    }
    void do_follow_red_line()
    {
        //TODO
    }

    // Milestone4: Driving till red:
    void do_milestone4_move_till_red()
    {
        static bool done_test = false;
        if (!done_test)
        {
            MotorControl::drive_fwd();
            if (color_sensors[COLORSENSOR_L].getCurrentColor() == ColorClass::GREEN || color_sensors[COLORSENSOR_R].getCurrentColor() == ColorClass::GREEN)
            {
                analogWrite(ENA_PWM, 0);
                analogWrite(ENB_PWM, 0);
                done_test = true;
            }
        }
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
    }
};
