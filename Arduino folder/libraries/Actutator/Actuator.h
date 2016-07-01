#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>
#include <Actions.h>

class Actuator {
	public:
		Actuator(int _pin):pin(_pin){
			pinMode(_pin,OUTPUT);
		}
		int getPin() { return pin; }
		virtual Actions actuate(boolean) = 0;
	protected:
		int pin;
};



#endif