#include <RCModule.h>
#include <Arduino.h>
#include <Sailboat.h>

void RC::updateMeasures() 
{
    uint16_t duration;
    uint16_t control = 0;
    
    // Rudder:
    duration = pulseIn(RC_PIN_1, HIGH);
    if (duration == 0) {control = 0;}
    //else {control = mapf(duration,RC_1_MIN,RC_1_MAX,175,510);}
    else {control = mapf(duration,RC_1_MIN,RC_1_MAX,220,390);}
    //rc_rudder = control;
    
    // Sail:
    duration = pulseIn(RC_PIN_3, HIGH);
    if (duration == 0) {control = 0;}
    //else {control = mapf(duration,RC_3_MIN,RC_3_MAX,220,390);}
    else {control = mapf(duration,RC_3_MIN,RC_3_MAX,175,510);}
    //Serial.println("ok");
    //rc_sail = control;
}


/*
void RC::interruptCH(uint8_t channel, uint8_t pin)
{
    uint16_t control;
    uint16_t duration = pulseIn(pin, HIGH);
    
    if (channel == 0)
    {
        control = map(duration,RC_1_MIN,RC_1_MAX,175,510);
        Sailboat::Instance()->getRudder()->RCCommand(control);
    }
    
    if (channel == 2)
    {
        control = map(duration,RC_3_MIN,RC_3_MAX,220,390);
        Sailboat::Instance()->getSail()->RCCommand(control);
    }
    rc_values[channel] = control;
    
    //Sailboat::Instance()->setController(RC_CONTROLLER);
}
*/
