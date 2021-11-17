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
        case State_t::MILESTONE5_FOLLOW_RED:
            do_milestone5_follow_red();
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

    // Milestone5: Follow red line:
    void do_milestone5_follow_red()
    {
        if (color_sensors[COLORSENSOR_FL].getCurrentColor() == ColorClass::RED)
        {
            // turn left
            analogWrite(ENA_PWM, 215);
            analogWrite(ENB_PWM, 215);
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, HIGH);
            Serial.println("Left");
        }
        else if (color_sensors[COLORSENSOR_FR].getCurrentColor() == ColorClass::RED)
        {
            // turn right
            analogWrite(ENA_PWM, 215);
            analogWrite(ENB_PWM, 215);
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
            Serial.println("Right");
        }
        else
        {
            MotorControl::drive_fwd();
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
