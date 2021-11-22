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
    scoopServo.write(SCOOP_OPEN_POSITION_ANGLE);
    delay(1000); // wait for servo to get there
}

void lowerScoopServo()
{
    scoopServo.write(SCOOP_CLOSED_POSITION_ANGLE);
    delay(1000); // wait for servo to get there
}
