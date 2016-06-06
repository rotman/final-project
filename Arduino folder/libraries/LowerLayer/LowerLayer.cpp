#include <LowerLayer.h>


void LowerLayer::initCommunication(RF24 &radio, byte rxAddr[6], byte wxAddr[6]) {
	radioHelper.init(radio, rxAddr, wxAddr);
}

void LowerLayer::sendMessage(RF24 &radio, Message &message) {
	radioHelper.sendMessage(radio, message);
}

Message LowerLayer::receiveMessage(RF24 &radio) {
	Message message;
	message = radioHelper.receiveMessage(radio);
	return message; 
}

void LowerLayer::initLayer() {
	sensors = LinkedList<Sensor*>();
	actuators = LinkedList<Actuator*>();
	//more inits here
}

void LowerLayer::addSensor(Sensor* sensor) {
	sensors.add(sensor);
}

void LowerLayer::removeSensor(Sensor* sensor) {
	for (int i = 0; i < sensors.size(); i++) {
		if (sensors.get(i) == sensor) {
			sensors.remove(i);
			break;
		}
	}
}

LinkedList<Message> LowerLayer::readSensorsData() {
	LinkedList<Message> messages = LinkedList<Message>();
	for (int i = 0; i < sensors.size(); i++) {
		messages.add(sensors.get(i)->readSensorData(false));
	}
	return messages; 
}

void LowerLayer::actuate(Actuator* actuator, bool on) {
	actuator->actuate(on);
}

void LowerLayer::onSensorFail() {
	
}

