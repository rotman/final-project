#include <GreenHousePlatform.h>

void GreenHousePlatform::init(RF24 &radio, byte rxAddr[6], byte wxAddr[6]) {
	
	radioHelper.init(radio, rxAddr, wxAddr);
	sensors = LinkedList<Sensor*>();
	//more inits here
	
}

void GreenHousePlatform::addSensor(Sensor* sensor) {
	sensors.add(sensor);
}

LinkedList<Message> GreenHousePlatform::readSensorsData() {
	LinkedList<Message> messages = LinkedList<Message>();
	for (int i = 0; i < sensors.size(); i++) {
		messages.add(sensors.get(i)->readSensorData(false));
	}
	return messages; 
}

void GreenHousePlatform::sendMessage(RF24 &radio, Message &message) {
	
	radioHelper.sendMessage(radio, message);
}

Message GreenHousePlatform::receiveMessage(RF24 &radio) {
	
	Message message;
	message = radioHelper.receiveMessage(radio);
	return message; 
}

void GreenHousePlatform::actuate() {
	
	
}

void GreenHousePlatform::onSensorFail() {
	
	
}