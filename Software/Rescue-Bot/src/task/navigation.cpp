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
        if (color_sensors[COLORSENSOR_FL].getCurrentColor() == ColorClass::NO_COLOR && color_sensors[COLORSENSOR_FR].getCurrentColor() == ColorClass::NO_COLOR)
        {
            MotorControl::drive_fwd();
        }
        else
        {
            if (color_sensors[COLORSENSOR_FL].getCurrentColor() == ColorClass::RED)
            {
                MotorControl::spin_right();
                return;
            }
            else if (color_sensors[COLORSENSOR_FR].getCurrentColor() == ColorClass::RED)
            {
                MotorControl::spin_left();
                return;
            }
            else
            {
                MotorControl::drive_fwd();
                return;
            }
        }
        return;
    }

    void do_find_lego_man()
    {
        if (color_sensors[COLORSENSOR_FL].getCurrentColor() == ColorClass::BLUE || color_sensors[COLORSENSOR_FR].getCurrentColor() == ColorClass::BLUE)
        {
            state = State_t::FOUND_LEGO_MAN;
            return;
        }
        else
        {
            do_follow_red_line();
        }
    }

    void do_finding_safe_zone()
    {
        if (color_sensors[COLORSENSOR_L].getCurrentColor() == ColorClass::GREEN || color_sensors[COLORSENSOR_R].getCurrentColor() == ColorClass::GREEN)
        {
            state = State_t::FOUND_SAFE_ZONE;
            return;
        }
        else
        {
            do_follow_red_line();
        }
    }

    void do_pick_up_lego_man()
    {
        //Drive forward measured time/ distance (PID here?)
        MotorControl::stopMotors();
        //Servo movement to pick up lego guy
        //Motors going backwards measured time/ distance (PID here?)
        int old_yaw = imu.getYaw();
        if (imu.getYaw() == old_yaw + 180)
        {
            MotorControl::drive_fwd();
            state = State_t::FINDING_SAFE_ZONE;
        }
        else
        {
            MotorControl::spin_right();
        }
    }

    void do_dropoff_lego_man()
    {
        //May need to drive forward a bit before starting
        int old_yaw = imu.getYaw();

        if (color_sensors[COLORSENSOR_L].getCurrentColor() == ColorClass::GREEN)
        {
            if (imu.getYaw() == old_yaw - 90)
            {
                //May need to drive forward a bit?
                MotorControl::stopMotors();
                //control the servo
                //If we drive forward we will need to drive backwards same amount
                if (imu.getYaw() == old_yaw)
                {
                    MotorControl::drive_fwd();
                    state = State_t::RETURN_TO_START;
                }
                else
                {
                    MotorControl::spin_right();
                }
            }
            else
            {
                MotorControl::spin_left();
            }
        }
        else
        {
            if (imu.getYaw() == old_yaw + 90)
            {
                //May need to drive forward
                MotorControl::stopMotors();
                //Control Servo
                //If we drive forward will need to drive backward same amount
                if (imu.getYaw() == old_yaw)
                {
                    MotorControl::drive_fwd();
                    state = State_t::RETURN_TO_START;
                }
                else
                {
                    MotorControl::spin_left();
                }
            }
            else
            {
                MotorControl::spin_right();
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

        // E.g. Reading IMU Sensor data:
        int yaw = imu.getYaw();
        // E.g. Reading color sensor data:
        if (color_sensors[COLORSENSOR_FL].getCurrentColor() == ColorClass::RED || color_sensors[COLORSENSOR_FR].getCurrentColor() == ColorClass::RED)
        {
            // both front sensors see red
        }
    }
};
