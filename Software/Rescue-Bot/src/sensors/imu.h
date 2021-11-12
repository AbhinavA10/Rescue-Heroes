#ifndef IMU_H
#define IMU_H

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "config.h"

// This way we can refer to `imu` in our application code
#define imu IMU_Wrapper::primary

// Normalized, (filtered?) orientation in degrees
struct Orientation
{
    int16_t yaw;
    int16_t pitch;
    int16_t roll;
};

// We use a seperate wrapper class with a static member
// so that we can access the IMU from within an interrupt
// service routine
class IMU_Wrapper;

// Our MPU 6050 IMU
class IMU
{
    friend class IMU_Wrapper;

public:
    bool init();
    void run();

    void readData();
    int milestone4();

    Orientation orientation; // make volatile to stop optimizing out

    Orientation getYPR();

    void filterYPR();
    void zero_yaw();

private:
    uint16_t yaw_offset_;
    
    MPU6050 mpu_;
    uint16_t imu_packetsize_;

    volatile bool data_ready_;
    uint16_t error_count = 0;
};

class IMU_Wrapper
{
public:
    static IMU *primary;
    static void onDataReady();
};

#endif