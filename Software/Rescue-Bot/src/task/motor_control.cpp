#include "motor_control.h"
#include "pin_assignment.h"

// this task = t_motorControl
namespace MotorControl
{

    Command current_command;

    static bool done = false;

    void init_motor_control()
    {
        // current_command.type = Command_t::NONE;

        motors.left->init(ENA_PWM, IN1, IN2, ENC2_A, ENC2_B);
        motors.right->init(ENB_PWM, IN3, IN4, ENC1_A, ENC1_B);
        // t_motorControl.setCallback(&motor_control);
    }

    void stopMotors()
    {
        current_command.type = Command_t::STOP;
        done = false;
    }

    void runMotors(int mspeed, float delayAmount)
    {
        // ****Motor Movement****
        /*
    255 is the max speed a motor can handle
    Blue motors can run at max 9V. 
    Battery pack I am using is a 8 pack AA pack, meaning it gives 12V (1.5V x 8), 
    Motor driver takes 1.4V about, meaning 10.6V is left for the motors.
    So 9/10.6 = x/255, therefore x = 215
    Therefore speeds that these blue motors can run at: Min = 140, Max = 215, (140-215)
        */
        // Run all the motors for a certain amount of time
        analogWrite(ENA_PWM, mspeed);
        analogWrite(ENB_PWM, mspeed);
        delay(delayAmount);

        // Stop when done
        analogWrite(ENA_PWM, 0);
        analogWrite(ENB_PWM, 0);
    }

    // Function to Move Forward
    void MoveForward(int mspeed, float delayAmount)
    {
        // Set Motor A forward
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);

        // Set Motor B forward
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);

        // Run the motors at the specified speed, and amount of time
        runMotors(mspeed, delayAmount);
    }
    // Function to Move Reverse
    void MoveReverse(int mspeed, float delayAmount)
    {
        // Set Motor A reverse
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);

        // Set Motor B reverse
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);

        // Run the motors at the specified speed, and amount of time
        runMotors(mspeed, delayAmount);
    }

    // Function to Spin Right
    void SpinRight(int mspeed, float delayAmount)
    {
        // Set Motor A reverse
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);

        // Set Motor B forward
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);

        // Run the motors at the specified speed, and amount of time
        runMotors(mspeed, delayAmount);
    }

    // Function to Spin Left
    void SpinLeft(int mspeed, float delayAmount)
    {
        // Set Motor A forward
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);

        // Set Motor B reverse
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);

        // Run the motors at the specified speed, and amount of time
        runMotors(mspeed, delayAmount);
    }
    void setCorrection()
    {
        //use PID for correction?
    }

    void run_drive_command()
    {
        // TODO
        motors.setSpeed(0, 0);
    }

    void run_turn_command()
    {
        //TODO
    }

    void run_stop_command()
    {
        motors.stop();
        // motors.left->resetDistance();
        // motors.right->resetDistance();
        done = true;
    }

    void run_command()
    {
        switch (current_command.type)
        {
        case Command_t::DRIVE:
            run_drive_command();
            break;
        case Command_t::TURN:
            run_turn_command();
            break;
        case Command_t::STOP:
            run_stop_command();
            break;
        default:
            break;
        };
    }
    void test_motors()
    {
        // motors.checkMotors(); // TODO integrate Motor encoders
        MoveForward(215, 1000); // Ex: Forward at 215 speed for 1000 ms
        delay(500);
        MoveReverse(215, 1000); // Ex: Forward at 215 speed for 1000 ms
        delay(500);
        SpinRight(140, 1000);
        delay(500);
        SpinLeft(200, 1000);
        delay(500);
    }

    void drive_fwd()
    {
        // milestone4
        MoveForward(190, 150); // Ex: Forward at 190 speed for 150ms
    }

    void spin_right()
    { // milestone4 imu
        SpinRight(215, 100);
    }

    void spin_left()
    { // milestone4 imu
        SpinLeft(215, 100);
    }
    void motor_control()
    {
        run_command();
        motors.left->adjustSpeed();
        motors.right->adjustSpeed();
    }

    void set_command(Command_t type, int16_t value)
    {
        done = false; // we have a new command to do
        current_command = Command{type, value};
    }

};
