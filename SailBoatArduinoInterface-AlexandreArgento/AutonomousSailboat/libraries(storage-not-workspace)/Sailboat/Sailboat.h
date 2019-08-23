#ifndef SAILBOAT_H
#define SAILBOAT_H

#include <config-Sailboat.h>

#include <Servo_Motor.h>

#include <IMU.h>
#include <RCModule.h>
#include <WindSensor.h>

#include <Controller.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>

class Sailboat
{
public:
	Sailboat() : controller(NULL), pubMsg("sailboat_log", &sailboatmsgs), watchdog(0), watchdogROS(0), timerMillis(0), timerMillisCOM(0), timerMillisCOMAct(0)
    {
        controllerNames[STANDBY_CONTROLLER] = "Standby";
    }
	~Sailboat();
	
	void init(ros::NodeHandle* n);
	void updateSensors();
	void communicateData();
	
	//WindSensor* getWindSensor() {return (WindSensor*)sensors[SENSOR_WINDSENSOR];}
	//GPS* getGPS() {return (GPS*)sensors[SENSOR_GPS];}
	//XSens* getIMU() {return (XSens*)sensors[SENSOR_IMU];}
    //BatterySensor* getBattery() {return (BatterySensor*)sensors[SENSOR_BATTERY];}
	
	RC* getRC() {return (RC*)sens[SENSOR_RC];}
	
	Servo_Motor* getRudder() {return (Servo_Motor*)actuators[ACTUATOR_RUDDER];}
	Servo_Motor* getSail() {return (Servo_Motor*)actuators[ACTUATOR_SAIL];}
#ifdef ACTUATOR_RUDDER2
	Servo_Motor* getRudder2() {return (Servo_Motor*)actuators[ACTUATOR_RUDDER2];}
#endif
	
	void setController(Controller* control);
    void setController(int index);
	void setControllers(Controller** control) {controllers = control;}
	int actualControllerIndex() {return actualControllerI;}
	Controller* actualController() {return controller;}
	
	void Control();
    
	void cmdCallback(const geometry_msgs::Twist& msg);
	void msgCallback(const std_msgs::String& msg);
    
    void publishMsg(String msg);
    void publishMsg(const char* msg);
    
    void resetWatchdogROS() {watchdogROS = millis();}
    
	static Sailboat* Instance() {if(sailboat == NULL) sailboat = new Sailboat(); return sailboat;}
    int PREVIOUS_CONTROLLER;
	int actualControllerI;
private:
	static Sailboat* sailboat;
	
	Controller** controllers;
	Controller* controller;
	SensorROS* sensors[NB_SENSORS];
	Sensor* sens[NB_SENSORS_NOT_ROS];
	ActuatorROS* actuators[NB_ACTUATORS];
	
    ros::NodeHandle* nh;
    
	geometry_msgs::Twist cmd;
    
    ros::Publisher pubMsg;
    std_msgs::String sailboatmsgs;
	
	unsigned long watchdog;
	unsigned long watchdogROS;
	
	unsigned long timerMillis;
	unsigned long timerMillisCOM;
	unsigned long timerMillisCOMAct;
	
	const char* controllerNames[NB_CONTROLLERS];
};

#endif
