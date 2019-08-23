#include <WindSensor.h>

void WindSensor::init(ros::NodeHandle* n)
{
    /*
	pinMode(WIND_SENSOR_PIN, INPUT);
#ifdef WIND_ANEMOMETER_PIN
	pinMode(WIND_ANEMOMETER_PIN, INPUT); 
#endif
    */
    SensorROS::init(n);
}

void WindSensor::updateMeasures()
{
	angle = 0;
    windSpeed = 0;
}

void WindSensor::communicateData()
{
    msg.x = 0;
    msg.y = 0;
    /*
#ifdef WIND_ANEMOMETER_PIN
	msg.x = windSpeed*cos(angle*2*3.141596/360);
	msg.y = windSpeed*sin(angle*2*3.141596/360);
#endif
    */
    /*
	msg.theta = angle*DEG_TO_RAD;
	*/
	pub.publish(&msg);
    
    /// ROS INFO
/*
    char message[4] = "WS!";
    nh->loginfo(message);
*/
}
