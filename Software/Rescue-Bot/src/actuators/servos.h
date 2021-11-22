#ifndef SERVOS_H
#define SERVOS_H
#include <Arduino.h>

#define SCOOP_CLOSED_POSITION_ANGLE 110 // degrees
#define SCOOP_OPEN_POSITION_ANGLE 137   // degrees
#define NANO_ADDR 8

void initScoopServo();  // public
void raiseScoopServo(); // public
void lowerScoopServo(); // public

void sendServoAngle(byte angle); // private

#endif
