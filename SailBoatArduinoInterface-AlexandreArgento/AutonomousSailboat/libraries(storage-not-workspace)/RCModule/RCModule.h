#ifndef RC_SENSOR_H
#define RC_SENSOR_H

#include <Sensor.h>
#include <Helper.h>

class RC : public Sensor
{
public:
	RC() : controlling(false), previousController(RETURNHOME_CONTROLLER), Sensor(0), rc_sail(0), rc_rudder(0)
    {
		for(int i = 0; i < 6; ++i)
        {
			rc_values[i] = 0; rc_start[i] = 0;
		}
		offsetmin[RC_CHANNEL_1] = RC_1_MIN;
		offsetmax[RC_CHANNEL_1] = RC_1_MAX;
		offsetmin[RC_CHANNEL_2] = RC_2_MIN;
		offsetmax[RC_CHANNEL_2] = RC_2_MAX;
		offsetmin[RC_CHANNEL_3] = RC_3_MIN;
		offsetmax[RC_CHANNEL_3] = RC_3_MAX;
		offsetmin[RC_CHANNEL_4] = RC_4_MIN;
		offsetmax[RC_CHANNEL_4] = RC_4_MAX;
		offsetmin[RC_CHANNEL_5] = RC_5_MIN;
		offsetmax[RC_CHANNEL_5] = RC_5_MAX;
		offsetmin[RC_CHANNEL_6] = RC_6_MIN;
		offsetmax[RC_CHANNEL_6] = RC_6_MAX;
	}
	
	void init() {}
	void updateMeasures();
	void communicateData() {}
	
	//void interruptCH(uint8_t channel, uint8_t pin);
	uint16_t getRawValue(uint8_t channel) {
    /*
    if(channel < RC_NUM_CHANNELS) return rc_values[channel];}
    {
        return rc_values[channel];
    }
    */
    if(channel == 0) {return rc_rudder;}
    if(channel == 2) {return rc_sail;}
}

	uint16_t getValue(uint8_t channel) {
    /*
    if(channel < RC_NUM_CHANNELS) return rc_values[channel];}
    {
        return rc_values[channel];
    }
    */
    if(channel == 0) {return rc_rudder;}
    if(channel == 2) {return rc_sail;}
}
	bool controlling;
	
private:
	uint16_t rc_values[6];
    uint16_t rc_sail;
    uint16_t rc_rudder;
	uint16_t rc_start[6];
	
	unsigned int offsetmin[6];
	unsigned int offsetmax[6];
	
	int previousController;
};

#endif
