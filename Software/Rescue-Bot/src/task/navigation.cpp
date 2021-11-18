#include "navigation.h"
#include "pin_assignment.h" // Color Sensor indicies
#include "pitches.h"

namespace Navigation
{

    State_t state = STARTING_STATE;
    int original_yaw = 0;

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
        case State_t::NONE:
            // do nothing
            break;
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
        // states for testing functionality
        case State_t::TEST_MOVE:
            do_test_move();
            break;
        case State_t::TEST_MOVE_DIST:
            do_test_move_dist();
            break;
        case State_t::TEST_MOVE_TILL_GREEN:
            do_test_move_till_green();
            break;
        case State_t::TEST_IMU_PT1:
            do_test_imu_pt1();
            break;
        case State_t::TEST_IMU_PT2:
            do_test_imu_pt2();
            break;
        case State_t::TEST_IMU_PT3:
            do_test_imu_pt3();
            break;
        case State_t::TEST_IMU_PT4:
            do_test_imu_pt4();
            break;
        case State_t::TEST_IMU_PT5:
            do_test_imu_pt5();
            break;
        case State_t::TEST_FOLLOW_RED:
            do_test_follow_red();
            break;
        case State_t::TEST_MOVE_SERVO:
            do_test_move_servo();
            break;
        default:
            PRINT_DEBUG("UNKNOWN STATE!")
            break;
        };
    }

    void do_follow_red_line()
    {
        if (color_sensors[COLORSENSOR_FL].getCurrentColor() == ColorClass::NO_COLOR && color_sensors[COLORSENSOR_FR].getCurrentColor() == ColorClass::NO_COLOR)
        {
            MotorControl::MoveForward();
            return;
        }
        else
        {
            if (color_sensors[COLORSENSOR_FL].getCurrentColor() == ColorClass::RED)
            {
                MotorControl::SpinRight();
                return;
            }
            else if (color_sensors[COLORSENSOR_FR].getCurrentColor() == ColorClass::RED)
            {
                MotorControl::SpinLeft();
                return;
            }
            else
            {
                MotorControl::MoveForward();
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
        MotorControl::StopMotors();
        lowerScoopServo();
        //Motors going backwards measured time/ distance (PID here?)
        static int old_yaw = imu.getYaw();
        if (imu.getYaw() == old_yaw + 180)
        {
            MotorControl::MoveForward();
            state = State_t::FINDING_SAFE_ZONE;
        }
        else
        {
            MotorControl::SpinRight();
        }
    }

    void do_dropoff_lego_man()
    {
        //May need to drive forward a bit before starting
        static int curr_yaw = imu.getYaw();

        if (color_sensors[COLORSENSOR_L].getCurrentColor() == ColorClass::GREEN)
        {
            if (imu.getYaw() == curr_yaw - 90)
            {
                //May need to drive forward a bit?
                MotorControl::StopMotors();
                raiseScoopServo();
                //If we drive forward we will need to drive backwards same amount
                if (imu.getYaw() == curr_yaw)
                {
                    MotorControl::MoveForward();
                    state = State_t::RETURN_TO_START;
                }
                else
                {
                    MotorControl::SpinRight();
                }
            }
            else
            {
                MotorControl::SpinLeft();
            }
        }
        else
        {
            if (imu.getYaw() == curr_yaw + 90)
            {
                //May need to drive forward
                MotorControl::StopMotors();
                raiseScoopServo();
                //If we drive forward will need to drive backward same amount
                if (imu.getYaw() == curr_yaw)
                {
                    MotorControl::MoveForward();
                    state = State_t::RETURN_TO_START;
                }
                else
                {
                    MotorControl::SpinLeft();
                }
            }
            else
            {
                MotorControl::SpinRight();
            }
        }
    }

    // Milestone4: Driving till green:
    void do_test_move_till_green()
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
    void do_test_follow_red()
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
            MotorControl::MoveForward();
            delay(500);
            MotorControl::MoveReverse();
            delay(500);
            MotorControl::SpinLeft();
            delay(500);
            MotorControl::SpinRight();
            delay(500);
            MotorControl::StopMotors();
            done_init = true;
        }
    }

    void do_test_move_dist()
    {
        MotorControl::MoveForward_Distance(5);
        delay(1000); // pause
        MotorControl::MoveReverse_Distance(5);
        state = State_t::NONE;
    }

    void do_test_move_servo()
    {
        lowerScoopServo();
        raiseScoopServo();
        lowerScoopServo();
        raiseScoopServo();
        state = State_t::NONE;
    }

    // Milestone4: IMU: Manually rotate robot, then let robot rotate back to start position
    void do_test_imu_pt1()
    {
        delay(1000); // wait 10 seconds for IMU to stabilize
        state = State_t::TEST_IMU_PT2;
    }
    void do_test_imu_pt2()
    {
        // save original yaw.
        original_yaw = imu.getYaw();
        // beep
        pinMode(BUZZER, OUTPUT);
        tone(BUZZER, NOTE_F5, 250);
        delay(1000 / 8 * 1.3);
        noTone(BUZZER);

        state = State_t::TEST_IMU_PT3;
    }
    void do_test_imu_pt3()
    {
        PRINT_DEBUG(original_yaw)
        delay(10000); // wait 10 seconds for robot to be moved and let DMP stabilize
        // beep
        PRINT_DEBUG(imu.getYaw())
        pinMode(BUZZER, OUTPUT);
        tone(BUZZER, NOTE_F4, 1000 / 8);
        delay(1000 / 8 * 1.3);
        noTone(BUZZER);
        state = State_t::TEST_IMU_PT4;
    }
    void do_test_imu_pt4()
    {
        int yaw = imu.getYaw();
        if (abs(yaw - original_yaw) > 5)
        {
            if (yaw > original_yaw)
            {
                // turn left
                MotorControl::SpinLeft();
                PRINT_DEBUG("turning left");
            }
            else
            {
                // turn right
                MotorControl::SpinRight();
                PRINT_DEBUG("turning right");
            }
        }
        else
        {
            MotorControl::StopMotors();
            state = State_t::TEST_IMU_PT5;
        }
    }
    void do_test_imu_pt5()
    {
        int dur = 1000 / 8;
        float dur_between = dur * 1.3;
        tone(BUZZER, NOTE_F4, dur);
        delay(dur_between);
        noTone(BUZZER);
        tone(BUZZER, NOTE_E4, dur);
        delay(dur_between);
        noTone(BUZZER);
        tone(BUZZER, NOTE_C4, dur);
        delay(dur_between);
        noTone(BUZZER);
        state = State_t::NONE;
    }
};
