#include "actuators/servos.h"
#include <Servo.h>
#include "pin_assignment.h"

Servo scoopServo;

void initScoopServo()
{
    pinMode(SERVO_PWM, OUTPUT);
    scoopServo.attach(SERVO_PWM);
    raiseScoopServo();
}

void raiseScoopServo()
{
    scoopServo.writeMicroseconds(SCOOP_OPEN_POSITION);
    delay(1000); // wait for servo to get there
}

void lowerScoopServo()
{
    scoopServo.writeMicroseconds(SCOOP_CLOSED_POSITION);
    delay(1000); // wait for servo to get there
}
