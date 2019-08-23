#include "RCControl.h"
#include <Sailboat.h>

RCControl::RCControl() {}

void RCControl::init() {}

void RCControl::Control(const geometry_msgs::Twist& cmd)
{
  //Serial.println("Standby");
    uint16_t commandSail = Sailboat::Instance()->getRC()->getValue(RC_SAIL);
    uint16_t commandRudder = Sailboat::Instance()->getRC()->getValue(RC_RUDDER);
    if (commandSail!=0 and commandRudder!=0)
    {
      /*Serial.println("RC Control");/*
      Serial.println("Sail:");
      Serial.println(commandSail);
      Serial.println("Rudder:");
      Serial.println(commandRudder);
      */
      //Sailboat::Instance()->getSail()->RCCommand(commandSail);
      Sailboat::Instance()->getRudder()->RCCommand(commandRudder);
    }
    else
    {
      Sailboat::Instance()->setController(Sailboat::Instance()->PREVIOUS_CONTROLLER);
    }
    
    //Sailboat::Instance()->resetWatchdogROS();
}
