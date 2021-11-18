#include <Arduino.h>
#include <math.h>
#include "config.h"
#include "actuators/motors.h"
#include "pin_assignment.h"

Motor *Motors::left = new Motor;
Motor *Motors::right = new Motor;

// Initializes motor with pins and sets up interrupts
void Motor::init(uint8_t pwm_pin, uint8_t in_pin_1, uint8_t in_pin_2, uint8_t sensor1_pin, uint8_t sensor2_pin)
{
    pwm_pin_ = pwm_pin;
    dir_pin_1_ = in_pin_1;
    dir_pin_2_ = in_pin_2;
    enc1_pin_ = sensor1_pin;
    enc2_pin_ = sensor2_pin;
    ticks_ = 0;

    pinMode(pwm_pin_, OUTPUT);
    pinMode(dir_pin_1_, OUTPUT);
    pinMode(dir_pin_2_, OUTPUT);

    // Set Encoder pins to input
    pinMode(enc1_pin_, INPUT);
    pinMode(enc2_pin_, INPUT);

    // Attach the interrupt pin to the function whenever there is a rising edge in the signal
    if (enc1_pin_ == ENC2_A)
    {
        attachInterrupt(digitalPinToInterrupt(enc1_pin_), Motors::leftMotorInterrupt, RISING);
    }
    else if (enc1_pin_ == ENC1_A)
    {
        attachInterrupt(digitalPinToInterrupt(enc1_pin_), Motors::rightMotorInterrupt, RISING);
    }
}

// Function to convert from centimeters to encoder ticks
int Motors::cmToTicks(float cm)
{
    int result;                                         // Final calculation result
    float circumference = (WHEEL_DIAMETER * PI) / 10;   // Calculate wheel circumference in cm
    float cm_step = circumference / TICKS_PER_ROTATION; // CM per Step

    float f_result = cm / cm_step; // Calculate result as a float
    result = (int)f_result;        // Convert to an integer (note this is NOT rounded)

    return result;
}

// Reads data coming from encoder and changes encoder tick count
void Motors::leftMotorInterrupt()
{
    // Read data from other encoder pin
    left->b_temp = digitalRead(ENC2_B);
    // Depending on which way you are rotating the wheels, it increases or decreases the count
    if (left->b_temp > 0)
    {
        left->ticks_++;
    }
    else
    {
        left->ticks_--;
    }
}

void Motors::rightMotorInterrupt()
{
    // see leftMotorInterrupt() for comments
    right->b_temp = digitalRead(ENC1_B);
    if (right->b_temp > 0)
    {
        right->ticks_++;
    }
    else
    {
        right->ticks_--;
    }
}

void Motors::printTicks()
{
    Serial.print(left->ticks_);
    Serial.print(" ");
    Serial.print(right->ticks_);
    Serial.print("\r\n");
}