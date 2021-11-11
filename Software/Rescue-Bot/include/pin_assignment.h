#ifndef PIN_ASSIGNMENT_H
#define PIN_ASSIGNMENT_H

#include <Arduino.h>

/*
    Pin Assignments  
*/
// #define SCL         D15 // already defined in Arduino.h
// #define SDA         D14 // already defined in Arduino.h
//TODO: find left vs right motor. 

// Motor A (front left)
#define ENA_PWM     D12
#define IN1         D11
#define IN2         D10
// Motor B (front right)
#define IN3         D9
#define IN4         D8
#define ENB_PWM     D7

#define SERVO_PWM   D6

#define ENC1_A      D5
#define ENC1_B      D4
#define ENC2_A      D3
#define ENC2_B      D2
#define IMU_INT     A0
#define BUZZER      A1

#endif