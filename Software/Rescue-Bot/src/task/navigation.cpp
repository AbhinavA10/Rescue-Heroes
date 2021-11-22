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
            do_find_lego_man(); // verified
            break;
        case State_t::FOUND_LEGO_MAN:
            // do_pick_up_lego_man(); // 180 degree turn
            do_pick_up_lego_man_90_turn();
            break;
        case State_t::FINDING_SAFE_ZONE:
            do_finding_safe_zone_to_right();
            break;
        case State_t::FOUND_SAFE_ZONE:
            do_dropoff_lego_man_to_right();
            break;
        case State_t::RETURN_TO_START:
            do_follow_red_line(); // verified
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
        case State_t::TEST_MOVE_PID:
            do_test_move_pid();
            break;
        default:
            PRINT_DEBUG("UNKNOWN STATE!")
            break;
        };
    }

    // Follow red line
    void do_follow_red_line()
    {
        if (color_sensors[COLORSENSOR_FL].getCurrentColor() == ColorClass::RED)
        {
            MotorControl::disablePID = true;
            MotorControl::SpinLeft(); // directly turn robot without PID
        }
        else if (color_sensors[COLORSENSOR_FR].getCurrentColor() == ColorClass::RED)
        {
            MotorControl::disablePID = true;
            MotorControl::SpinRight(); // directly turn robot without PID
        }
        else
        {
            MotorControl::disablePID = false;
            MotorControl::MoveForward_PID();
        }
    }

    // Follow red line till blue
    void do_find_lego_man()
    {
        if (color_sensors[COLORSENSOR_FL].getCurrentColor() == ColorClass::BLUE || color_sensors[COLORSENSOR_FR].getCurrentColor() == ColorClass::BLUE)
        {
            state = State_t::FOUND_LEGO_MAN;
            MotorControl::StopMotors_PID();
        }
        else
        {
            do_follow_red_line();
        }
    }

    // Reached blue, pickup lego man
    void do_pick_up_lego_man()
    {
        static bool done_moving = false;
        static int required_yaw = 0;
        if (!done_moving)
        {
            required_yaw = imu.calculate_required_yaw_right_turn(180);
            // blocking section
            MotorControl::disablePID = true;
            MotorControl::MoveForward_Distance(3); // Blocking. Also calls StopMotors()
            lowerScoopServo();
            MotorControl::MoveReverse_Distance(3); // Blocking. Also calls StopMotors()
            MotorControl::disablePID = false;
            done_moving = true; // only move once, when this function is called
        }

        int yaw = imu.getNormalizedYaw();
        if (abs(yaw - required_yaw) > 3)
        {
            // spin right till our current yaw is close enough to
            MotorControl::SpinRight_PID();
            //Note: to account for sign change, only spin in one direction
        }
        else
        {
            MotorControl::StopMotors_PID();
            // state = State_t::FINDING_SAFE_ZONE;
            state = State_t::RETURN_TO_START; // TODO: remove this line
        }
    }

    // Reached blue, pickup lego man
    // by doing a 90 degree right turn, then turning till we see red on left sensor
    void do_pick_up_lego_man_90_turn()
    {
        static bool done_moving = false;
        static bool done_imu_turn = false;
        static int required_yaw = 0;
        if (!done_moving)
        {
            required_yaw = imu.calculate_required_yaw_right_turn(90);
            // blocking section
            MotorControl::disablePID = true;
            MotorControl::MoveForward_Distance(4); // Blocking. Also calls StopMotors()
            lowerScoopServo();
            MotorControl::MoveReverse_Distance(4); // Blocking. Also calls StopMotors()
            MotorControl::disablePID = false;
            done_moving = true; // only move once, when this function is called
        }

        // Turn right 90 degrees
        if (!done_imu_turn)
        {
            int yaw = imu.getNormalizedYaw();
            if (abs(yaw - required_yaw) > 3)
            {
                // spin right till our current yaw is close enough to
                MotorControl::SpinRight_PID();
                //Note: to account for sign change, only spin in one direction
            }
            else
            {
                done_imu_turn = true;
            }
        }
        else
        {
            // IMU turning done. Now turn till we see red on the left sensor.
            MotorControl::SpinRight();
            if (color_sensors[COLORSENSOR_FL].getCurrentColor() == ColorClass::RED)
            {
                MotorControl::StopMotors_PID();
                state = State_t::FINDING_SAFE_ZONE;
            }
        }
    }

    // Follow red line till green
    void do_finding_safe_zone_to_right()
    {
        if (color_sensors[COLORSENSOR_R].getCurrentColor() == ColorClass::GREEN)
        {
            // Sense only safe zone on the right!
            state = State_t::FOUND_SAFE_ZONE;
            MotorControl::StopMotors_PID();
        }
        else
        {
            do_follow_red_line();
        }
    }

    // Reached green, drop off lego man. Only on right
    void do_dropoff_lego_man_to_right()
    {
        // 'states' within this function
        static bool done_moving_fwd = false;
        static bool done_imu_turn_green = true;
        static int required_yaw = 0;
        static bool done_moving_legoman = true;
        static bool done_imu_turn_undo = true;
        static int required_yaw_undo = 0;
        static bool done_all = false;

        // Move forwards a little
        if (!done_moving_fwd)
        {
            // blocking section
            MotorControl::disablePID = true;
            MotorControl::MoveForward_Distance(6); // Blocking. Also calls StopMotors()
            required_yaw = imu.calculate_required_yaw_right_turn(90);
            MotorControl::disablePID = false;
            done_moving_fwd = true; // only move once, when this function is called
            done_imu_turn_green = false;
        }

        // Turn right towards green
        if (!done_imu_turn_green)
        {
            int yaw = imu.getNormalizedYaw();
            if (abs(yaw - required_yaw) > 3)
            {
                // spin right till our current yaw is close enough to
                MotorControl::SpinRight_PID();
                //Note: to account for sign change, only spin in one direction
            }
            else
            {
                MotorControl::StopMotors_PID();
                done_imu_turn_green = true;
                done_moving_legoman = false;
            }
        }
        // Move into greenzone, drop off, and reverse
        if (!done_moving_legoman)
        {
            // blocking section
            MotorControl::disablePID = true;
            MotorControl::MoveForward_Distance(3); // Blocking. Also calls StopMotors()
            raiseScoopServo();
            MotorControl::MoveReverse_Distance(3); // Blocking. Also calls StopMotors()
            required_yaw_undo = imu.calculate_required_yaw_left_turn(40);
            MotorControl::disablePID = false;
            done_moving_legoman = true; // only move once, when this function is called
            done_imu_turn_undo = false;
        }

        // Turn left 90 degrees to undo the original turn
        if (!done_imu_turn_undo)
        {
            int yaw = imu.getNormalizedYaw();
            if (abs(yaw - required_yaw) > 3)
            {
                // spin left till our current yaw is close enough to
                MotorControl::SpinLeft_PID();
                //Note: to account for sign change, only spin in one direction
            }
            else
            {
                done_imu_turn_undo = true;
                done_all = true;
            }
        }
        // IMU undo-turning done. Now turn till we see red on the left sensor.
        if (done_all)
        {
            MotorControl::SpinLeft();
            if (color_sensors[COLORSENSOR_FR].getCurrentColor() == ColorClass::RED)
            {
                MotorControl::StopMotors_PID();
                state = State_t::RETURN_TO_START;
            }
        }
    }

    // Milestone4: Driving till green:
    void do_test_move_till_green()
    {
        MotorControl::disablePID = true;
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
        MotorControl::disablePID = true;
        if (color_sensors[COLORSENSOR_FL].getCurrentColor() == ColorClass::BLUE || color_sensors[COLORSENSOR_FR].getCurrentColor() == ColorClass::BLUE)
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
        MotorControl::disablePID = true;

        if (!done_init)
        {
            MotorControl::MoveForward();
            delay(1000);
            MotorControl::MoveReverse();
            delay(1000);
            MotorControl::SpinLeft();
            delay(1000);
            MotorControl::SpinRight();
            delay(1000);
            MotorControl::StopMotors();
            done_init = true;
        }
    }

    void do_test_move_pid()
    {
        // Repeating target waveform:
        int t = micros() / 1e6;
        t = t % 16;
        if (t < 2)
        {
            MotorControl::MoveForward_PID();
        }
        else if (t < 4)
        {
            MotorControl::StopMotors_PID();
        }
        else if (t < 6)
        {
            MotorControl::MoveReverse_PID();
        }
        else if (t < 8)
        {
            MotorControl::StopMotors_PID();
        }
        else if (t < 10)
        {
            MotorControl::SpinLeft_PID();
        }
        else if (t < 12)
        {
            MotorControl::StopMotors_PID();
        }
        else if (t < 14)
        {
            MotorControl::SpinRight_PID();
        }
        else
        {
            MotorControl::StopMotors_PID();
        }
    }

    void do_test_move_dist()
    {
        MotorControl::disablePID = true;
        MotorControl::MoveForward_Distance(5);
        delay(1000); // pause
        MotorControl::MoveReverse_Distance(5);
        state = State_t::NONE;
    }

    void do_test_move_servo()
    {
        MotorControl::disablePID = true;
        lowerScoopServo();
        raiseScoopServo();
        lowerScoopServo();
        raiseScoopServo();
        state = State_t::NONE;
    }

    // Milestone4: IMU: Manually rotate robot, then let robot rotate back to start position
    void do_test_imu_pt1()
    {
        MotorControl::disablePID = true;
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
        imu.readData(); // Hack: force reading of IMU data
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
