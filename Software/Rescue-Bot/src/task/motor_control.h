#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>
#include <TaskSchedulerDeclarations.h>

#include "actuators/motors.h"

#include "navigation.h"
#include "config.h"

#define MOTOR_P_CONTSTANT 2 // TBD
#define MOTOR_I_CONTSTANT 2 // TBD
#define MOTOR_D_CONTSTANT 2 // TBD

extern Task t_motorControl;
extern Motors motors;

extern uint16_t correction;

enum class Command_t : uint8_t
{
    DRIVE,
    TURN,
    STOP,
    NONE
};
// Motor Control Mode
enum class Mode : uint8_t
{
    SPEED,
    DISTANCE,
};

//PID Controller for Motor Speed and Distance modes
namespace MotorControl
{

    struct Command
    {
        Command_t type;
        int16_t value;
        Mode mode;
    };

    extern Command current_command;

    void stopMotors();
    void runMotors();
    void test_motors();
    void drive_fwd();

    void setCorrection(int16_t);

    void init_motor_control();
    void motor_control();

    void set_command(Command_t, int16_t);
};

#endif