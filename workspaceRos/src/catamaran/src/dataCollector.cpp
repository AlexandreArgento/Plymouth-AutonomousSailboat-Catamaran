#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include "sensor_msgs/Imu.h"

void IMUCallback(const sensor_msgs::Imu msg)
{
    ROS_INFO("IMU: [%f]", (float) msg.orientation.x);
}
/*
void ServoCallback(const std_msgs::Float32 msg)
{
    ROS_INFO("Servo: [%s]", msg.data)
}
*/
int main(int argc, char **argv)
{
    ros::init(argc, argv, "DataCollector");
    ros::NodeHandle nh;
    
    ros::Subscriber sub = nh.subscribe("IMU", 1000, IMUCallback);
    //ros::Subscriber sub2 = n.subscribe("Servo", 1000, ServoCallback);
    
    ros::spin();
    
    return 0;
}

