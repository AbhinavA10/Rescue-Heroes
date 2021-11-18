#include "motor_control.h"
#include "pin_assignment.h"

namespace MotorControl
{

    static bool done = false;

    void init()
    {
        // current_command.type = Command_t::NONE;
        motors.left->init(ENA_PWM, IN1, IN2, ENC2_A, ENC2_B);
        motors.right->init(ENB_PWM, IN3, IN4, ENC1_A, ENC1_B);
    }

    void StopMotors()
    {
        write_speed(0, 0);
    }

    void run_for_duration(int mspeed, float delayAmount)
    {
        /*
    255 is the max speed a motor can handle
    Blue motors can run at max 9V. 
    Battery pack I am using is a 8 pack AA pack, meaning it gives 12V (1.5V x 8), 
    Motor driver takes 1.4V about, meaning 10.6V is left for the motors.
    So 9/10.6 = x/255, therefore x = 215
    Therefore speeds that these blue motors can run at: Min = 140, Max = 215, (140-215)
        */
        // Run all the motors for a certain amount of time
        write_speed(mspeed, mspeed);
        delay(delayAmount);

        // Stop when done
        write_speed(0, 0);
    }

    // Set Motor speed
    // parameters: left_speed, right_speed
    void write_speed(int left, int right)
    {
        analogWrite(ENA_PWM, left);
        analogWrite(ENB_PWM, right);
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
    // Function to Move Reverse
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
        // e.g.: run_for_duration(FWD_SPEED, delayAmount);
    }

    // Function to Spin Right
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

    // Function to Spin Left
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

};
