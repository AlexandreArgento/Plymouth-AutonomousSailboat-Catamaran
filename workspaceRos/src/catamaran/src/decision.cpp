#include <ros/ros.h>
#include "std_msgs/String.h"
#include <std_msgs/Float64MultiArray.h>
#include <geometry_msgs/Pose2D.h>
#include <geometry_msgs/Twist.h>

void WindCallback(const geometry_msgs::Pose2D& msg)
{
    /*
    Wind sensor data update here.
    */
    ROS_INFO("WindSensor: x=[%f] y=[%f] theta=[%f]", (float) msg.x, (float) msg.y, (float) msg.theta);
}

void KalmanCallback(const std_msgs::Float64MultiArray& msg)
{
    /*
    State vector update here.
    */
    ROS_INFO("State Vector update");
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"decision");
    ros::NodeHandle nh;
    
    /// Subscription
    ros::Subscriber subWS = nh.subscribe("WindSensorFiltered", 1000, WindCallback);
    ros::Subscriber subKF = nh.subscribe("KalmanFilter", 1000, KalmanCallback);
    
    /// Publication
    ros::Publisher pub = nh.advertise<std_msgs::String>("decision_msg", 100);
    ros::Publisher pub2 = nh.advertise<geometry_msgs::Twist>("decision_cmd", 100);
    std_msgs::String behaviour;
    geometry_msgs::Twist parameters;
    behaviour.data = "";
    
    ros::Rate loop_rate(10);
    
    while (ros::ok())
    {
        pub.publish(behaviour);
        pub2.publish(parameters);
        loop_rate.sleep();
    }
    return 0;
}

