#ifndef IMU_SENSOR_H
#define IMU_SENSOR_H

/*
// Accelerometer/Gyro register addresses
#define ACCEL_CONFIG 0x1C
#define GYRO_CONFIG 0x1B
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D
#define ACCEL_ZOUT_H 0x3F
#define TEMP_OUT_H 0x41
#define GYRO_XOUT_H 0x43
#define GYRO_YOUT_H 0x45
#define GYRO_ZOUT_H 0x47
#define PWR_MGMT_1 0x6B

//Compass register addresses
#define COMP_STATUS 0x02
#define COMP_XOUT_L 0x03
#define COMP_YOUT_L 0x05
#define COMP_ZOUT_L 0x07

// Accelerometer range modes
#define ACCELRANGE_2g 0
#define ACCELRANGE_4g 1
#define ACCELRANGE_8g 2
#define ACCELRANGE_16g 3

// Gyroscope sensitivity
#define GYRORANGE_250DPS 0
#define GYRORANGE_500DPS 1
#define GYRORANGE_1000DPS 2
#define GYRORANGE_2000DPS 3
*/

#include <Sensor.h>
#include <sensor_msgs/Imu.h>
#include "MPU9250.h"
#include "I2Cdev.h"

class IMU : public SensorROS
{
	public:
		IMU() : SensorROS("IMU", &msg) {}
		
		void init(ros::NodeHandle* n);
		void updateMeasures();
		void communicateData();
	private:
	    MPU9250 accelgyro;
        I2Cdev I2C_M;
        float heading;
        
		sensor_msgs::Imu msg;
};

#endif
