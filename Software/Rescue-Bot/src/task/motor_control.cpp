#include "motor_control.h"
#include "pin_assignment.h"
#include "actuators/servos.h"

#define NMOTORS 2
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1

namespace MotorControl
{

    long prev_time = 0;

    SimplePID pid[2]; // Independant PIDs for each motor
    float vt[2] = {0, 0};

    const int pwm[] = {ENA_PWM, ENB_PWM};
    const int in1[] = {IN1, IN3};
    const int in2[] = {IN2, IN4};

    long posPrev[] = {0, 0}; // previous encoder counts
    float vel_rpm_filtered[] = {0, 0};
    float vel_rpm_prev[] = {0, 0};

    void init()
    {
        motors.left->init(ENA_PWM, IN1, IN2, ENC2_A, ENC2_B);
        motors.right->init(ENB_PWM, IN3, IN4, ENC1_A, ENC1_B);
        initScoopServo();
        for (int i = 0; i < 2; i++)
        {
            pid[i].setParams(70, 3.5, 0, MAX_SPEED); // PID params
            // pid[i].setParams(5, 0, 0, MAX_SPEED);
        }
    }

    //Resets both tick counters to 0.
    void reset_ticks()
    {
        motors.left->ticks = 0;
        motors.right->ticks = 0;
    }

    // Set left motor speed
    void write_left_speed(int left)
    {
        /*
        255 is the max speed a motor can normally handle
        Blue motors can run at max 9V. Battery pack we're 8xAA ==> gives 12V (1.5V x 8), 
        L298N Motor driver takes 1.4V about, meaning 10.6V is left for the motors.
        So 9/10.6 = x/255 ==> x = 215 = max speed of blue motors
        */
        left = constrain(left, 0, MAX_SPEED);
        analogWrite(ENA_PWM, left);
    }

    // Set right motor speed
    void write_right_speed(int right)
    {
        right = constrain(right, 0, MAX_SPEED);
        analogWrite(ENB_PWM, right);
    }

    // Set Motor speed
    // parameters: left_speed, right_speed
    void write_speed(int left, int right)
    {
        write_left_speed(left);
        write_right_speed(right);
    }

    // Runs the motors for specified distance
    // Note: is blocking
    void move_till_dist(float cm)
    {
        int ticks_setpoint = Motors::cmToTicks(cm);
        reset_ticks(); // Reset all tick counters
        // move forward till one of motors reach setpoint
        while (ticks_setpoint > abs(motors.left->ticks) && ticks_setpoint > abs(motors.right->ticks))
        {
            if (ticks_setpoint > abs(motors.left->ticks))
            {
                write_left_speed(FWD_SPEED);
            }
            else
            {
                write_left_speed(0);
            }
            if (ticks_setpoint > abs(motors.right->ticks))
            {
                write_right_speed(FWD_SPEED);
            }
            else
            {
                write_right_speed(0);
            }
            // Motors::printTicks(); // debugging
        }
        // PRINT_DEBUG(ticks_setpoint)
        // Motors::printTicks();
        StopMotors();  // Stop when done
        reset_ticks(); // Reset all tick counters
    }

    // Function to Move Forward
    void MoveForward()
    {
        // Set Motor A forward
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        // Set Motor B forward
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);

        write_speed(FWD_SPEED, FWD_SPEED);
    }

    void MoveForward_Distance(float cm)
    {
        MoveForward();
        move_till_dist(cm);
    }

    // Move backwards
    void MoveReverse()
    {
        // Set Motor A reverse
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        // Set Motor B reverse
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);

        write_speed(FWD_SPEED, FWD_SPEED);
        // Run the motors at the specified speed, and amount of time
        // e.g.: run_motors_for_duration(FWD_SPEED, delayAmount);
    }

    void MoveReverse_Distance(float cm)
    {
        MoveReverse();
        move_till_dist(cm);
    }

    // Spin Right
    void SpinRight()
    {
        // Set Motor A reverse
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        // Set Motor B forward
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);

        write_speed(TURNING_SPEED, TURNING_SPEED);
    }

    // Spin Right for a fixed amount of time in ms.
    // Note: is blocking.
    void SpinRight_Timed(int amt)
    {
        SpinRight();
        delay(amt);   // Run motors for a set time
        StopMotors(); // stop when done
    }

    // Spin Left
    void SpinLeft()
    {
        // Set Motor A forward
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        // Set Motor B reverse
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);

        write_speed(TURNING_SPEED, TURNING_SPEED);
    }

    // Spin Left for a fixed amount of time in ms.
    // Note: is blocking.
    void SpinLeft_Timed(int amt)
    {
        SpinLeft();
        delay(amt);   // Run motors for a set time
        StopMotors(); // stop when done
    }

    // Stop both motors
    void StopMotors()
    {
        write_speed(0, 0);
    }

    void run()
    {
        // Motors::printTicks();
        update_motors_pid();
    }

    void setMotorPID(int dir, int pwmVal, int pwm, int in1, int in2)
    {
        analogWrite(pwm, pwmVal); // Motor speed
        if (dir == 1)
        {
            // Turn motors forward
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
        }
        else if (dir == -1)
        {
            // Turn motors reverse
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
        }
        else
        {
            // Or dont turn
            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
        }
    }

    // Set speed for PID Control
    void forward_pid()
    {
        vt[LEFT_MOTOR] = SPEED_M_S;
        vt[RIGHT_MOTOR] = SPEED_M_S;
        Serial.println("Forward");
    }
    void backward_pid()
    {
        vt[LEFT_MOTOR] = -SPEED_M_S;
        vt[RIGHT_MOTOR] = -SPEED_M_S;
        Serial.println("Back");
    }
    void left_pid()
    {
        vt[LEFT_MOTOR] = -SPEED_M_S;
        vt[RIGHT_MOTOR] = SPEED_M_S;
        Serial.println("Left");
    }
    void right_pid()
    {
        vt[LEFT_MOTOR] = SPEED_M_S;
        vt[RIGHT_MOTOR] = -SPEED_M_S;
        Serial.println("Right");
    }
    void stop_pid()
    {
        vt[LEFT_MOTOR] = 0;
        vt[RIGHT_MOTOR] = 0;
    }

    // PID speed control of motors
    void update_motors_pid()
    {
        // read the position
        long pos[2];    // temp variable, reading current pos from interrupt var
        noInterrupts(); // disable interrupts temporarily while reading
        pos[LEFT_MOTOR] = Motors::left->ticks;
        pos[RIGHT_MOTOR] = Motors::right->ticks;
        interrupts(); // turn interrupts back on

        // Compute velocity
        long curr_time = micros();
        float deltaT = ((float)(curr_time - prev_time)) / 1.0e6;
        prev_time = curr_time;

        for (int k = 0; k < NMOTORS; k++)
        {
            float vel_temp_ticks = (pos[k] - posPrev[k]) / deltaT; // calculating current ticks/s
            posPrev[k] = pos[k];
            // Convert count/s to RPM of motor shaft (not wheel)
            float vel_rpm = vel_temp_ticks / 600.0 * 60.0; // rpm. temp

            // Low-pass filter (25 Hz cutoff)
            // vel_rpm_filtered = 0.854 * vel_rpm_filtered + 0.0728 * vel_rpm + 0.0728 * vel_rpm_prev; // Original 25Hz cutoff
            vel_rpm_filtered[k] = 0.96907 * vel_rpm_filtered[k] + 0.015465 * vel_rpm + 0.015465 * vel_rpm_prev[k]; // Our 5Hz cutoff
            vel_rpm_prev[k] = vel_rpm;
        }

        // Loop through the motors
        for (int k = 0; k < NMOTORS; k++)
        {
            int pwr, dir;                                               // calculated by PID
            pid[k].evalu(vel_rpm_filtered[k], vt[k], deltaT, pwr, dir); // compute the required pwm
            setMotorPID(dir, pwr, pwm[k], in1[k], in2[k]);              // signal the motor
        }
        for (int i = 0; i < 2; i++)
        {
            Serial.print(vt[i]);
            Serial.print(" ");
            Serial.print(vel_rpm_filtered[i]);
            Serial.print(" ");
        }
        Serial.println();
    }
};
