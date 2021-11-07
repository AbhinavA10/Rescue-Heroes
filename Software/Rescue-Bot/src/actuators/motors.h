#ifndef MOTORS_H
#define MOTORS_H

#define NUM_COUNTS_PER_REVOLUTION 135

#define LEFT_MOTOR_PWM_PIN 5
#define LEFT_MOTOR_IN1_PIN 13
#define LEFT_MOTOR_IN2_PIN 13

#define RIGHT_MOTOR_PWM_PIN 13
#define RIGHT_MOTOR_IN1_PIN 13
#define RIGHT_MOTOR_IN2_PIN 13

#define LEFT_MOTOR_SENSOR_A_PIN 19
#define LEFT_MOTOR_SENSOR_B_PIN 25

#define RIGHT_MOTOR_SENSOR_A_PIN 2
#define RIGHT_MOTOR_SENSOR_B_PIN 10

#define WHEEL_RADIUS 3.3         // cm
#define TICKS_PER_REVOLUTION 208 // TBD
#define RADS_PER_TICK 0.0302     // TBD

#define MAX_MOTOR_SPEED 50 // cm/s

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
    motor->init({PINS}) must be called first for each motor before setSpeed is used
    */
public:
    void init(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);

    int8_t direction;
    double filtered_speed;

    // Sets motor control parameters
    void setSpeed(int8_t);
    void setDirection(Direction);

    // Runs motor control
    void adjustSpeed();

    // Value from -100 to 100 corresponding to motor speed
    // Adjusted to make measured speed equal to set point
    // Command sent to PWM pins on motors, after mapping appropriately
    double speed_command;
    // The real speed we want
    double speed_setpoint;
    // Feedback from encoders
    double speed;

    void stop();

    // ISR when encoder encounters an edge
    void update();

    void resetDistance();
    double getDistance();
    void readDistance();
    double distance;

    int32_t ticks_;

private:
    uint8_t get_pwm_command(int8_t);

    unsigned long last_;
    uint8_t pwm_pin_;
    uint8_t dir_pin_1_;
    uint8_t dir_pin_2_;
    uint8_t sensor1_pin_;
    uint8_t sensor2_pin_;
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