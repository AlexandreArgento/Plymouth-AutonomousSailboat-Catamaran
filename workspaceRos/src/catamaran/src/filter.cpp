#include <ros/ros.h>
#include <geometry_msgs/Pose2D.h>

void WindCallback(const geometry_msgs::Pose2D msg)
{
    ROS_INFO("WindSensor: x=[%f] y=[%f] theta=[%f]", (float) msg.x, (float) msg.y, (float) msg.theta);
    /*
    filter treatment here: msgfilt = filter(msg)
    */
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "filter");
    ros::NodeHandle nh;
    
    ros::Subscriber sub = nh.subscribe("WindSensor", 1000, WindCallback);
    
    ros::Publisher pub = nh.advertise<geometry_msgs::Pose2D>("WindSensorFiltered", 100);
    geometry_msgs::Pose2D msgfilt;
    msgfilt.x = 0.0;
    msgfilt.y = 0.0;
    msgfilt.theta = 0.0;
    
    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        pub.publish(msgfilt);
        loop_rate.sleep();
    }
    return 0;
}

