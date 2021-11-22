#ifndef IMU_H
#define IMU_H

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "config.h"

// Our MPU 6050 IMU
class IMU
{

public:
    IMU();
    bool init();
    void init_hardware();

    void readData();

    int getYaw();
    int getNormalizedYaw();
    void zero_yaw();
    int calculate_required_yaw_right_turn(int right_turn_angle);
    int calculate_required_yaw_left_turn(int left_turn_angle);
    // void onDataReady();

private:
    uint16_t yaw_offset_;
    int yaw_;

    MPU6050 mpu_;
    uint16_t imu_packetsize_;

    volatile bool data_ready_;
};

#endif