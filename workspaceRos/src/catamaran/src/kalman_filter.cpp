#include <ros/ros.h>
#include <std_msgs/Float64MultiArray.h>
#include <sensor_msgs/NavSatFix.h>
#include "sensor_msgs/Imu.h"

void IMUCallback(const sensor_msgs::Imu msg)
{
    ROS_INFO("IMU: [%f]", (float) msg.orientation.x);
    /*
    IMU data update here.
    */
}

void GPSCallback(const sensor_msgs::NavSatFix& msg)
{
    /*
    GPS data update here.
    */
    ROS_INFO("GPS data update");
}

/*
void ServoCallback(const std_msgs::Float32 msg)
{
    ROS_INFO("Servo: [%s]", msg.data)
    
    //Servo data update here.
}
*/

int main(int argc, char **argv)
{
    ros::init(argc, argv, "DataCollector");
    ros::NodeHandle nh;
    
    /// Publications
    ros::Publisher pub = nh.advertise<std_msgs::Float64MultiArray>("KalmanFilter", 100);
    
    /// Subscriptions
    ros::Subscriber sub = nh.subscribe("IMU", 1000, IMUCallback);
    ros::Subscriber subGPS = nh.subscribe("GPS", 1000, GPSCallback);
    //ros::Subscriber sub2 = n.subscribe("Servo", 1000, ServoCallback);
    
    ros::spin();
    
    return 0;
}

