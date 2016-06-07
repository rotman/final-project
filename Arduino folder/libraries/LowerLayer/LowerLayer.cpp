#include <LowerLayer.h>


void LowerLayer::initCommunication(RF24 &radio, int readingAddress, int writingAddress) {
	radioHelper.init(radio, readingAddress, writingAddress);
}

void LowerLayer::sendMessage(RF24 &radio, Message &message) {
	Serial.println(" LowerLayer::sendMessage called");
	radioHelper.sendMessage(radio, message);
	Serial.println(" LowerLayer::sendMessage returned");
}

Message LowerLayer::receiveMessage(RF24 &radio) {
	Message message = radioHelper.receiveMessage(radio);
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
		Message newMessage;
		if (sensors.get(i)->getId() == commonValues.humidityTemperatureSensorId) {
			newMessage = sensors.get(i)->readSensorData(true);
		}
		else {
			newMessage = sensors.get(i)->readSensorData(false);
		}
		messages.add(newMessage);
	}
	return messages; 
}

void LowerLayer::actuate(Actuator* actuator, bool on) {
	actuator->actuate(on);
}

void LowerLayer::onSensorFail() {
	
}

