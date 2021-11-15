#ifndef IMU_H
#define IMU_H

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "config.h"

// Filtered orientation in degrees
struct Orientation
{
    int16_t yaw;
    int16_t pitch;
    int16_t roll;
};

// Our MPU 6050 IMU
class IMU
{

public:
    IMU();
    bool init();
    void run();

    void readData();
    int milestone4();

    Orientation getYPR();
    int getYaw();

    void filterYPR();
    void zero_yaw();
    void onDataReady();

private:
    uint16_t yaw_offset_;
    Orientation orientation;
    int yaw_;

    MPU6050 mpu_;
    uint16_t imu_packetsize_;

    volatile bool data_ready_;
};

#endif