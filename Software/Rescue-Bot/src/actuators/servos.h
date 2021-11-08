#ifndef SERVOS_H
#define SERVOS_H

#include <Arduino.h>
#include <Servo.h>

#define SERVO_SCOOP_PIN 1

#define SCOOP_CLOSED_POSITION 60 // TBD
#define SCOOP_OPEN_POSITION 180  // TBD

void initScoopServo();
void lowerScoopServo();
void raiseScoopServo();

#endif
