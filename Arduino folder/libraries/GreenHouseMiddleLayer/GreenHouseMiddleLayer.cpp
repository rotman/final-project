#include <GreenHouseMiddleLayer.h>


/*int GreenHouseMiddleLayer::findIdAndType(int id,char type){
	for (int i = 0; i < lastMessagePerType.size(); ++i) {
		if (lastMessagePerType.get(i).source == id && lastMessagePerType.get(i).sensorType == type) {
			return i;
		}
	}
	return -1;
}*/
void GreenHouseMiddleLayer::initLayer(int address) {
	this->address = address;
	
	//register lower layers
	addLowerId(CommonValues::lowerLayerAddress1);
	addLowerId(CommonValues::lowerLayerAddress2);
	addLowerId(CommonValues::lowerLayerConsumptionAdress);	//maybe remove the consumption layer from the low layers array
															//init radio
	ICommunicationable* radio = new Radio();
	radio->initCommunication(this->address, CommonValues::lowerLayerAddress1);
	communicationList.add(radio);
	setLoopTime(CommonValues::defaultLoopTime);

	//more inits here
}

bool GreenHouseMiddleLayer::sendMessage(Message& message) {
	return communicationList.get(0)->sendMessage(message);
};
void GreenHouseMiddleLayer::receiveMessage(Message& message) {
	 communicationList.get(0)->receiveMessage(message);
};



void GreenHouseMiddleLayer::prepareMessage(Message& message, int add) {
	message.source = this->address;
	message.dest = add;	
}

float GreenHouseMiddleLayer::doAverage(LinkedList<Message>& messages) {
	float average;
	for (int i = 0 ; i<messages.size();++i) {
		average+=messages.get(i).data;
	}
	average = average/messages.size();
	return average;
}

void GreenHouseMiddleLayer::analyze() {	
	float temperatureAverage = 0;
	float airHumidityAverage = 0;
	float lightAverage = 0;
	Message newMessage;
	
	//we have some data to analyze
	if (isTemperatureReadyToAnalyze) {
		//calculate average
		temperatureAverage = doAverage(temperatureData);
		//check thresholds
		if (temperatureAverage >= CommonValues::temperatureThresholdMax) {
			actuate(CommonValues::fan1Pin);
			actuate(CommonValues::fan2Pin);
			newMessage.action = FAN;
		}
		else if (temperatureAverage < CommonValues::temperatureThresholdMin) {
			actuate(CommonValues::heatPin);
			newMessage.action = HEATER;

		}
		//prepare message and send to high layer
		prepareMessage(newMessage, CommonValues::highLayerAddress);
		newMessage.data = temperatureAverage;
		newMessage.messageType = CommonValues::dataType;
		newMessage.sensorType = CommonValues::temperatureType;
		communicationList.get(0)->sendMessage(newMessage);
		//clear the array after done
		temperatureData.clear();
	}
	//we have some data to analyze
	if (isHumidityReadyToAnalyze) {
		//calculate average
		airHumidityAverage = doAverage(humidityData);
		//check thresholds
		if (airHumidityAverage < CommonValues::airHumidityThresholdMin) {
			actuate(CommonValues::steamPin);
			newMessage.action = STEAMER;
		}
		//prepare message and send to high layer
		newMessage.data = airHumidityAverage;
		newMessage.messageType = CommonValues::dataType;
		newMessage.sensorType = CommonValues::humidityType;
		communicationList.get(0)->sendMessage(newMessage);
		//clear the array after done
		temperatureData.clear();
	}
	if (isLightReadyToAnalyze) {
		//calculate average
		lightAverage = doAverage(lightData);
		//TODO decide what to do with light thresholds
		
		//prepare message and send to high layer
		newMessage.data = lightAverage;
		newMessage.messageType = CommonValues::dataType;
		newMessage.sensorType = CommonValues::lightType;
		communicationList.get(0)->sendMessage(newMessage);
		//clear the array after done
		lightData.clear();
	}	
	
	//no need to do average on consumption data
	
}

void GreenHouseMiddleLayer::decodeMessage(Message& msg) {	
	if (CommonValues::emptyMessage == msg.sensorType) {
		Serial.println("message is empty");
		//do nothing the message is empty
		return;
	}
	DateTime dateTime;
	msg.dateTime = clock.createDateTime();             //add time to message
	if (msg.dest != CommonValues::middleLayerAddress) {
		Serial.println("message is not for me pass it on");
		communicationList.get(0)->sendMessage(msg);	
		return;
	}
	//from higer layer
	else if (msg.source >= CommonValues::highLayerMinAddress && msg.source < CommonValues::highLayerMaxAddress) {   
		switch (msg.messageType) {
			case CommonValues::emptyMessage:
				Serial.println("message is null");
				//this can't happen, we've already check if the message is empty
				return;
			break;
			case CommonValues::policyChange:
				switch (msg.sensorType) {
					case CommonValues::soilHumidityType:
						Serial.println("soilHumidityType");
						//if it's soil Humidity policy changes, send it to the lower layers
						for (int i = 1; i<= lowersIds.size() ; ++i) {
							if (i != CommonValues::lowerLayerConsumptionAdress) {
								Serial.print("GreenHouseMiddleLayer, sending new thresholds to address ");
								Serial.println(lowersIds.get(i));
								prepareMessage(msg, lowersIds.get(i));
								communicationList.get(0)->sendMessage(msg);
							}
						}			
					break;
					case CommonValues::temperatureType:
						CommonValues::temperatureThresholdMin = msg.data;
						CommonValues::temperatureThresholdMax = msg.additionalData;
					break;
					case CommonValues::humidityType:
						CommonValues::airHumidityThresholdMin = msg.data;
						CommonValues::airHumidityThresholdMax = msg.additionalData;
					break;
					case CommonValues::lightType:
						CommonValues::lightThresholdMin = msg.data;
						CommonValues::lightThresholdMax = msg.additionalData;
					break;
				}
			case CommonValues::loopTimeChange:
				
			break;
			case CommonValues::myAddressChange:
				
			break;
			case CommonValues::yourAddressChange:

			
			break;
			case CommonValues::arduinoMalfunction: 

			break;			 
		}
	}
	//if the meesgae came from bottom layer
	//the layer should act/send up the hirarchy if needed
	else if (msg.source >= CommonValues::lowerLayerMinAddress && msg.source < CommonValues::lowerLayerMaxAddress) {
		switch (msg.messageType) {
			//first check if it's an emergency message
			case CommonValues::emergencyType:
				Serial.println("GreenHouseMiddleLayer, emergencyType from switch case - turn on all fans");
				actuate(CommonValues::fan1Pin);
				actuate(CommonValues::fan2Pin);
				prepareMessage(msg, CommonValues::highLayerAddress);
				communicationList.get(0)->sendMessage(msg);	
			break;
			case CommonValues::dataType:
				switch (msg.sensorType) {
					case CommonValues::soilHumidityType:
						//if it's soil Humidity data, send it to the high layer
						//not using prepare message here because we want to know from which lower layer the data was sent
						msg.dest = CommonValues::highLayerAddress;
						communicationList.get(0)->sendMessage(msg);
					break;
					case CommonValues::currentType:
						//if it's current consumption data, send it to the high layer
						prepareMessage(msg, CommonValues::highLayerAddress);
						communicationList.get(0)->sendMessage(msg);
					break;
					case CommonValues::waterType:
						//if it's water consumption data, send it to the high layer
						prepareMessage(msg, CommonValues::highLayerAddress);
						communicationList.get(0)->sendMessage(msg);
					break;
					case CommonValues::temperatureType:
						temperatureData.add(msg);
						isTemperatureReadyToAnalyze = (isArrayFullAndUnique(temperatureData) && isTimeConsistency(temperatureData, CommonValues::minutesInInterval));
					break;
					case CommonValues::humidityType:
						humidityData.add(msg);
						isHumidityReadyToAnalyze = (isArrayFullAndUnique(humidityData) && isTimeConsistency(temperatureData, CommonValues::minutesInInterval));
					break;
					case CommonValues::lightType:
						lightData.add(msg);
						isLightReadyToAnalyze = (isArrayFullAndUnique(lightData) && isTimeConsistency(temperatureData, CommonValues::minutesInInterval));
					break;
				}
			break;
		//TODO think maybe handle with more messageTypes	
		}
		analyze();
	}
}

bool GreenHouseMiddleLayer::isTimeConsistency(LinkedList<Message>& data, int minutes) {
	unsigned long interval = minutes*CommonValues::minute;
	for (int i = 0; i<data.size(); ++i) {
		for (int j = 1; j<data.size(); j++) {
			if ((GreenHouseMiddleLayer::convertDateTimeToMillis(data.get(i).dateTime) - convertDateTimeToMillis(data.get(j).dateTime)) > interval) {
				return false;
			}
		}
	}
	return true;
}

unsigned long GreenHouseMiddleLayer::convertDateTimeToMillis(DateTime dateTime) {
	unsigned long millis = (dateTime.seconds*1000) + (dateTime.minutes*60000) + (dateTime.hours*3600000) + 
		(dateTime.date*86400000) + (dateTime.month*2629746000) + (dateTime.year*31556952000);
	Serial.println(millis);
	return millis;
}

bool GreenHouseMiddleLayer::isArrayFullAndUnique(LinkedList<Message>& data) {
	if (data.size() == CommonValues::lowerLayerRegisteredNum) {
		int j = 1;
		for (int i = 0; i<data.size(); ++i) {
			while (j<data.size()) {
				if (data.get(i).source == data.get(j).source) {
					return false;
				}
				j = i+1;
			}
		}
		return true;
	}
	return false;
}

void GreenHouseMiddleLayer::actuate(int pin) {
	for (int i = 0; i<actuatorsList.size() ; ++i) {
		if (actuatorsList.get(i)->getPin() == pin) {
			actuatorsList.get(i)->actuate(true);
			break;
		}
	}	
}


