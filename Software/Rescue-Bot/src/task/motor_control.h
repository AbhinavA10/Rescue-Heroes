#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#define MIN_SPEED 155
#define MAX_SPEED 215

#define FWD_SPEED 170
#define TURNING_SPEED 215

#include <Arduino.h>
#include "actuators/motors.h"
#include "navigation.h"
#include "config.h"

extern Motors motors;

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

    // extern Command current_command;
    void init();

    void runMotors();
    void run_for_duration(int mspeed, float delayAmount);
    void write_speed(int left, int right);
    void MoveForward(); // public interface
    void MoveReverse(); // public interface
    void SpinRight();   // public interface
    void SpinLeft();    // public interface
    void StopMotors(); // public interface
};

#endif