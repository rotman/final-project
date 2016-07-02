#ifndef ACTUATORABLE
#define ACTUATORABLE

#include <Arduino.h>
#include <Actuator.h>
#include <LinkedList.h>

class Actuatorable {
	public:
		virtual ~Actuatorable() {}

		void addActuator(Actuator* actuator);

		void removeActuator(int);

		Actuator* findActuatorById();
	
		LinkedList<Actuator*>& getActuatorsList();

};

#endif
