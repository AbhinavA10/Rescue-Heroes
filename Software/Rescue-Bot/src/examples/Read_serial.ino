// Reading from Serial Monitor and setting servo position
#include <Arduino.h>
#include <Wire.h> // I2C
#include <SPI.h>  // Required for Color Sensor library to compile

#include "pin_assignment.h"

#include <Servo.h>

Servo myservo;
const unsigned int MAX_MESSAGE_LENGTH = 12;
void setup()
{
  myservo.attach(SERVO_PWM);
  Serial.begin(115200);
}
void loop()
{

  //Check to see if anything is available in the serial receive buffer
  while (Serial.available() > 0)
  {
    //Create a place to hold the incoming message
    static char message[MAX_MESSAGE_LENGTH];
    static unsigned int message_pos = 0;

    //Read the next available byte in the serial receive buffer
    char inByte = Serial.read();

    //Message coming in (check not terminating character) and guard for over message size
    if (inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1))
    {
      //Add the incoming byte to our message
      message[message_pos] = inByte;
      message_pos++;
    }
    //Full message received...
    else
    {
      //Add null character to string
      message[message_pos] = '\0';

      //Print the message (or do other things)
      Serial.println(message);

      //Or convert to integer and print
      int number = atoi(message);
      Serial.println(number);
      
      myservo.writeMicroseconds(number); // set servo to user inputted value
      delay(20);

      //Reset for the next message
      message_pos = 0;
    }
  }
}