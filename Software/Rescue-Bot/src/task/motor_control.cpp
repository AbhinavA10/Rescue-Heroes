#include "motor_control.h"

// this task = t_motorControl
namespace MotorControl
{

    Command current_command;

    static bool done = false;

    void init_motor_control()
    {
        current_command.type = Command_t::NONE;

        motors.left->init(LEFT_MOTOR_PWM_PIN, LEFT_MOTOR_IN1_PIN, LEFT_MOTOR_IN2_PIN, LEFT_MOTOR_SENSOR_A_PIN, LEFT_MOTOR_SENSOR_B_PIN);
        motors.right->init(RIGHT_MOTOR_PWM_PIN, RIGHT_MOTOR_IN1_PIN, RIGHT_MOTOR_IN2_PIN, RIGHT_MOTOR_SENSOR_A_PIN, RIGHT_MOTOR_SENSOR_B_PIN);

        t_motorControl.setCallback(&motor_control);
    }

    void stopMotors()
    {
        current_command.type = Command_t::STOP;
        done = false;
    }

    void setCorrection()
    {
        //use PID for correction?
    }

    void run_drive_command()
    {
        // TODO
        motors.setSpeed(0,0);
    }

    void run_turn_command()
    {
        //TODO
    }

    void run_stop_command()
    {
        motors.stop();
        motors.left->resetDistance();
        motors.right->resetDistance();
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
