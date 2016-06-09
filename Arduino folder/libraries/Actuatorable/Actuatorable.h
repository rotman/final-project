#ifndef ACTUATORABLE
#define ACTUATORABLE

#include <Arduino.h>
#include <Actuator.h>
#include <LinkedList.h>

class Actuatorable {
	public:
		virtual ~Actuatorable() {}
		virtual void addActuator(Actuator*) = 0;
		virtual void removeActuator(int) = 0;
		virtual void actuate(int, bool) = 0;
	private:
		LinkedList<Actuator*> actuatorsArray;

};

#endif