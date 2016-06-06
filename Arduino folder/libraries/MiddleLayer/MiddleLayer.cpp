#include <MiddleLayer.h>


void MiddleLayer::initCommunication(RF24 &radio, byte rxAddr[6], byte wxAddr[6]) {
	radioHelper.init(radio, rxAddr, wxAddr);
}

void MiddleLayer::sendMessage(RF24 &radio, Message &message) {
	radioHelper.sendMessage(radio, message);
}

Message MiddleLayer::receiveMessage(RF24 &radio) {
	Message message;
	message = radioHelper.receiveMessage(radio);
	return message; 
}

void MiddleLayer::initLayer() {
	actuators = LinkedList<Actuator*>();
	//more inits here
}

void MiddleLayer::actuate(Actuator* actuator, bool on) {
	actuator->actuate(on);
}