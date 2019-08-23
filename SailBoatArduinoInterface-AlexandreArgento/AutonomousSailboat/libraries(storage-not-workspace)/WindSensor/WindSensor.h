#ifndef WIND_SENSOR_H
#define WIND_SENSOR_H

#include <Sensor.h>
#include <geometry_msgs/Pose2D.h>

#ifndef HARDWARE_TUNING
#define WIND_SENSOR_OFFSET 198  // May need to be tuned!
                                     // value which gives the zero angle
           							             // Manual tuning does not works, so I chose software tuning
#endif

#define ANGLE_MAX 360
#define ANGLE_MIN 0

class WindSensor : public SensorROS
{
	public:
		WindSensor() : SensorROS("WindSensor", &msg), angle(0), windSpeed(0) {}
		void init(ros::NodeHandle* n);
		void updateMeasures();
		void communicateData();
		
	private:
		double angle;
        double windSpeed;
        
		geometry_msgs::Pose2D msg;
};

#endif
