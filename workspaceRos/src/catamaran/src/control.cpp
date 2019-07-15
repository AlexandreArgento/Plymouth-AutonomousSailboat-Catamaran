#include <cstring>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>

std::string behaviour = "?";
float param1;
float param2;
float param3;

void control(std::string& behaviour)
{
    /* // Control calculation here, by modifying cmd, using the parameters param1 or param2 or param3
    switch(behaviour)
    {
        case "Return home":
            cmd.linear.x = ... ;
            cmd.linear.y = ... ;
            cmd.linear.z = ... ;
            break;
        case "Standby":
            cmd.linear.x = ... ;
            cmd.linear.y = ... ;
            cmd.linear.z = ... ;
            break;
        case "Field Following":
            cmd.linear.x = ... ;
            cmd.linear.y = ... ;
            cmd.linear.z = ... ;
    }
    */
}

void BehaviourCallback(const std_msgs::String& msg)
{
    // Update + Trigger
    
    switch(msg.data[0])
    {
        case 'R':
            behaviour = "Return home";
            break;
        case 'S':
            behaviour = "Standby";
            break;
        case 'F':
            behaviour = "Field Following";
    }
    
    ROS_INFO("Behaviour: [%s]", behaviour.c_str());
    
    control(behaviour);
}

void ParameterCallback(const geometry_msgs::Twist msg)
{
    // Update
    param1 = (float) msg.linear.x;
    param3 = (float) msg.linear.y;
    param2 = (float) msg.linear.z;
    ROS_INFO("Parameters: [%f], [%f], [%f]", param1, param2, param3);
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"control");
    ros::NodeHandle nh;
    
    /// Subscription
    ros::Subscriber sub = nh.subscribe("decision_msg", 1000, BehaviourCallback); // decision_msg updates behaviour and triggers the control calculation
    ros::Subscriber sub2 = nh.subscribe("decision_cmd", 1000, ParameterCallback); // decision_cmd updates the parameters
    
    /// Publication
    ros::Publisher pub = nh.advertise<std_msgs::String>("sailboat_msg", 100);
    ros::Publisher pub2 = nh.advertise<geometry_msgs::Twist>("sailboat_cmd", 100);
    std_msgs::String msg;
    geometry_msgs::Twist cmd;
    
    ros::Rate loop_rate(10);
    
    while (ros::ok())
    {
        msg.data = behaviour;
        pub.publish(msg);
        pub2.publish(cmd);
        
        loop_rate.sleep();
    }
    return 0;
}

