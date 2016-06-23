#include <GreenHouseLowerLayer.h>

void GreenHouseLowerLayer::sendMessage(Message& message) {
	Serial.println("GreenHouseLowerLayer::sendMessage");
	communicationList.get(0)->sendMessage(message);
}

void GreenHouseLowerLayer::receiveMessage(Message& message) {
	communicationList.get(0)->receiveMessage(message);
}

void GreenHouseLowerLayer::initLayer(int address) {
	this->address = address;
	previousMillis = 0;
	ICommunicationable* radio = new Radio();
	radio->initCommunication(this->address, CommonValues::middleLayerAddress);
	communicationList.add(radio);
	setLoopTime(CommonValues::defaultLoopTime);
	//more inits here , think maybe to move the inits to relevant constractors
}


void GreenHouseLowerLayer::analyze() {
	//TODO destruct all created linked list
	Serial.println("analyze");
	LinkedList<Message> sensorsData;
	readSensorsData(sensorsData);
	if (this->address == CommonValues::lowerLayerConsumptionAdress) { //am i the consumtion layer?
		currentMillis = millis();
		for (int i = 0; i < sensorsData.size(); i++) {
			switch (sensorsData.get(i).sensorType) {
				case CommonValues::currentType:
					currentConsumptionData += sensorsData.get(i).data;
				break;
				case CommonValues::waterType:
					if (sensorsData.get(i).additionalData == CommonValues::waterConsumptionPin1) {
						waterConsumptionData1 += sensorsData.get(i).data;
					}
					else if (sensorsData.get(i).additionalData == CommonValues::waterConsumptionPin2) {
						waterConsumptionData2 += sensorsData.get(i).data;
					}
				break;
			}
		}
		//set the timer for sending consumption data to once a day
		if ((unsigned long)(currentMillis - previousMillis) >= CommonValues::day) {
			Message currentMessage;
			prepareDataMessage(currentMessage, currentConsumptionData, CommonValues::currentType);
			if (!(communicationList.get(0)->sendMessage(currentMessage))){
				//TODO if no sent
			}
			Message waterMessage1;
			//TODO ROTEM why to add CommonValues::waterType ? we do it at the Sensor class
			prepareDataMessage(waterMessage1, waterConsumptionData1, CommonValues::waterType);
			if (!(communicationList.get(0)->sendMessage(waterMessage1))) {
				//TODO if no sent
			}
			Message waterMessage2;
			//TODO ROTEM why to add CommonValues::waterType ? we do it at the Sensor class
			prepareDataMessage(waterMessage2, waterConsumptionData2, CommonValues::waterType);
		 
			if (!(communicationList.get(0)->sendMessage(waterMessage2))) {
				//TODO if no sent
			}
			previousMillis = currentMillis;
		}
	}
	else 
	{	//i am not the Consumption layer, im a regular lower layer
		for (int i = 0; i < sensorsData.size(); ++i) {
			Serial.print("sensor type:");
			Serial.println(sensorsData.get(i).sensorType);
			switch (sensorsData.get(i).sensorType) {
				case CommonValues::temperatureType:
					//this is emergency state - send message to middle layer immidietly
					if (sensorsData.get(i).data >= CommonValues::EMERGENCY_TEMPERATURE) {
						Message newMessage;
						prepareDataMessage(newMessage, sensorsData.get(i).data, CommonValues::emergencyType);
						bool isSent = communicationList.get(0)->sendMessage(newMessage);
						if (!isSent) {
							//TODO maybe resent until received ROTEM whyyyyy
							bool isSent = communicationList.get(0)->sendMessage(newMessage);
						}
					}
					//add data to data array for average
					temperatureData.add(sensorsData.get(i).data);
					if (temperatureData.size() == CommonValues::producersSize) {
						float average = doAverage(temperatureData);
						Message newMessage;
						prepareDataMessage(newMessage, average, CommonValues::temperatureType);
						if (communicationList.get(0)->sendMessage(newMessage)) {
							//clear array after doing average
							temperatureData.clear();
						}
						else {//send failed
							//TODO 
						}
					}
				break;
				case CommonValues::humidityType:
					//add data to data array for average
					airHumidityData.add(sensorsData.get(i).data);	
					if (airHumidityData.size() == CommonValues::producersSize) {
						float average = doAverage(airHumidityData);
						Message newMessage;
						prepareDataMessage(newMessage, average, CommonValues::humidityType);
						sendMessage(newMessage);
						//clear array after doing average
						airHumidityData.clear();
					}
				break;
				case CommonValues::soilHumidityType:
					Message newMessage;
					//before doing average, check if need to actuate first
					if (sensorsData.get(i).data <= CommonValues::soilHumidityThresholdMin) {
						for (int i = 0; i<getActuatorsList().size() ; ++i) {
							if (getActuatorsList().get(i)->getPin() == CommonValues::pumpPin) {
								getActuatorsList().get(i)->actuate(true);
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
					//Serial.print("soilHumidityDataaaaaaaaaaaaa sizee:");
					//Serial.println(soilHumidityData.size());
					if (soilHumidityData.size() == CommonValues::producersSize) {
						float average = doAverage(soilHumidityData);
						prepareDataMessage(newMessage, average, CommonValues::soilHumidityType);
						communicationList.get(0)->sendMessage(newMessage);
						//clear array after doing average
						soilHumidityData.clear();
					}
				break;
				case CommonValues::lightType:
					//add data to data array for average
					lightData.add(sensorsData.get(i).data);
					if (lightData.size() == CommonValues::producersSize) {
						float average = doAverage(lightData);
						Message newMessage;
						prepareDataMessage(newMessage, average, CommonValues::lightType);
						communicationList.get(0)->sendMessage(newMessage);
						//clear array after doing average
						lightData.clear();
					}
				break;	
				default : Serial.println("default");
					break;
			}

		}
	//	getSensorsData().clear(); //TODO think about moving this to sensorable somehow
	}
}
//TODO rotem what is this? dont know if necessary..
void GreenHouseLowerLayer::prepareDataMessage(Message& message, float data, char type) {
	message.data = data;
	if (type == CommonValues::emergencyType) {
		message.messageType = CommonValues::emergencyType;		
	}
	else {
		message.messageType = CommonValues::dataType;
		message.sensorType = type;	
	}
	prepareMessage(message, CommonValues::middleLayerAddress);
}

float GreenHouseLowerLayer::doAverage(LinkedList<float>& data) {
	float average;
	for (int i = 0 ; i<data.size();i++) {
		average+=data.get(i);
	}
	average = average/data.size();
	return average;
}	

void GreenHouseLowerLayer::decodeMessage(Message& message){
	if (CommonValues::emptyMessage == message.sensorType) {
		//do nothing the message is empty
		return;
	}
	if (this->address != message.dest) {
		//not for me, resend the message to it's original destination
		communicationList.get(0)->sendMessage(message);	
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

void GreenHouseLowerLayer::prepareMessage(Message& message, int address) {
	message.source = this->address;
	message.dest = address;
}




