#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "Adafruit_TCS34725.h"

// Define the experimental constants for the color sensor
#define COLOR_RED_R_ADAFRUIT 164.6
#define COLOR_RED_G_ADAFRUIT 44.3
#define COLOR_RED_B_ADAFRUIT 41.8
#define COLOR_RED_MAX_DISTANCE_ADAFRUIT 20 // 9.1

#define COLOR_GREEN_R_ADAFRUIT 69.22
#define COLOR_GREEN_G_ADAFRUIT 107.36
#define COLOR_GREEN_B_ADAFRUIT 50.75
#define COLOR_GREEN_MAX_DISTANCE_ADAFRUIT 14.1

#define COLOR_BLUE_R_ADAFRUIT 29.11
#define COLOR_BLUE_G_ADAFRUIT 80.89
#define COLOR_BLUE_B_ADAFRUIT 132.33
#define COLOR_BLUE_MAX_DISTANCE_ADAFRUIT 12.1

#define RED 1
#define GREEN 2
#define BLUE 3
#define OTHER 0

#define LEFT 20
#define RIGHT 21
#define NONE 22

#define carSpeed 215

#define numberOfSensors 4 // Put the number of color sensors you have here!

Adafruit_TCS34725 tcs[] = {Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_4X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_4X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_4X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_4X)};

//Line Tracking IO define
int colorSensor_R;
int colorSensor_L;

// Motor A (front left)
int ENA = D12;
int IN1 = D11;
int IN2 = D10;

// Motor B (front right)
int ENB = D7;
int IN3 = D9;
int IN4 = D8;

// Euclidian Distance for colors
float RedDist = 0;
float GreenDist = 0;
float BlueDist = 0;
int ColorFound_R = 0;
int ColorFound_L = 0;

void choose_mux_bus(uint8_t bus)
{
  Wire.beginTransmission(0x70);
  Wire.write(1 << (bus + 2)); // will be using 2-3 instead of 0-1 SDA/SCL pins because of convience (placed better on the breadboard)
  Wire.endTransmission();
}

float findColor(float R_New, float G_New, float B_New)
{
  RedDist = sqrt(pow(R_New - COLOR_RED_R_ADAFRUIT, 2) + pow(G_New - COLOR_RED_G_ADAFRUIT, 2) + pow(B_New - COLOR_RED_B_ADAFRUIT, 2));
  GreenDist = sqrt(pow(R_New - COLOR_GREEN_R_ADAFRUIT, 2) + pow(G_New - COLOR_GREEN_G_ADAFRUIT, 2) + pow(B_New - COLOR_GREEN_B_ADAFRUIT, 2));
  BlueDist = sqrt(pow(R_New - COLOR_BLUE_R_ADAFRUIT, 2) + pow(G_New - COLOR_BLUE_G_ADAFRUIT, 2) + pow(B_New - COLOR_BLUE_B_ADAFRUIT, 2));
  if (RedDist < COLOR_RED_MAX_DISTANCE_ADAFRUIT)
  {
    return RED;
  }
  else if (GreenDist < COLOR_GREEN_MAX_DISTANCE_ADAFRUIT)
  {
    return GREEN;
  }
  else if (BlueDist < COLOR_BLUE_MAX_DISTANCE_ADAFRUIT)
  {
    return BLUE;
  }
  else
  {
    return OTHER;
  }
}

int readColor()
{
  for (int i = 0; i < numberOfSensors; i++)
  {
    // This is for stopping it from reading data from color sensor 1 and 2, and only allows 0 and 3
    if (i == 2 || i == 3)
    {
      continue;
    }

    choose_mux_bus(i);
    float red, green, blue;
    tcs[i].getRGB(&red, &green, &blue);

    // Serial.print("Sensor: ");
    // Serial.print(i);
    // Serial.print("\t");
    // Serial.print("R:\t");
    // Serial.print(int(red));
    // Serial.print("\tG:\t");
    // Serial.print(int(green));
    // Serial.print("\tB:\t");
    // Serial.print(int(blue));
    // Serial.print("\n");

    if (i == 0 && findColor(red, green, blue) == RED)
    {
      return LEFT;
      // Serial.println("LEFT = red");
    }
    if (i == 1 && findColor(red, green, blue) == RED)
    {
      return RIGHT;
      // Serial.println("RIGHT = red");
    }
  }
  return NONE;
}

void forward()
{
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  // Set Motor A forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Set Motor B forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Forward");
}

void left()
{
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  // Set Motor A forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Set Motor B reverse
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Left");
}

void right()
{
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  // Set Motor A reverse
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // Set Motor B forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  Serial.println("Right");
}

void stop()
{
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  //Serial.println("Stop!");
}

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  pinMode(D12, OUTPUT);
  pinMode(D11, OUTPUT);
  pinMode(D10, OUTPUT);
  pinMode(D9, OUTPUT);
  pinMode(D8, OUTPUT);
  pinMode(D7, OUTPUT);

  for (int i = 0; i < numberOfSensors; i++)
  {
    Serial.println(i);
    choose_mux_bus(i);
    if (tcs[i].begin())
    {
      Serial.print("Found sensor ");
      Serial.println(i);
    }
    else
    {
      Serial.println("No Sensor Found");
      while (true)
        ;
    }
  }
}

void loop()
{
  switch (readColor())
  {
  case LEFT:
    left();
    break;
  case RIGHT:
    right();
    break;
  default:
    forward();
    break;
  }
  delay(3);
}