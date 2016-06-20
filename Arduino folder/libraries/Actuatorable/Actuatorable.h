#ifndef ACTUATORABLE
#define ACTUATORABLE

#include <Arduino.h>
#include <Actuator.h>
#include <LinkedList.h>

class Actuatorable {
	public:
		virtual ~Actuatorable() {}


		void addActuator(Actuator* actuator) {
			actuatorsList.add(actuator);
		}
		
		void removeActuator(int pin) {
			for (int i = 0; i < actuatorsList.size(); i++) {
				if (actuatorsList.get(i)->getPin() == pin) {
					actuatorsList.remove(i);
					break;
				}
			}
		}
		
		Actuator* findActuatorById(int pin) {
			for (int i = 0; i < actuatorsList.size(); i++) {
				if (actuatorsList.get(i)->getPin() == pin) {
					return actuatorsList.get(i);
				}
			}
		}
		LinkedList<Actuator*>& getActuatorsList() {
			return this->actuatorsList;
		}
		
	protected:
		LinkedList<Actuator*> actuatorsList;

};

#endif
