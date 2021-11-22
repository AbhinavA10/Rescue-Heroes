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
            do_finding_safe_zone();
            break;
        case State_t::FOUND_SAFE_ZONE:
            do_dropoff_lego_man();
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
            MotorControl::SpinLeft();
        }
        else if (color_sensors[COLORSENSOR_FR].getCurrentColor() == ColorClass::RED)
        {
            MotorControl::SpinRight();
        }
        else
        {
            MotorControl::MoveForward();
        }
    }

    // Follow red line till blue
    void do_find_lego_man()
    {
        if (color_sensors[COLORSENSOR_FL].getCurrentColor() == ColorClass::BLUE || color_sensors[COLORSENSOR_FR].getCurrentColor() == ColorClass::BLUE)
        {
            state = State_t::FOUND_LEGO_MAN;
            MotorControl::StopMotors();
        }
        else
        {
            do_follow_red_line();
        }
    }

    // Calculate required yaw if making a right turn.
    // Assumes you're only turning right!
    int calculate_required_yaw_right_turn(int right_turn_angle)
    {
        int old_yaw = imu.getNormalizedYaw();
        int required_yaw = old_yaw + right_turn_angle;
        // Calculate required yaw.
        if (required_yaw > 360)
        {
            // old_yaw is in range (360-right_turn_angle) -> 360.
            // Adding +right_turn_angle will overflow into "negative yaw"
            // adding right_turn_angle needs to become value closer to 0 instead
            required_yaw = required_yaw - 360;
        }
        return required_yaw;
    }

    // Calculate required yaw if making a left turn.
    // Assumes you're only turning left!
    int calculate_required_yaw_left_turn(int left_turn_angle)
    {
        int old_yaw = imu.getNormalizedYaw();
        int required_yaw = old_yaw - left_turn_angle;
        // Calculate required yaw.
        if (required_yaw < 0)
        {
            // old_yaw is in range 0 -> left_turn_angle.
            // Subtracting -left_turn_angle will overflow into near 360 deg
            // Subtracting left_turn_angle needs to become value closer to 360 instead
            required_yaw = required_yaw + 360;
        }
        return required_yaw;
    }

    // Reached blue, pickup lego man
    void do_pick_up_lego_man()
    {
        static bool done_moving = false;
        static int required_yaw = 0;
        if (!done_moving)
        {
            required_yaw = calculate_required_yaw_right_turn(180);
            // blocking section
            MotorControl::MoveForward_Distance(3); // Blocking. Also calls StopMotors()
            lowerScoopServo();
            MotorControl::MoveReverse_Distance(3); // Blocking. Also calls StopMotors()
            done_moving = true;                    // only move once, when this function is called
        }

        int yaw = imu.getNormalizedYaw();
        if (abs(yaw - required_yaw) > 3)
        {
            // spin right till our current yaw is close enough to
            MotorControl::SpinRight();
            //Note: to account for sign change, only spin in one direction
        }
        else
        {
            MotorControl::StopMotors();
            // state = State_t::FINDING_SAFE_ZONE;
            state = State_t::RETURN_TO_START; // For now, focus on returning to start with lego man.
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
            required_yaw = calculate_required_yaw_right_turn(90);
            // blocking section
            MotorControl::MoveForward_Distance(3); // Blocking. Also calls StopMotors()
            lowerScoopServo();
            MotorControl::MoveReverse_Distance(3); // Blocking. Also calls StopMotors()
            done_moving = true;                    // only move once, when this function is called
        }

        // Turn right 90 degrees
        if (!done_imu_turn)
        {
            int yaw = imu.getNormalizedYaw();
            if (abs(yaw - required_yaw) > 3)
            {
                // spin right till our current yaw is close enough to
                MotorControl::SpinRight();
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
                MotorControl::StopMotors();
                // state = State_t::FINDING_SAFE_ZONE;
                state = State_t::RETURN_TO_START; // For now, focus on returning to start with lego man.
            }
        }
    }

    // Follow red line till green
    void do_finding_safe_zone()
    {
        if (color_sensors[COLORSENSOR_L].getCurrentColor() == ColorClass::GREEN || color_sensors[COLORSENSOR_R].getCurrentColor() == ColorClass::GREEN)
        {
            state = State_t::FOUND_SAFE_ZONE;
            MotorControl::StopMotors();
        }
        else
        {
            do_follow_red_line();
        }
    }

    // Reached green, drop off lego man
    void do_dropoff_lego_man()
    {
        //TODO: read through and test. IMU stuff might need to change
        //May need to drive forward a bit before starting
        static int old_yaw = imu.getYaw();

        if (color_sensors[COLORSENSOR_L].getCurrentColor() == ColorClass::GREEN)
        {
            if (imu.getYaw() == old_yaw - 90)
            {
                //May need to drive forward a bit?
                MotorControl::StopMotors();
                raiseScoopServo();
                //If we drive forward we will need to drive backwards same amount
                if (imu.getYaw() == old_yaw)
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
            if (imu.getYaw() == old_yaw + 90)
            {
                //May need to drive forward
                MotorControl::StopMotors();
                raiseScoopServo();
                //If we drive forward will need to drive backward same amount
                if (imu.getYaw() == old_yaw)
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
            MotorControl::forward_pid();
        }
        else if (t < 4)
        {
            MotorControl::stop_pid();
        }
        else if (t < 6)
        {
            MotorControl::backward_pid();
        }
        else if (t < 8)
        {
            MotorControl::stop_pid();
        }
        else if (t < 10)
        {
            MotorControl::left_pid();
        }
        else if (t < 12)
        {
            MotorControl::stop_pid();
        }
        else if (t < 14)
        {
            MotorControl::right_pid();
        }
        else
        {
            MotorControl::stop_pid();
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
