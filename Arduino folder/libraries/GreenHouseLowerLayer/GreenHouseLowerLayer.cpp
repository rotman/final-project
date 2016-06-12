#include <GreenHouseLowerLayer.h>

void GreenHouseLowerLayer::initLayer(int address) {
	this->address = address;
	initDataArrays();
	//more inits here , think maybe to move the inits to relevant constractors
}

void GreenHouseLowerLayer::initDataArrays() {
	temperatureData = LinkedList<float>();
	soilHumidityData = LinkedList<float>();
	airHumidityData = LinkedList<float>();
	lightData = LinkedList<float>();
}
void GreenHouseLowerLayer::analyze() {
	LinkedList<Message> sensorsData = readSensorsData();
	for (int i = 0; i < sensorsData.size(); i++) {
		switch (sensorsData.get(i).sesnorType) {
			case temperateType:
				//this is emergency state - send message to middle layer immidietly
				if (sensorsData.get(i).data >= CommonValues::EMERGENCY_TEMPERATURE) {
					sendMessage(sensorsData.get(i).data);
				}
				//add data to data array for average
				temperatureData.add(sensorsData.get(i).data);
				if (temperatureData.size == producersSize) {
					float average = doAverage(temperatureData);
					Message newMessage = prepareDataMessage(average, temperateType);
					sendMessage(newMessage);
					//clear array after doing average
					temperatureData.clear();
				}
				
			break:
			case humidityType:
				//add data to data array for average
				airHumidityData.add(sensorsData.get(i).data);
				if (airHumidityData.size == producersSize) {
					float average = doAverage(airHumidityData);
					Message newMessage = prepareDataMessage(average, humidityType);
					sendMessage(newMessage);
					//clear array after doing average
					airHumidityData.clear();
				}
			break;
			case soilHumidityType:
				Message newMessage;
				//before doing average, check if need to actuate first
				if (sensorsData.get(i).data <= CommonValues::soilHumidityThresholdMin) {
					for (int i = 0; i<actuatorsArray.size() ; i++) {
						if (actuatorsArray.get(i)->getPin() == CommonValues::soilPin) {
							actuatorsArray.get(i)->actuate(true);
							if (this->address == CommonValues::lowerLayerAddress1) {
								newMessage.action = PUMP1;	
							}
							else if (this->address == CommonValues::lowerLayerAddress2) {
								newMessage.action = PUMP2;
							}
							break;
						}
					}
				}	
				//add data to data array for average
				soilHumidityData.add(sensorsData.get(i).data);
				if (soilHumidityData.size == producersSize) {
					float average = doAverage(soilHumidityData);
					newMessage = prepareDataMessage(average, soilHumidityType);
					sendMessage(newMessage);
					//clear array after doing average
					soilHumidityData.clear();
				}
				
			break;
			case lightType:
				//add data to data array for average
				lightData.add(sensorsData.get(i).data);
				if (lightData.size == producersSize) {
					float average = doAverage(lightData);
					Message newMessage = prepareDataMessage(average, lightData);
					sendMessage(newMessage);
					//clear array after doing average
					lightData.clear();
				}			
			break;			
		}

	}
}

Message& GreenHouseLowerLayer::prepareDataMessage(float data, char type) {
	Message newMessage;
	newMessage.data = data;
	newMessage.sensorType = type;
	newMessage.messageType = CommonValues::dataType;
	prepareMessage(newMessage, CommonValues::middleLayerAddress);
	return newMessage;
}

float GreenHouseLowerLayer::doAverage(LinkedList<float> data) {
	float average;
	for (int i = 0 ; i<data.size();i++) {
		average+=data;
	}
	average = average/data.size();
	return average;
}

void GreenHouseLowerLayer::decodeMessage(Message& message){
	if ('z' == message.sensorType) {
		//do nothing the message is empty
		return;
	}
	if (this->address != message.address) {
		//TODO resend message to it's true dest
		//do nothing the message is not for me
		return;	
	}
	//means we got new policy from upper layer
	if (message.messageType == CommonValues::policyChange) {
		switch (message.sensorType) {
			case CommonValues::temperateType:
				CommonValues::soilHumidityThresholdMin = message.data;
				CommonValues::soilHumidityThresholdMax = message.additionalData;
			break;
			case CommonValues::humidityType:
				CommonValues::soilHumidityThresholdMin = message.data;
				CommonValues::soilHumidityThresholdMax = message.additionalData;
			break;
			case CommonValues::soilHumidityType:
				CommonValues::soilHumidityThresholdMin = message.data;
				CommonValues::soilHumidityThresholdMax = message.additionalData;
			break;
			case CommonValues::lightType:
				CommonValues::lightThresholdMin = message.data;
				CommonValues::lightThresholdMax = message.additionalData;
			break;
		}
	}
}

Message GreenHouseLowerLayer::prepareMessage(Message& message, int address) {
	message.source = this->address;
	message.dest = address;
	return message;
}




