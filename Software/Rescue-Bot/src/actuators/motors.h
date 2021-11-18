#ifndef MOTORS_H
#define MOTORS_H

#define TICKS_PER_ROTATION 135 // counts per wheel rotation
#define WHEEL_DIAMETER 66.1    // Wheel diameter in millimeters

// A single motor
class Motor
{
public:
    void init(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);

    double pos_current;  // Current distance motor has travelled
    double pos_setpoint; // setpoint distance

    volatile int32_t ticks_;
    volatile int b_temp; // temp value used in interrupts

private:
    uint8_t pwm_pin_;
    uint8_t dir_pin_1_;
    uint8_t dir_pin_2_;
    uint8_t enc1_pin_;
    uint8_t enc2_pin_;
};

// Pair of Drive Motors
class Motors
{
public:
    // Use static class members so we can access them from interupts
    static Motor *left;
    static Motor *right;

    static void leftMotorInterrupt();
    static void rightMotorInterrupt();
    static void printTicks(); // debugging
    static int cmToTicks(float cm);
};

#endif