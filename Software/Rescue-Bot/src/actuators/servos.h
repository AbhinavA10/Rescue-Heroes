#ifndef SERVOS_H
#define SERVOS_H

#define SCOOP_CLOSED_POSITION_ANGLE 110 // degrees
#define SCOOP_OPEN_POSITION_ANGLE 145   // degrees

void initScoopServo();
void raiseScoopServo();
void lowerScoopServo();

#endif
