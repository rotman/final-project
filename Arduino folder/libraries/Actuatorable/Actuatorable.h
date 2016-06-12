#ifndef ACTUATORABLE
#define ACTUATORABLE

#include <Arduino.h>
#include <Actuator.h>
#include <LinkedList.h>

class Actuatorable {
	public:
		virtual ~Actuatorable() {}
		void addActuator(Actuator* actuator) {
			actuatorsArray.add(actuator);
		}
		
		void removeActuator(int pin) {
			for (int i = 0; i < actuatorsArray.size(); i++) {
				if (actuatorsArray.get(i)->getPin() == pin) {
					actuatorsArray.remove(i);
					break;
				}
			}
		}
		
		Actuator* findActuatorById(int pin) {
			for (int i = 0; i < actuatorsArray.size(); i++) {
				if (actuatorsArray.get(i)->getPin() == pin) {
					return actuatorsArray.get(i);
				}
			}
		}
		
	protected:
		LinkedList<Actuator*> actuatorsArray = LinkedList<Actuator*>();

};

#endif
