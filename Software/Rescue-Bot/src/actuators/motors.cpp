#include <Arduino.h>
#include <math.h>

#include "actuators/motors.h"

Motor *Motors::left = new Motor;
Motor *Motors::right = new Motor;

void Motors::leftMotorInterrupt()
{
    left->update();
}

void Motors::rightMotorInterrupt()
{
    right->update();
}

void Motors::stop()
{
    Motors::left->stop();
    Motors::right->stop();
}

// Initializes motor with pins and sets up interrupts
// Must be run before motor.setSpeed() can be used
void Motor::init(uint8_t pwm_pin, uint8_t in_pin_1, uint8_t in_pin_2, uint8_t sensor1_pin, uint8_t sensor2_pin)
{
    pwm_pin_ = pwm_pin;
    dir_pin_1_ = in_pin_1;
    dir_pin_2_ = in_pin_2;
    sensor1_pin_ = sensor1_pin;
    sensor2_pin_ = sensor2_pin;
    ticks_ = 0;

    speed = 0;
    speed_setpoint = 0;
    speed_command = 0;
    
    pinMode(pwm_pin_, OUTPUT);
    pinMode(dir_pin_1_, OUTPUT);
    pinMode(dir_pin_2_, OUTPUT);

/*
    pinMode(sensor2_pin, INPUT);
    if (sensor1_pin == LEFT_MOTOR_SENSOR_A_PIN)
    {
        attachInterrupt(digitalPinToInterrupt(sensor1_pin), Motors::leftMotorInterrupt, RISING);
    }
    else if (sensor1_pin == RIGHT_MOTOR_SENSOR_A_PIN)
    {
        attachInterrupt(digitalPinToInterrupt(sensor1_pin), Motors::rightMotorInterrupt, RISING);
    }
    */
}