#include "actuators/servos.h"
#include <Servo.h>
#include "pin_assignment.h"

Servo scoopServo;

void initScoopServo()
{
    scoopServo.attach(SERVO_PWM);
    raiseScoopServo();
}

void lowerScoopServo()
{
    scoopServo.writeMicroseconds(SCOOP_CLOSED_POSITION);
    delay(1000); // wait for servo to get there
}

void raiseScoopServo()
{
    scoopServo.writeMicroseconds(SCOOP_OPEN_POSITION);
    delay(1000); // wait for servo to get there
}