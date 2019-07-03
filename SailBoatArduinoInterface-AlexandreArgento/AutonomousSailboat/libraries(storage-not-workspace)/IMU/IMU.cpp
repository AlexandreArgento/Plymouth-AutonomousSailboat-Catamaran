#include <IMU.h>
#include <Wire.h>

void IMU::init(ros::NodeHandle* n)
{
	Wire.begin();
    accelgyro.initialize();
    //Maybe accelgyro.testConnection() later
	//Barometer.init();

	SensorROS::init(n);
}

void IMU::updateMeasures()
{
    /// Getting Compass data ///
    uint8_t buffer_m[6];
    I2C_M.writeByte(MPU9150_RA_MAG_ADDRESS, 0x0A, 0x01); //enable the magnetometer
    delay(10);
    I2C_M.readBytes(MPU9150_RA_MAG_ADDRESS, MPU9150_RA_MAG_XOUT_L, 6, buffer_m);

    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    int16_t mx, my, mz;

    accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
    
    mx = ((int16_t)(buffer_m[1]) << 8) | buffer_m[0] ;
    my = ((int16_t)(buffer_m[3]) << 8) | buffer_m[2] ;
    mz = ((int16_t)(buffer_m[5]) << 8) | buffer_m[4] ;

    float Mxyz[3];
    Mxyz[0] = (double) mx * 1200 / 4096;
    Mxyz[1] = (double) my * 1200 / 4096;
    Mxyz[2] = (double) mz * 1200 / 4096;

    /// Calibration adjustment (to improve!) ///
    float mx_centre = 9.00; //Data from latest calibration
    float my_centre = -1.00; //Data from latest calibration
    float mz_centre = -13.00; //Data from latest calibration

    Mxyz[0] = Mxyz[0] - mx_centre;
    Mxyz[1] = Mxyz[1] - my_centre;
    Mxyz[2] = Mxyz[2] - mz_centre;

    /// Getting heading ///
    heading = 180 * atan2(Mxyz[1], Mxyz[0]) / PI;
    if (heading < 0) heading += 360;
}

void IMU::communicateData()
{
    /*
	msg.orientation.x = 0.980;
	msg.orientation.y = 0.001;
	msg.orientation.z = 0.189;
	msg.orientation.w = -0.063;
	*/

    msg.orientation.x = heading;
    msg.orientation.y = 0.0;
	msg.orientation.z = 0.0;
	msg.orientation.w = 0.0;

	msg.header.stamp = nh->now();
	pub.publish(&msg);
}
