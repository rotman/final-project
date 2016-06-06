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

void LowerLayer::initLayer(int address) {
	this->address = address;
	sensors = LinkedList<Sensor*>();
	actuators = LinkedList<Actuator*>();
	//more inits here
}

void LowerLayer::addSensor(Sensor* sensor) {
	sensors.add(sensor);
}

void LowerLayer::removeSensor(int id) {
	for (int i = 0; i < sensors.size(); i++) {
		if (actuators.get(i)->getId() == id) {
			sensors.remove(i);
			break;
		}
	}
}

void LowerLayer::addActuator(Actuator* actuator) {
	actuators.add(actuator);
}

void LowerLayer::removeActuator(int id) {
	for (int i = 0; i < actuators.size(); i++) {
		if (actuators.get(i)->getId() == id) {
			actuators.remove(i);
			break;
		}
	}
}

LinkedList<Message> LowerLayer::readSensorsData() {
	LinkedList<Message> messages = LinkedList<Message>();
	CommonValues commonValues;
	for (int i = 0; i < sensors.size(); i++) {
		if (sensors.get(i)->getId() == commonValues.humidityTemperatureSensorId) {
			messages.add(sensors.get(i)->readSensorData(true));
		}
		else {
			messages.add(sensors.get(i)->readSensorData(false));
		}
	}
	return messages; 
}

void LowerLayer::actuate(Actuator* actuator, bool on) {
	actuator->actuate(on);
}

void LowerLayer::onSensorFail() {
	
}

