#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>


class Actuator {
	public:
		Actuator(int id) {
			this->id = id;
		}
		
		int getId() {
			return id;
		}
		
		virtual void actuate(bool) = 0;
	protected:
		int id;
};



#endif