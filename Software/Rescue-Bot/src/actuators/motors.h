#ifndef MOTORS_H
#define MOTORS_H

#define MAX_MOTOR_SPEED 215    // PWM width
#define TICKS_PER_ROTATION 135 // counts per wheel rotation
#define WHEEL_DIAMETER 66.1    // Wheel diameter in millimeters

// Direction of Motor Travel
enum class Direction : int8_t
{
    REVERSE = -1,
    FORWARD = 1
};

// A single motor
class Motor
{
    /*
    motor->init() must be called first for each motor before setSpeed is used
    */
public:
    void init(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
    void stop();

    double pos_current;  // Current distance motor has travelled
    double pos_setpoint; // setpoint distance


    volatile int32_t ticks_;
    volatile int b_temp; // temp value used in interrupts

private:
    uint8_t get_pwm_command(int8_t);

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

    static void setSpeed(int8_t, int8_t);
    static void stop();
};

#endif