#ifndef CONFIG_H
#define CONFIG_H


/**********************************************ID********************************************/
/**SENSORS**/
/***********/
#define NB_SENSORS		1

#define SENSOR_WINDSENSOR	1
//#define SENSOR_GPS		2
#define SENSOR_IMU			0
//#define SENSOR_BATTERY      3

#define NB_SENSORS_NOT_ROS		0

#define SENSOR_RC			0

/**ACTUATORS**/
/***********/
#define NB_ACTUATORS		2

#define ACTUATOR_RUDDER		0
#define ACTUATOR_SAIL		1

/**********************************************PINS********************************************/
//WIND
//#define WIND_ANEMOMETER_PIN 3


/*****************************************CONFIGURATION****************************************/
/**CONFIG**/
/**********/
//WIND
#define WIND_SENSOR_MIN 48
#define WIND_SENSOR_MAX 990

//RUDDER
#define RUDDER_POS_MIN  175
#define RUDDER_POS_NEUTRAL  350
#define RUDDER_POS_MAX  510

#define RUDDER_MIN  -90
#define RUDDER_NEUTRAL  0
#define RUDDER_MAX  90

//SAIL
#define WINCH_ANGLE_MIN 220
#define WINCH_ANGLE_NEUTRAL WINCH_ANGLE_MIN
#define WINCH_ANGLE_MAX 390
#define WINCH_DIAMETER 23 // in mm

#define SAIL_MIN 0
#define SAIL_NEUTRAL SAIL_MIN
#define SAIL_MAX 90

#endif
