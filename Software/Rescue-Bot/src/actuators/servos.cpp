#include "actuators/servos.h"

Servo scoopServo;

void initScoopServo()
{
    scoopServo.attach(SERVO_SCOOP_PIN);
}

void lowerScoopServo()
{
    scoopServo.attach(SERVO_SCOOP_PIN);
    scoopServo.write(SCOOP_CLOSED_POSITION);
}

void raiseScoopServo()
{
    scoopServo.attach(SERVO_SCOOP_PIN);
    scoopServo.write(SCOOP_OPEN_POSITION);
}