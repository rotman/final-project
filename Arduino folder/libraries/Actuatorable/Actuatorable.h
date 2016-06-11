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
		virtual Actuator* findActuatorById(int) = 0;
	protected:
		LinkedList<Actuator*> actuatorsArray;

};

#endif
