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

    // Set Motor speed
    // parameters: left_speed, right_speed
    void write_speed(int left, int right)
    {
        /*
        255 is the max speed a motor can normally handle
        Blue motors can run at max 9V. Battery pack we're 8xAA ==> gives 12V (1.5V x 8), 
        L298N Motor driver takes 1.4V about, meaning 10.6V is left for the motors.
        So 9/10.6 = x/255 ==> x = 215 = max speed of blue motors
        */
        left = constrain(left, 0, MAX_SPEED);
        right = constrain(right, 0, MAX_SPEED);
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
