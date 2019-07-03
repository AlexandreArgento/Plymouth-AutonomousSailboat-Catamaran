
#include <ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Empty.h>

#include "I2Cdev.h"

#include <Sailboat.h>
#include "Standby.h"

#define EI_NOTPORTB
#define EI_NOTPORTJ
#define EI_NOTEXTERNAL
#include <EnableInterrupt.h>


///////////
/// ROS ///
///////////

ros::NodeHandle nh;

ros::Subscriber<geometry_msgs::Twist, Sailboat> sub("sailboat_cmd", &Sailboat::cmdCallback, Sailboat::Instance());
ros::Subscriber<std_msgs::String, Sailboat> sub2("sailboat_msg", &Sailboat::msgCallback, Sailboat::Instance());


////////////
/// Data ///
////////////

const char signature [] = "Sailboat";
char * p = (char *) malloc (sizeof (signature));


/////////////////
/// Functions ///
/////////////////

void setControllers()
{
  Controller* controllers[NB_CONTROLLERS];
  controllers[STANDBY_CONTROLLER] = new Standby();/*
  controllers[RUDDERSAIL_CONTROLLER] = new RudderSail();
  controllers[RETURNHOME_CONTROLLER] = new ReturnHome();
  controllers[HEADER_CONTROLLER] = new Header();
  controllers[RC_CONTROLLER] = new RCControl();
  controllers[SAILCAP_CONTROLLER] = new SailCap();
  controllers[RUDDER_CONTROLLER] = new RudderControl();*/

  Sailboat::Instance()->setControllers(controllers);
  Sailboat::Instance()->setController(STANDBY_CONTROLLER);
}


#ifdef WIND_ANEMOMETER_PIN
void AnemometerReading() 
{
  Sailboat::Instance()->getWindSensor()->updateAnemometer();
}
#endif

/////////////////////
/// Interruptions ///
/////////////////////
/*
void intCH1()
{
  Sailboat::Instance()->getRC()->interruptCH(RC_1, RC_PIN_1);
}

void intCH2()
{
  Sailboat::Instance()->getRC()->interruptCH(RC_2, RC_PIN_2);
}

void intCH3()
{
  Sailboat::Instance()->getRC()->interruptCH(RC_3, RC_PIN_3);
}

void intCH4()
{
  Sailboat::Instance()->getRC()->interruptCH(RC_4, RC_PIN_4);
}

void intCH5()
{
  Sailboat::Instance()->getRC()->interruptCH(RC_5, RC_PIN_5);
}

void intCH6()
{
  Sailboat::Instance()->getRC()->interruptCH(RC_6, RC_PIN_6);
}


void setRCInterrupts()
{
  pinMode(RC_PIN_1, INPUT);
  pinMode(RC_PIN_2, INPUT);
  pinMode(RC_PIN_3, INPUT);
  pinMode(RC_PIN_4, INPUT);
  pinMode(RC_PIN_5, INPUT);
  pinMode(RC_PIN_6, INPUT);
  enableInterrupt(RC_PIN_1, intCH1, CHANGE);
  enableInterrupt(RC_PIN_2, intCH2, CHANGE);
  enableInterrupt(RC_PIN_3, intCH3, CHANGE);
  enableInterrupt(RC_PIN_4, intCH4, CHANGE);
  enableInterrupt(RC_PIN_5, intCH5, CHANGE);
  enableInterrupt(RC_PIN_6, intCH6, CHANGE);
}
*/

/////////////
/// Setup ///
/////////////

void setup()
{
  //Serial.begin(115200);
  //Logger::Instance()->MessagesSetup();

  nh.getHardware()->setBaud(115200);
  nh.initNode();
  
  nh.subscribe(sub);
  nh.subscribe(sub2);

  
  Sailboat::Instance()->init(&nh);
  
  
  delay(100);
  
  
  setControllers();
  //setRCInterrupts();
  
#ifdef WIND_ANEMOMETER_PIN
  attachInterrupt(digitalPinToInterrupt(WIND_ANEMOMETER_PIN), AnemometerReading, FALLING);
#endif
  
  delay(10);
}

////////////
/// Loop ///
////////////

void loop()
{
  Sailboat::Instance()->updateSensors();
  //Logger::Instance()->Update();
  Sailboat::Instance()->communicateData();
  Sailboat::Instance()->Control();

  nh.spinOnce();
  delay(4);
}
