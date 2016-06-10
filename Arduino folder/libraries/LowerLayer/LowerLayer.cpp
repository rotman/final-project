#include <LowerLayer.h>
/*
implement: 
virtual void analyze() = 0;
virtual void decodeMessage() = 0;
virtual S prepareMessage(S, int) = 0;
virtual void sendMessage(E&, S&) = 0;
virtual S receiveMessage(E&) = 0;
virtual void addActuator(Actuator*) = 0;
virtual void removeActuator(int) = 0;
virtual void actuate(int, bool) = 0;
virtual void addSensor(Sensor*) = 0;
virtual void removeSensor(int) = 0;
virtual LinkedList<S> readSensorsData() = 0;
virtual void onSensorFail() = 0;
*/
Actuator* LowerLayer::findActuatorById(int){}

void LowerLayer::decodeMessage(){}
void LowerLayer::analyze(){}
Message LowerLayer::prepareMessage(Message, int) {}
void LowerLayer::initLayer(int address) {
	this->address = address;
	sensorsArray = LinkedList<Sensor*>();
	actuatorsArray = LinkedList<Actuator*>();
	//more inits here , think maybe to move the inits to relevant constractors
}

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

void LowerLayer::addSensor(Sensor* sensor) {
	sensorsArray.add(sensor);
}

void LowerLayer::removeSensor(int pin) {
	for (int i = 0; i < sensorsArray.size(); i++) {
		if (actuatorsArray.get(i)->getPin() == pin) {
			sensorsArray.remove(i);
			break;
		}
	}
}

void LowerLayer::addActuator(Actuator* actuator) {
	actuatorsArray.add(actuator);
}

void LowerLayer::removeActuator(int pin) {
	for (int i = 0; i < actuatorsArray.size(); i++) {
		if (actuatorsArray.get(i)->getPin() == pin) {
			actuatorsArray.remove(i);
			break;
		}
	}
}

LinkedList<Message> LowerLayer::readSensorsData() {
	LinkedList<Message> messages = LinkedList<Message>();
	CommonValues commonValues;
	for (int i = 0; i < sensorsArray.size(); i++) {
		Message newMessage;
		if (sensorsArray.get(i)->getId() == commonValues.humidityTemperatureSensorId) {
			newMessage = sensorsArray.get(i)->readSensorData(true);
		}
		else {
			newMessage = sensorsArray.get(i)->readSensorData(false);
		}
		messages.add(newMessage);
	}
	return messages; 
}


void LowerLayer::onSensorFail() {
	
}

