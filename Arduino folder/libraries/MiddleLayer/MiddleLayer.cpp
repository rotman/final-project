#include <MiddleLayer.h>


void MiddleLayer::initCommunication(RF24 &radio, byte rxAddr[6], byte wxAddr[6]) {
	radioHelper.init(radio, rxAddr, wxAddr);
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
	startClock();
	//more inits here
}

void MiddleLayer::addActuator(Actuator* actuator) {
	actuators.add(actuator);
}

void MiddleLayer::removeActuator(int id) {
	for (int i = 0; i < actuators.size(); i++) {
		if (actuators.get(i)->getId() == id) {
			actuators.remove(i);
			break;
		}
	}
}

void MiddleLayer::actuate(Actuator* actuator, bool on) {
	actuator->actuate(on);
}

void MiddleLayer::startClock() {
	//	TODO
}

void MiddleLayer::getTime() {
	//TODO
}