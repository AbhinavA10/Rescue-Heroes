#include <Arduino.h>
#include <math.h>
#include "config.h"
#include "actuators/motors.h"
#include "pin_assignment.h"

Motor *Motors::left = new Motor;
Motor *Motors::right = new Motor;

// Constant for steps in disk
const float stepcount = 135; // counts per wheel rotation

// Constant for wheel diameter
const float wheeldiameter = 66.10; // Wheel diameter in millimeters, change if different

volatile int count1 = 0;
volatile int count2 = 0;

// Function to convert from centimeters to encoder_counts/steps
int CMtoSteps(float cm)
{

    int result;                                        // Final calculation result
    float circumference = (wheeldiameter * 3.14) / 10; // Calculate wheel circumference in cm
    float cm_step = circumference / stepcount;         // CM per Step

    float f_result = cm / cm_step; // Calculate result as a float
    result = (int)f_result;        // Convert to an integer (note this is NOT rounded)

    return result; // End and return result
}
// Reads data coming from encoder and changes encoder count
void Motors::leftMotorInterrupt()
{
    // Read data from other encoder pin
    int b = digitalRead(ENC1_B);
    // Depending on which way you are rotating the wheels, it increases or decreases the count
    // 135 count = 1 rotation
    if (b > 0)
    {
        count1++;
    }
    else
    {
        count1--;
    }
    // Note: don't put serial print statements in interrupts
    // left->update();
}

void Motors::rightMotorInterrupt()
{
    // Read data from other encoder pin
    int b = digitalRead(ENC2_B);
    // Depending on which way you are rotating the wheels, it increases or decreases the count
    // 135 count = 1 rotation
    if (b > 0)
    {
        count2++;
    }
    else
    {
        count2--;
    }
    // right->update();
}

void Motors::stop()
{
    Motors::left->stop();
    Motors::right->stop();
}

void Motors::checkMotors()
{
    Serial.print(count1);
    Serial.print(" ");
    Serial.print(count2);
    Serial.print("\r\n");
}

// Initializes motor with pins and sets up interrupts
// Must be run before motor.setSpeed() can be used
void Motor::init(uint8_t pwm_pin, uint8_t in_pin_1, uint8_t in_pin_2, uint8_t sensor1_pin, uint8_t sensor2_pin)
{
    pwm_pin_ = pwm_pin;
    dir_pin_1_ = in_pin_1;
    dir_pin_2_ = in_pin_2;
    enc1_pin_ = sensor1_pin;
    enc2_pin_ = sensor2_pin;
    ticks_ = 0;

    speed = 0;
    speed_setpoint = 0;
    speed_command = 0;

    pinMode(pwm_pin_, OUTPUT);
    pinMode(dir_pin_1_, OUTPUT);
    pinMode(dir_pin_2_, OUTPUT);

    // Set Encoder pins to input
    pinMode(enc1_pin_, INPUT);
    pinMode(enc2_pin_, INPUT);

    // Attach the interrupt pin to the function whenever there is a rising edge in the signal
    if (enc1_pin_ == ENC1_A)
    {
        attachInterrupt(digitalPinToInterrupt(enc1_pin_), Motors::leftMotorInterrupt, RISING);
    }
    else if (enc1_pin_ == ENC2_A)
    {
        attachInterrupt(digitalPinToInterrupt(enc2_pin_), Motors::rightMotorInterrupt, RISING);
    }
}