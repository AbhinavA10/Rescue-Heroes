#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#define MIN_SPEED 155
#define MAX_SPEED 215

#define FWD_SPEED 160
#define TURNING_SPEED 215

#include <Arduino.h>
#include "actuators/motors.h"
#include "navigation.h"
#include "config.h"

extern Motors motors;

// Controller for Motor Speed and Distance modes
namespace MotorControl
{

    void init();
    void run();

    void reset_ticks();                    // private
    void write_left_speed(int left);       // private
    void write_right_speed(int right);     // private
    void write_speed(int left, int right); // private
    void move_till_dist(float cm);         // private

    void MoveForward();                  // public interface
    void MoveForward_Distance(float cm); // public interface
    void MoveReverse();                  // public interface
    void MoveReverse_Distance(float cm); // public interface
    void SpinRight();                    // public interface
    void SpinRight_Timed(int amt);       // public interface
    void SpinLeft();                     // public interface
    void SpinLeft_Timed(int amt);        // public interface
    void StopMotors();                   // public interface
};

#endif