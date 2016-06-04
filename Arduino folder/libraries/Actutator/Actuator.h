#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>


class Actuator {
	public:
		virtual void actuate(bool) = 0;
};



#endif