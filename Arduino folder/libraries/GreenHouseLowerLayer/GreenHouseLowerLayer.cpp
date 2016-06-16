#include <GreenHouseLowerLayer.h>

void GreenHouseLowerLayer::initLayer(int address) {
	this->address = address;
	Serial.print(this->address);
	Serial.println();
	previousMillis = 0;
	ICommunicationable* radio = new Radio();
	radio->initCommunication(this->address, CommonValues::middleLayerAddress);
	communicationArray.add(radio);
	initDataArrays();
	//more inits here , think maybe to move the inits to relevant constractors
}

void GreenHouseLowerLayer::initDataArrays() {
	if (this->address != CommonValues::lowerLayerConsumptionAdress) {
		temperatureData = LinkedList<float>();
		soilHumidityData = LinkedList<float>();
		airHumidityData = LinkedList<float>();
		lightData = LinkedList<float>();
	}
}

void GreenHouseLowerLayer::analyze() {
	LinkedList<Message> sensorsData = readSensorsData();
	if (this->address == CommonValues::lowerLayerConsumptionAdress) {
		currentMillis = millis();
		for (int i = 0; i < sensorsData.size(); i++) {
			switch (sensorsData.get(i).sensorType) {
				case CommonValues::currentType:
					currentConsumptionData += sensorsData.get(i).data;
				break;
				case CommonValues::waterType:
					waterConsumptionData += sensorsData.get(i).data;
				break;
			}
		}
		//set the timer for sending consumption data to once a day
		if ((unsigned long)(currentMillis - previousMillis) >= CommonValues::day) {
			Message currentMessage = prepareDataMessage(currentConsumptionData, CommonValues::currentType);
			Message waterMessage = prepareDataMessage(waterConsumptionData, CommonValues::waterType);
			bool isCurrentSent = communicationArray.get(0)->sendMessage(currentMessage);
			if (!isCurrentSent) {
				bool isCurrentSent = communicationArray.get(0)->sendMessage(currentMessage);
			}
			bool isWaterSent = communicationArray.get(0)->sendMessage(waterMessage);
			if (!isWaterSent) {
				bool isWaterSent = communicationArray.get(0)->sendMessage(waterMessage);
			}
			previousMillis = currentMillis;
		}
	}
	else {
		for (int i = 0; i < sensorsData.size(); i++) {
			switch (sensorsData.get(i).sensorType) {
				case CommonValues::temperatureType:
					//this is emergency state - send message to middle layer immidietly
					if (sensorsData.get(i).data >= CommonValues::EMERGENCY_TEMPERATURE) {
						Message newMessage = prepareDataMessage(sensorsData.get(i).data, CommonValues::emergencyType);
						bool isSent = communicationArray.get(0)->sendMessage(newMessage);
						if (!isSent) {
							//TODO maybe resent until received
							bool isSent = communicationArray.get(0)->sendMessage(newMessage);
						}
					}
					//add data to data array for average
					temperatureData.add(sensorsData.get(i).data);
					if (temperatureData.size() == CommonValues::producersSize) {
						float average = doAverage(temperatureData);
						Message newMessage = prepareDataMessage(average, CommonValues::temperatureType);
						communicationArray.get(0)->sendMessage(newMessage);
						//clear array after doing average
						temperatureData.clear();
					}
				break;
				case CommonValues::humidityType:
					//add data to data array for average
					airHumidityData.add(sensorsData.get(i).data);
					if (airHumidityData.size() == CommonValues::producersSize) {
						float average = doAverage(airHumidityData);
						Message newMessage = prepareDataMessage(average, CommonValues::humidityType);
						communicationArray.get(0)->sendMessage(newMessage);
						//clear array after doing average
						airHumidityData.clear();
					}
				break;
				case CommonValues::soilHumidityType:
					Message newMessage;
					//before doing average, check if need to actuate first
					if (sensorsData.get(i).data <= CommonValues::soilHumidityThresholdMin) {
						Serial.println("GreenHouseLowerLayer, actuate needed");
						for (int i = 0; i<actuatorsArray.size() ; i++) {
							if (actuatorsArray.get(i)->getPin() == CommonValues::soilPin) {
								actuatorsArray.get(i)->actuate(true);
								Serial.println("GreenHouseLowerLayer, PUMP1 actuate");									
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
					if (soilHumidityData.size() == CommonValues::producersSize) {
						float average = doAverage(soilHumidityData);
						newMessage = prepareDataMessage(average, CommonValues::soilHumidityType);
						communicationArray.get(0)->sendMessage(newMessage);
						//clear array after doing average
						soilHumidityData.clear();

					}
				break;
				case CommonValues::lightType:
					//add data to data array for average
					lightData.add(sensorsData.get(i).data);
					if (lightData.size() == CommonValues::producersSize) {
						float average = doAverage(lightData);
						Message newMessage = prepareDataMessage(average, CommonValues::lightType);
						communicationArray.get(0)->sendMessage(newMessage);
						//clear array after doing average
						lightData.clear();
					}

				break;			
			}
		}
	}
}

Message& GreenHouseLowerLayer::prepareDataMessage(float data, char type) {
	Message newMessage;
	newMessage.data = data;
	if (type == CommonValues::emergencyType) {
		newMessage.messageType = CommonValues::emergencyType;		
	}
	else {
		newMessage.messageType = CommonValues::dataType;
		newMessage.sensorType = type;	
	}
	prepareMessage(newMessage, CommonValues::middleLayerAddress);
	return newMessage;
}

float GreenHouseLowerLayer::doAverage(LinkedList<float> data) {
	float average;
	for (int i = 0 ; i<data.size();i++) {
		average+=data.get(i);
	}
	average = average/data.size();
	return average;
}

void GreenHouseLowerLayer::decodeMessage(Message& message){
	if ('z' == message.sensorType) {
		//do nothing the message is empty
		return;
	}
	if (this->address != message.dest) {
		//not for me, resend the message to it's original destination
		communicationArray.get(0)->sendMessage(message);	
		return;	
	}
	//means we got new policy from upper layer
	if (message.messageType == CommonValues::policyChange) {
		if (message.sensorType == CommonValues::soilHumidityType) {
			CommonValues::soilHumidityThresholdMin = message.data;
			CommonValues::soilHumidityThresholdMax = message.additionalData;
		}
	}
}

Message& GreenHouseLowerLayer::prepareMessage(Message& message, int address) {
	message.source = this->address;
	message.dest = address;
	return message;
}




