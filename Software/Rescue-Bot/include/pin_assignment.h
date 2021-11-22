#ifndef PIN_ASSIGNMENT_H
#define PIN_ASSIGNMENT_H

#include <Arduino.h>

/*
    Pin Assignments  
*/
// #define SCL         D15 // Blue. already defined in Arduino.h
// #define SDA         D14 // Yellow. already defined in Arduino.h

// Motor A (left)
#define ENA_PWM     D12 // Band - Orange
#define IN1         D11 // Band - Yellow
#define IN2         D10 // Band - Green
// Motor B (right)
#define IN3         D9 // Band - Blue
#define IN4         D8 // Band - Purple
#define ENB_PWM     D7 // Band - White

// #define SERVO_PWM   D6 // Single - orange

// Motor B (right)
#define ENC1_A      D5 // Pair - red
#define ENC1_B      D4 // Pair - orange

// Motor A (left)
#define ENC2_A      D3 // Pair - red with black
#define ENC2_B      D2 // Pair - orange with black

#define IMU_INT     A0 // Single - Green Hookup wire
#define BUZZER      A1 // Single - Yellow Hookup wire
#define TOGGLE_PIN  A2 // general pin that can be used for toggling/debugging

// Indicies in ColorSensors array
#define COLORSENSOR_FL 0
#define COLORSENSOR_FR 1
#define COLORSENSOR_L 2
#define COLORSENSOR_R 3

#endif