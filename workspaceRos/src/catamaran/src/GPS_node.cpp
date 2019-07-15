#include <ros/ros.h>
#include <sensor_msgs/NavSatFix.h>

void Update(sensor_msgs::NavSatFix& GPSmsg)
{
    /// main GPS data extraction here
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"GPS_node");
    ros::NodeHandle nh;
    
    ros::Publisher pub = nh.advertise<sensor_msgs::NavSatFix>("GPS", 100);
    sensor_msgs::NavSatFix GPSmsg;
    
    ros::Rate loop_rate(10);
    
    while (ros::ok())
    {
        Update(GPSmsg);
        pub.publish(GPSmsg);
        loop_rate.sleep();
    }
    return 0;
}

