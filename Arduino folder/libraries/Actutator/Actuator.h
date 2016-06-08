#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>


class Actuator {
	public:
		Actuator(int _pin):pin(_pin){}
		int getPin() { return pin; }
		virtual void actuate(bool) = 0;
	protected:
		int pin;
};



#endif