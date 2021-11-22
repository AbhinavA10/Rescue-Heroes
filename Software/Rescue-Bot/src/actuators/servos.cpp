#include "actuators/servos.h"
#include "pin_assignment.h"
#include <Wire.h>

// Servo position is set through dedicated servo driver (Arduino nano)
// Dedicated servo driver enables jitter-free PWM
// Arduino nano is an I2C receiver on I2C Addr NANO_ADDR

void initScoopServo()
{
    raiseScoopServo();
}

// Raise servo
void raiseScoopServo()
{
    byte servo_angle = SCOOP_OPEN_POSITION_ANGLE;
    sendServoAngle(servo_angle);
    delay(1000); // wait servo to get there
}

// Lower servo
void lowerScoopServo()
{
    byte servo_angle = SCOOP_CLOSED_POSITION_ANGLE;
    sendServoAngle(servo_angle);
    delay(1000); // wait for servo to get there
}

// Send required servo angle to Servo driver
void sendServoAngle(byte angle)
{
    Wire.beginTransmission(NANO_ADDR); // transmit to device #4
    Wire.write(angle);                 // sends one byte
    Wire.endTransmission();            // stop transmitting
}
