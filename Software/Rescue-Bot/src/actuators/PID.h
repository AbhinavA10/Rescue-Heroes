#ifndef PID_H
#define PID_H
class SimplePID
{
    // From Curio Res' tutorial
private:
    float kp, kd, ki, umax;
    float eprev, eintegral;

public:
    SimplePID();
    void setParams(float kpIn, float kdIn, float kiIn, float umaxIn);
    void evalu(int value, int target, float deltaT, int &pwr, int &dir);
};

#endif
