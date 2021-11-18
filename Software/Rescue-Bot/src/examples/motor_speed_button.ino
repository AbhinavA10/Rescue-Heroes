// Determining bounds of our motor speed, by pressing a push button to change the speed.

#include <Arduino.h>
#include <Wire.h> // I2C
#include <SPI.h>  // Required for Color Sensor library to compile
#include "pin_assignment.h"
#include "config.h"
#include "actuators/servos.h"
#include "task/motor_control.h"
#include "task/display.h"
int motor_speed = 140; // baseline. 150 seems to be a better baseline till feedback control
void drive(int mspeed)
{
    // Set Motor A forward
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    // Set Motor B forward
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    // Run the motors at the specified speed
    analogWrite(ENA_PWM, mspeed);
    analogWrite(ENB_PWM, mspeed);
}

// this constant won't change:
const int buttonPin = USER_BTN; // the pin that the pushbutton is attached to

// Variables will change:
int buttonPushCounter = 0; // counter for the number of button presses
int buttonState = 0;       // current state of the button
int lastButtonState = 0;   // previous state of the button
void setup()
{
    Serial.begin(115200);
    Display::init_display();
    initScoopServo();
    MotorControl::init_motor_control();
    pinMode(USER_BTN, INPUT);
}

void loop()
{
    buttonState = digitalRead(buttonPin);

    // compare the buttonState to its previous state
    if (buttonState != lastButtonState)
    {
        // if the state has changed, increment the counter
        if (buttonState == HIGH)
        {
            // if the current state is HIGH then the button went from off to on:
            buttonPushCounter++;
            motor_speed++;
            Serial.print("number of button pushes: ");
            Serial.println(buttonPushCounter);
        }
        else
        {
            // if the current state is LOW then the button went from on to off:
        }
        // Delay a little bit to avoid bouncing
        delay(50);
    }
    // save the current state as the last state, for next time through the loop
    lastButtonState = buttonState;
    Display::refresh_display_big(motor_speed);
    drive(motor_speed);
}