#ifndef GREEN_HOUSE_ACTUATOR
#define GREEN_HOUSE_ACTUATOR

#include <Actuator.h>
#include <Arduino.h>

class GreenHouseActuator : public Actuator {
public:
	GreenHouseActuator(int);
	void actuate(bool);
};


#endif