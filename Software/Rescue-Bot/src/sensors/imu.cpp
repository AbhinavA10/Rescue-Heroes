#include "imu.h"
#include "pin_assignment.h"
#include "config.h"

// The "static" IMU object that our ISR will access
IMU *IMU_Wrapper::primary = new IMU;

// Set up and initialize the IMU
bool IMU::init()
{
    yaw_offset_ = 0;
    data_ready_ = false;
    error_count = 0;

    orientation = Orientation{};
    mpu_ = MPU6050();

    mpu_.initialize();
    return true;
}

// yaw/
// pitch/roll angles (in degrees) calculated from the quaternions coming
// from the FIFO. Note this also requires gravity vector calculations.

volatile bool mpuInterrupt = false; // indicates whether MPU interrupt pin has gone high

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;        // [w, x, y, z]         quaternion container
VectorFloat gravity; // [x, y, z]            gravity vector
float ypr[3];        // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

void IMU::run()
{

    // From example:
    // verify connection
    Serial.println(F("Testing device connections..."));
    bool conn = mpu_.testConnection();
    Serial.println(conn ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

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
        pinMode(IMU_INT, INPUT);
        // enable Arduino interrupt detection
        Serial.print(F("Enabling interrupt detection (Arduino external interrupt "));
        Serial.print(digitalPinToInterrupt(IMU_INT));
        Serial.println(F(")..."));
        attachInterrupt(digitalPinToInterrupt(IMU_INT), IMU_Wrapper::onDataReady, RISING);
        mpuIntStatus = mpu_.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        Serial.println(F("DMP ready! Waiting for first interrupt..."));
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
    }
}

// Interrupt that tells us the IMU has new data
// Note: interrupt is not actually used...
void IMU_Wrapper::onDataReady()
{
    mpuInterrupt = true;
    imu->data_ready_ = true;
}

// ISR that is run every time the IMU has a new reading
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
        orientation.yaw = ypr[0] * 180 / PI;
        orientation.pitch = ypr[1] * 180 / PI;
        orientation.roll = ypr[2] * 180 / PI;
        Serial.print("ypr\t");
        Serial.print(orientation.yaw);
        Serial.print("\t");
        Serial.print(orientation.pitch);
        Serial.print("\t");
        Serial.println(orientation.roll);
        mpu_.resetFIFO();
    }
    // Try exponential filter to reduce noise if needed, see https://en.wikipedia.org/wiki/Exponential_smoothing
}

int IMU::milestone4()
{
    // if programming failed, don't try to do anything
    if (!dmpReady)
        return INT16_MIN; // return impossible value
    // read a packet from FIFO
    if (mpu_.dmpGetCurrentFIFOPacket(fifoBuffer))
    { // Get the Latest packet
        mpu_.dmpGetQuaternion(&q, fifoBuffer);
        mpu_.dmpGetGravity(&gravity, &q);
        mpu_.dmpGetYawPitchRoll(ypr, &q, &gravity);
        int yaw = round(ypr[0] * 180 / PI);
        PRINT_DEBUG(yaw)
        mpu_.resetFIFO();
        return yaw;
    }
}

// Set yaw value to 0
void IMU::zero_yaw()
{
    yaw_offset_ = orientation.yaw;
}

// Return Yaw, Pitch, Roll of IMU
Orientation IMU::getYPR()
{
    return orientation;
}