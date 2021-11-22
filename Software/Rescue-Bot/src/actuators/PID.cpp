#include <Arduino.h>
#include "PID.h"
// Default initialization list
SimplePID::SimplePID() : kp(1), kd(0), ki(0), umax(215), eprev(0.0), eintegral(0.0) {}

// Set the parameters
// Kp, Kd, Ki, max PID output
void SimplePID::setParams(float kpIn, float kdIn, float kiIn, float umaxIn)
{
    kp = kpIn;
    kd = kdIn;
    ki = kiIn;
    umax = umaxIn;
}

// Evaluate the signal
void SimplePID::evalu(int value, int target, float deltaT, int &pwr, int &dir)
{

    // error
    int e = target - value;

    float dedt = (e - eprev) / (deltaT);
    eintegral = eintegral + e * deltaT;
    float u = kp * e + kd * dedt + ki * eintegral;

    // motor power
    pwr = (int)fabs(u);
    if (pwr > umax)
    {
        pwr = umax;
    }

    // motor direction
    dir = 1;
    if (u < 0)
    {
        dir = -1;
    }

    // store previous error
    eprev = e;
}
