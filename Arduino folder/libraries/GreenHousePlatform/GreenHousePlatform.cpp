#include <GreenHousePlatform.h>

void GreenHousePlatform::init(RF24 &radio, byte rxAddr[6], byte wxAddr[6]) {
	
	radioHelper.init(radio, rxAddr, wxAddr);
	//more inits here
	
}

Message GreenHousePlatform::readSensorData() {
	
	Message message;
	
	return message; 
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