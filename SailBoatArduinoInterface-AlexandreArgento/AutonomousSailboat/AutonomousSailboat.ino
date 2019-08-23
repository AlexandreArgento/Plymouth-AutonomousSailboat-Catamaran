
/// ROS libraries inclusion
#include <ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Empty.h>

/// Arduino libraries inclusion
#include "I2Cdev.h"
//#include <EnableInterrupt.h>

/// Class librairies inclusion
#include <Sailboat.h>

/// Controllers inclusion
#include "Standby.h"
#include "RCControl.h"

/*
#define EI_NOTPORTB
#define EI_NOTPORTJ
#define EI_NOTEXTERNAL
*/


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
  controllers[STANDBY_CONTROLLER] = new Standby();
  //controllers[RUDDERSAIL_CONTROLLER] = new RudderSail();
  //controllers[RETURNHOME_CONTROLLER] = new ReturnHome();
  //controllers[HEADER_CONTROLLER] = new Header();
  controllers[RC_CONTROLLER] = new RCControl();
  //controllers[SAILCAP_CONTROLLER] = new SailCap();
  //controllers[RUDDER_CONTROLLER] = new RudderControl();

  Sailboat::Instance()->setControllers(controllers);
  Sailboat::Instance()->setController(STANDBY_CONTROLLER);
}


#ifdef WIND_ANEMOMETER_PIN
void AnemometerReading() 
{
  Sailboat::Instance()->getWindSensor()->updateAnemometer();
}
#endif
/*
bool RC_Activated()
{
  int16_t val = Sailboat::Instance()->getRC()->getValue(RC_SAIL);
  if (val != 0 and val < 10000) {return true;}
  else {return false;}
}
*/

double duration1 = 0;
double duration3 = 0;
double control = 0;
void RCcontrol()
{
  duration1 = pulseIn(RC_PIN_1, HIGH);
  duration3 = pulseIn(RC_PIN_3, HIGH);
  
  if (duration1 == 0) {control = 0;}
  else {control = mapf(duration1,RC_1_MIN,RC_1_MAX,220,390);}
  
  if (control != 0)
  {
    Sailboat::Instance()->getRudder()->applyCommand(control);
    Serial.println("Rudder");
    Serial.println(control);
    delay(1000);
  }
  
  if (duration3 == 0) {control = 0;}
  else {control = mapf(duration3,RC_3_MIN,RC_3_MAX,175,510);}

  if (control != 0)
  {
    Sailboat::Instance()->getSail()->applyCommand(control);
    Serial.println("Sail");
    Serial.println(control);
    delay(1000);
  }
}

/////////////////////
/// Interruptions ///
/////////////////////
/*
void intCH1() // Rudder RC command
{
  Serial.println("int1");

  if (duration1 == 0) {control = 0;}
  else {control = mapf(duration1,RC_1_MIN,RC_1_MAX,220,390);}

  Sailboat::Instance()->getRudder()->applyCommand(control);
}

void intCH3() // Sail RC command
{
  Serial.println("int3");
  
  if (duration3 == 0) {control = 0;}
  else {control = mapf(duration3,RC_3_MIN,RC_3_MAX,175,510);}

  Sailboat::Instance()->getSail()->applyCommand(control);
}

void setRCInterrupts()
{
  pinMode(RC_PIN_1, INPUT_PULLUP);
  pinMode(RC_PIN_3, INPUT_PULLUP);
  //enableInterrupt(RC_PIN_1, intCH1, CHANGE);
  //enableInterrupt(RC_PIN_3, intCH3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RC_PIN_1), intCH1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RC_PIN_3), intCH3, CHANGE);
}
*/

/////////////
/// Setup ///
/////////////

void setup()
{
  Serial.begin(115200);
  //Logger::Instance()->MessagesSetup();

  nh.getHardware()->setBaud(115200);
  nh.initNode();
  
  nh.subscribe(sub);
  nh.subscribe(sub2);
  
  
  Sailboat::Instance()->init(&nh);
  
  delay(100);
  
  //setRCInterrupts();
  Serial.println("setup");
  
  setControllers();
  
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
  Serial.println("");
  Serial.println("loop in");
  
  RCcontrol();
  
  Sailboat::Instance()->updateSensors();
  //Logger::Instance()->Update();
  //Sailboat::Instance()->communicateData();
  Sailboat::Instance()->Control();
  
  nh.spinOnce();
  delay(4);
  Serial.println("loop out");
}
