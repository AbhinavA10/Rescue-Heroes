// https://www.arduino.cc/en/Tutorial/LibraryExamples/MasterWriter
// Sets servo angle to value sent by master.

#include <Wire.h>
#include <Servo.h>

Servo myservo; // create servo object to control a servo
// twelve servo objects can be created on most boards
bool receivedVal = false;
volatile int x = 0;
void setup()
{
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(110); // tell servo to go to position in variable 'pos'
}

void loop()
{
  delay(100);
  if (receivedVal)
  {
    receivedVal = false;
    Serial.println(x); // print the integer
    myservo.write(x);
  }
}
// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int numBytes)
{
  while (1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);      // print the character
  }
  x = Wire.read(); // receive byte as an integer
  receivedVal = true;
}
