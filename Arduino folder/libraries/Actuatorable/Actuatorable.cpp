
#include <Actuatorable.h>



void Actuatorable::addActuator(Actuator* actuator) {
	actuatorsList.add(actuator);
}

void Actuatorable::removeActuator(int pin) {
	int size = actuatorsList.size();
	for (int i = 0; i < size; i++) {
		if (actuatorsList.get(i)->getPin() == pin) {
			actuatorsList.remove(i);
			break;
		}
	}
}

Actuator* Actuatorable::findActuatorById(int pin) {
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


