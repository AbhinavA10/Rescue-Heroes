#ifndef SERVOS_H
#define SERVOS_H

#define SCOOP_CLOSED_POSITION 900 // us
#define SCOOP_OPEN_POSITION 2140  // us

void initScoopServo();
void lowerScoopServo();
void raiseScoopServo();

#endif
