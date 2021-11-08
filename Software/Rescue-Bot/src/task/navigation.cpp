#include "navigation.h"

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
        case State_t::FOLLOW_RED_LINE:
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
