#include <GreenHouseLowerLayer.h>
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
Actuator* GreenHouseLowerLayer::findActuatorById(int){}

void GreenHouseLowerLayer::decodeMessage(Message message){}
void GreenHouseLowerLayer::analyze(){}
Message GreenHouseLowerLayer::prepareMessage(Message, int) {}
void GreenHouseLowerLayer::initLayer(int address) {
	this->address = address;
	sensorsArray = LinkedList<Sensor*>();
	actuatorsArray = LinkedList<Actuator*>();
	//more inits here , think maybe to move the inits to relevant constractors
}

void GreenHouseLowerLayer::addSensor(Sensor* sensor) {
	sensorsArray.add(sensor);
}

void GreenHouseLowerLayer::removeSensor(int pin) {
	for (int i = 0; i < sensorsArray.size(); i++) {
		if (actuatorsArray.get(i)->getPin() == pin) {
			sensorsArray.remove(i);
			break;
		}
	}
}

void GreenHouseLowerLayer::addActuator(Actuator* actuator) {
	actuatorsArray.add(actuator);
}

void GreenHouseLowerLayer::removeActuator(int pin) {
	for (int i = 0; i < actuatorsArray.size(); i++) {
		if (actuatorsArray.get(i)->getPin() == pin) {
			actuatorsArray.remove(i);
			break;
		}
	}
}

LinkedList<Message> GreenHouseLowerLayer::readSensorsData() {
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


void GreenHouseLowerLayer::onSensorFail() {

}
