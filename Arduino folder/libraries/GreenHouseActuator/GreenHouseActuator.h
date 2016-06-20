#ifndef GREEN_HOUSE_ACTUATOR
#define GREEN_HOUSE_ACTUATOR

#include <Arduino.h>
#include <Actuator.h>
#include <CommonValues.h>


class GreenHouseActuator :public Actuator{
	public:	
		GreenHouseActuator(int);
		void actuate(bool);
};



#endif