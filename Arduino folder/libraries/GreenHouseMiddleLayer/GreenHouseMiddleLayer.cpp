#include <GreenHouseMiddleLayer.h>



void GreenHouseMiddleLayer::initLayer(int address) {
	this->address = address;
	actuators = LinkedList<Actuator*>();
	//more inits here
}

void GreenHouseMiddleLayer::addActuator(Actuator* actuator) {
	actuators.add(actuator);
}

void GreenHouseMiddleLayer::removeActuator(int pin) {
	for (int i = 0; i < actuators.size(); i++) {
		if (actuators.get(i)->getPin() == pin) {
			actuators.remove(i);
			break;
		}
	}
}

void GreenHouseMiddleLayer::actuate(Actuator* actuator, bool on) {
	actuator->actuate(on);
}



void GreenHouseMiddleLayer::getTime() {
	//TODO
}
