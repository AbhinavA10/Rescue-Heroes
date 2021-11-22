#include "imu.h"
#include "pin_assignment.h"
#include "config.h"
#include "task/display.h"

IMU::IMU() {}

// Set up and initialize the IMU
bool IMU::init()
{
    yaw_offset_ = 0;
    data_ready_ = false;

    mpu_ = MPU6050();

    mpu_.initialize();
    return true;
}

// yaw/pitch/roll angles (in degrees) calculated from the quaternions coming
// from the FIFO. Note this also requires gravity vector calculations.

volatile bool mpuInterrupt = false; // indicates whether MPU interrupt pin has gone high

// MPU control/status vars
bool dmpReady = false; // set true if DMP init was successful
// uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;        // [w, x, y, z]         quaternion container
VectorFloat gravity; // [x, y, z]            gravity vector
float ypr[3];        // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// Initialize IMU Hardware
void IMU::init_hardware()
{

    // verify connection
    Serial.println(F("Testing device connections..."));
    bool conn = mpu_.testConnection();
    Serial.println(conn ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
    Display::text[IMU_SENSOR_STATUS_INDEX] = (conn) ? F("IMU Y") : F("IMU N");

    // load and configure the DMP
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu_.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu_.setXGyroOffset(220);
    mpu_.setYGyroOffset(76);
    mpu_.setZGyroOffset(-85);
    mpu_.setZAccelOffset(1788); // 1688 factory default for my test chip
                                // make sure it worked (returns 0 if so)
    if (devStatus == 0)
    {
        // Calibration Time: generate offsets and calibrate our MPU6050
        mpu_.CalibrateAccel(6);
        mpu_.CalibrateGyro(6);
        mpu_.PrintActiveOffsets();
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu_.setDMPEnabled(true);
        // pinMode(IMU_INT, INPUT); // IMU Interrupt is not used.
        // enable Arduino interrupt detection
        // Serial.print(F("Enabling interrupt detection (Arduino external interrupt "));
        // Serial.print(digitalPinToInterrupt(IMU_INT));
        // Serial.println(F(")..."));
        // attachInterrupt(digitalPinToInterrupt(IMU_INT), IMU::onDataReady, RISING);
        // mpuIntStatus = mpu_.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        Serial.println(F("DMP ready!"));
        Display::text[IMU_SENSOR_STATUS_INDEX] += F("; DMP Y");
        dmpReady = true;
        // get expected DMP packet size for later comparison
        packetSize = mpu_.dmpGetFIFOPacketSize();
    }
    else
    {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
        Display::text[IMU_SENSOR_STATUS_INDEX] += F("; DMP N");
    }
}

// Interrupt that tells us the IMU has new data
// Note: interrupt is not actually used...
// void IMU::onDataReady()
// {
//     mpuInterrupt = true;
// }

// Get latest data from IMU
void IMU::readData()
{
    // if programming failed, don't try to do anything
    if (!dmpReady)
        return;
    // read a packet from FIFO
    if (mpu_.dmpGetCurrentFIFOPacket(fifoBuffer))
    { // Get the Latest packet
        mpu_.dmpGetQuaternion(&q, fifoBuffer);
        mpu_.dmpGetGravity(&gravity, &q);
        mpu_.dmpGetYawPitchRoll(ypr, &q, &gravity);
        // float yaw = ypr[0] * 180 / PI;
        // float pitch = ypr[1] * 180 / PI;
        // float roll = ypr[2] * 180 / PI;
        // Serial.print("ypr\t");
        // Serial.print(yaw);
        // Serial.print("\t");
        // Serial.print(pitch);
        // Serial.print("\t");
        // Serial.println(roll);
        yaw_ = round(ypr[0] * 180 / PI);
        mpu_.resetFIFO();
    }
}

// Set yaw value to 0
void IMU::zero_yaw()
{
    yaw_offset_ = yaw_;
}

// Return Yaw
int IMU::getYaw()
{
    return yaw_;
}
// Return Normalized Yaw
int IMU::getNormalizedYaw()
{
    // normalize yaw from -180 -> 180 to 0->360
    return yaw_ + 180;
}

// Calculate required yaw if making a right turn.
// Assumes you're only turning right!
int IMU::calculate_required_yaw_right_turn(int right_turn_angle)
{
    int old_yaw = getNormalizedYaw();
    int required_yaw = old_yaw + right_turn_angle;
    // Calculate required yaw.
    if (required_yaw > 360)
    {
        // old_yaw is in range (360-right_turn_angle) -> 360.
        // Adding +right_turn_angle will overflow into "negative yaw"
        // adding right_turn_angle needs to become value closer to 0 instead
        required_yaw = required_yaw - 360;
    }
    return required_yaw;
}

// Calculate required yaw if making a left turn.
// Assumes you're only turning left!
int IMU::calculate_required_yaw_left_turn(int left_turn_angle)
{
    int old_yaw = getNormalizedYaw();
    int required_yaw = old_yaw - left_turn_angle;
    // Calculate required yaw.
    if (required_yaw < 0)
    {
        // old_yaw is in range 0 -> left_turn_angle.
        // Subtracting -left_turn_angle will overflow into near 360 deg
        // Subtracting left_turn_angle needs to become value closer to 360 instead
        required_yaw = required_yaw + 360;
    }
    return required_yaw;
}