#include "imu.h"

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
    //TODO: enable DMP

    return true;
}

void IMU::run()
{
    attachInterrupt(digitalPinToInterrupt(IMU_INTERRUPT_PIN), IMU_Wrapper::onDataReady, RISING);
}

// Interrupt that tells us the IMU has new data
void IMU_Wrapper::onDataReady()
{
    imu->data_ready_ = true;
}

// ISR that is run every time the IMU has a new reading
void IMU::readData()
{
    // Try exponential filter to reduce noise if needed, see https://en.wikipedia.org/wiki/Exponential_smoothing
}

// Set yaw value to 0
void IMU::zero_yaw()
{
    yaw_offset_ = orientation.yaw;
}

// Return Yaw, Pitch, Roll of IMU
Orientation IMU::getYPR()
{
    return Orientation{
        yaw_.last(),
        pitch_.last(),
        roll_.last()};
}