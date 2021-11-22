#ifndef SERVOS_H
#define SERVOS_H

#define SCOOP_CLOSED_POSITION 1250 // us
#define SCOOP_OPEN_POSITION 1600  // us
// Lego man slips out at 1300. 1200 hits floor

void initScoopServo();
void raiseScoopServo();
void lowerScoopServo();

#endif
