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
			int size = actuatorsList.size();
			for (int i = 0; i < size; i++) {
				if (actuatorsList.get(i)->getPin() == pin) {
					actuatorsList.remove(i);
					break;
				}
			}
		}

		Actuator* findActuatorById(int pin) {
			int size = actuatorsList.size();
			for (int i = 0; i < size; ++i) {
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
