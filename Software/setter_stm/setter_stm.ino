// Demonstrates use of the Wire library
// Writes servo position to an I2C slave device
#include <Wire.h>
void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
}
byte x = 0;
void loop()
{
  x = 140;
  Wire.beginTransmission(8); // transmit to device #4
  Wire.write("x is ");       // sends five bytes
  Wire.write(x);             // sends one byte
  Wire.endTransmission();    // stop transmitting

  delay(1000);
  x = 110;
  Wire.beginTransmission(8); // transmit to device #4
  Wire.write("x is ");       // sends five bytes
  Wire.write(x);             // sends one byte
  Wire.endTransmission();    // stop transmitting

  delay(1000);
}
