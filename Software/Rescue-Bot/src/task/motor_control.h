#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#define MIN_SPEED 155 // PWM
#define MAX_SPEED 215 // PWM

#define FWD_SPEED 180
#define TURNING_SPEED 215

#define SPEED_M_S 15 // speed in m/s
// motors will actually take robot slower than this, but with the PID parameters,
// this value works well and follows red line
#define MAX_SPEED_M_S 30 // max found empirically accounting for robot weight

#include <Arduino.h>
#include "actuators/motors.h"
#include "navigation.h"
#include "config.h"
#include "actuators/PID.h"

extern Motors motors;

// Controller for Motor Speed and Distance modes
namespace MotorControl
{

    void init();
    void run();

    void reset_ticks();                                               // private
    void write_left_speed(int left);                                  // private
    void write_right_speed(int right);                                // private
    void write_speed(int left, int right);                            // private
    void move_till_dist(float cm);                                    // private
    void setMotorPID(int dir, int pwmVal, int pwm, int in1, int in2); // private

    void MoveForward();                  // public interface
    void MoveForward_Distance(float cm); // public interface
    void MoveReverse();                  // public interface
    void MoveReverse_Distance(float cm); // public interface
    void SpinRight();                    // public interface
    void SpinRight_Timed(int amt);       // public interface
    void SpinLeft();                     // public interface
    void SpinLeft_Timed(int amt);        // public interface
    void StopMotors();                   // public interface

    extern long prev_time;
    extern bool disablePID;
    void setMotor(int dir, int pwmVal, int pwm, int in1, int in2);

    extern SimplePID pid[2];  // Independant PIDs for each motor
    extern float vt[2];       // target velocity
    void MoveForward_PID();   // public interface
    void MoveReverse_PID();   // public interface
    void SpinLeft_PID();      // public interface
    void SpinRight_PID();     // public interface
    void StopMotors_PID();    // public interface
    void update_motors_pid(); // public interface
};

#endif