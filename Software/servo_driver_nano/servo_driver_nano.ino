// Sets servo angle to value sent by master.
// Acts as a dedicated servo driver

#include <Wire.h>
#include <Servo.h>

Servo myservo;                // create servo object to control a servo
bool receivedVal = false;     // Wire event flag
volatile int servo_angle = 0; // angle sent by master STM32
void setup()
{
  Wire.begin(8);                // join i2c bus as address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(130); // set starting position between open and close, to init servo.
}

void loop()
{
  delay(100);
  if (receivedVal)
  {
    receivedVal = false;
    Serial.println(servo_angle); // print the integer
    myservo.write(servo_angle);  // tell servo to go to position in variable 'servo_angle'
  }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int numBytes)
{
  while (1 < Wire.available()) // loop through all but the last byte
  {
  }
  servo_angle = Wire.read(); // receive byte as an integer
  receivedVal = true;
}
