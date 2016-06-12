#include <GreenHouseMiddleLayer.h>


int GreenHouseMiddleLayer::findIdAndType(int id,char type){
	for (int i = 0; i < lastMessagePerType.size(); ++i) {
		if (lastMessagePerType.get(i).source == id && lastMessagePerType.get(i).sensorType == type) {
			return i;
		}
	}
	return -1;
}

void GreenHouseMiddleLayer::initLayer(int address) {
	this->address = address;
	actuators = LinkedList<Actuator*>();
	//more inits here
}

void GreenHouseMiddleLayer::addActuator(Actuator* actuator) {
	actuators.add(actuator);
}

void GreenHouseMiddleLayer::actuate(Actuator* actuator, bool on) {
	actuator->actuate(on);
}

void GreenHouseMiddleLayer::removeActuator(int pin) {
	for (int i = 0; i < actuators.size(); i++) {
		if (actuators.get(i)->getPin() == pin) {
			actuators.remove(i);
			break;
		}
	}
}

void GreenHouseMiddleLayer::actuate(Actuator* actuator, bool on) {
	actuator->actuate(on);
}

Message GreenHouseMiddleLayer::prepareMessage(Message message, int address) {
	Serial.println("prepareMessage()");
	message.source = CommonValues::middleLayerAddress;
	message.dest = address;
	return message;
}

void GreenHouseMiddleLayer::analyze(){
	int sensorsNumber = lowersIds.size();
	int temperatureAverage=0;
	int soilHumidityAverage=0;
	int lightAverage=0;
	int currentAverage=0;
	int waterAverage = 0;
	for (int i = 0; i < lowersIds.size(); ++i) {
		temperatureAverage += findIdAndType(lowersIds.get(i),CommonValues::temperatureType).data;
		soilHumidityAverage += findIdAndType(lowersIds.get(i),CommonValues::soilHumidityType).data;
		lightAverage += findIdAndType(lowersIds.get(i),CommonValues::lightType).data;
		currentAverage += findIdAndType(lowersIds.get(i),CommonValues::currentType).data;
		waterAverage += findIdAndType(lowersIds.get(i),CommonValues::waterType).data;
		//TODO check if the time of messages are within the sensorTypeNotRespondingTime threshold
	}

	temperatureAverage /= sensorsNumber;
	soilHumidityAverage /= sensorsNumber;
	lightAverage /= sensorsNumber;
	currentAverage /= sensorsNumber;
	waterAverage /= sensorsNumber;
	//TODO check threshold
}

void GreenHouseMiddleLayer::decodeMessage(Message msg) {
	Serial.println("decodeMessage()");
	DateTime dateTime;
	msg.dateTime = clock.createDateTime();             //add time to message
	if (msg.dest != CommonValues::middleLayerAddress) {
		Serial.println("not for me, be a good friend and pass it on");
		radioHelper.sendMessage(msg);
		return;
	}
	else if (msg.source >= highLayerMinAddress && msg.source < highLayerMaxAddress) {   //from higer layer
		switch (msg.messageType) {
		case CommonValues.emptyMessage:break;//TODO
		case CommonValues.policyChange:break;//TODO
		case CommonValues.loopTimeChange:break;//TODO
		case CommonValues.myAddressChange:break;//TODO
		case CommonValues.yourAddressChange: break;//TODO
		case CommonValues.arduinoMalfunction: break;//TODO
		default:break;
			 
		}
	}
	//if the meesgae came from bottom layer
	//the layer should act/send up the hirarchy if needed
	else if (msg.source >= lowerLayerMinAddress && msg.source < lowerLayerMaxAddress) {
		int idPosition = findIdAndType(msg.source, msg.sensorType);
		if (idPosition == -1)				//at the first time
			lastMessagePerType.add(msg);
		else {
			lastMessagePerType.get(idPosition).data = msg.data;			//update last data
			lastMessagePerType.get(idPosition).dateTime = msg.dateTime; //update last data
		}
		analyze();
		}
	}

