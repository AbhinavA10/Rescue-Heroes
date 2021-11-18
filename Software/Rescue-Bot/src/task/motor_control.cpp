#include "motor_control.h"
#include "pin_assignment.h"
#include "actuators/servos.h"

namespace MotorControl
{

    static bool done = false;

    void init()
    {
        motors.left->init(ENA_PWM, IN1, IN2, ENC2_A, ENC2_B);
        motors.right->init(ENB_PWM, IN3, IN4, ENC1_A, ENC1_B);
        initScoopServo();
    }

    //Resets both tick counters to 0.
    void reset_ticks()
    {
        motors.left->ticks_ = 0;
        motors.right->ticks_ = 0;
    }

    // Set left motor speed
    void write_left_speed(int left)
    {
        /*
        255 is the max speed a motor can normally handle
        Blue motors can run at max 9V. Battery pack we're 8xAA ==> gives 12V (1.5V x 8), 
        L298N Motor driver takes 1.4V about, meaning 10.6V is left for the motors.
        So 9/10.6 = x/255 ==> x = 215 = max speed of blue motors
        */
        left = constrain(left, 0, MAX_SPEED);
        analogWrite(ENA_PWM, left);
    }

    // Set right motor speed
    void write_right_speed(int right)
    {
        right = constrain(right, 0, MAX_SPEED);
        analogWrite(ENB_PWM, right);
    }

    // Set Motor speed
    // parameters: left_speed, right_speed
    void write_speed(int left, int right)
    {
        write_left_speed(left);
        write_right_speed(right);
    }

    // Runs the motors for specified distance
    // Note: is blocking
    void move_till_dist(float cm)
    {
        int ticks_setpoint = Motors::cmToTicks(cm);
        reset_ticks(); // Reset all tick counters
        // move forward till one of motors reach setpoint
        while (ticks_setpoint > abs(motors.left->ticks_) && ticks_setpoint > abs(motors.right->ticks_))
        {
            if (ticks_setpoint > abs(motors.left->ticks_))
            {
                write_left_speed(FWD_SPEED);
            }
            else
            {
                write_left_speed(0);
            }
            if (ticks_setpoint > abs(motors.right->ticks_))
            {
                write_right_speed(FWD_SPEED);
            }
            else
            {
                write_right_speed(0);
            }
            // Motors::printTicks(); // debugging
        }
        // PRINT_DEBUG(ticks_setpoint)
        // Motors::printTicks();
        StopMotors();  // Stop when done
        reset_ticks(); // Reset all tick counters
    }

    // Function to Move Forward
    void MoveForward()
    {
        // Set Motor A forward
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        // Set Motor B forward
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);

        write_speed(FWD_SPEED, FWD_SPEED);
    }

    void MoveForward_Distance(float cm)
    {
        MoveForward();
        move_till_dist(cm);
    }

    // Move backwards
    void MoveReverse()
    {
        // Set Motor A reverse
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        // Set Motor B reverse
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);

        write_speed(FWD_SPEED, FWD_SPEED);
        // Run the motors at the specified speed, and amount of time
        // e.g.: run_motors_for_duration(FWD_SPEED, delayAmount);
    }

    void MoveReverse_Distance(float cm)
    {
        MoveReverse();
        move_till_dist(cm);
    }

    // Spin Right
    void SpinRight()
    {
        // Set Motor A reverse
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        // Set Motor B forward
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);

        write_speed(TURNING_SPEED, TURNING_SPEED);
    }

    // Spin Right for a fixed amount of time in ms.
    // Note: is blocking.
    void SpinRight_Timed(int amt)
    {
        SpinRight();
        delay(amt);   // Run motors for a set time
        StopMotors(); // stop when done
    }

    // Spin Left
    void SpinLeft()
    {
        // Set Motor A forward
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        // Set Motor B reverse
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);

        write_speed(TURNING_SPEED, TURNING_SPEED);
    }

    // Spin Left for a fixed amount of time in ms.
    // Note: is blocking.
    void SpinLeft_Timed(int amt)
    {
        SpinLeft();
        delay(amt);   // Run motors for a set time
        StopMotors(); // stop when done
    }

    // Stop both motors
    void StopMotors()
    {
        write_speed(0, 0);
    }

    void run()
    {
        // Motors::printTicks();
    }
};
