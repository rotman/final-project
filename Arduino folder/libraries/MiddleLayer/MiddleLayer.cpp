#include <MiddleLayer.h>


void MiddleLayer::initCommunication(RF24 &radio, int readingAddress, int writingAddress) {
	radioHelper.init(radio, readingAddress, writingAddress);
}

void MiddleLayer::sendMessage(RF24 &radio, Message &message) {
	radioHelper.sendMessage(radio, message);
}

Message MiddleLayer::receiveMessage(RF24 &radio) {
	Message message = radioHelper.receiveMessage(radio);
	return message; 
}

void MiddleLayer::initLayer(int address) {
	this->address = address;
	actuators = LinkedList<Actuator*>();
	//more inits here
}

void MiddleLayer::addActuator(Actuator* actuator) {
	actuators.add(actuator);
}

void MiddleLayer::removeActuator(int pin) {
	for (int i = 0; i < actuators.size(); i++) {
		if (actuators.get(i)->getPin() == pin) {
			actuators.remove(i);
			break;
		}
	}
}

void MiddleLayer::actuate(Actuator* actuator, bool on) {
	actuator->actuate(on);
}



void MiddleLayer::getTime() {
	//TODO
}