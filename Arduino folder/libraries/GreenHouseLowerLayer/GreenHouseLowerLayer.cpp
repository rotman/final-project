#include <GreenHouseLowerLayer.h>

void GreenHouseLowerLayer::initLayer(int address) {
	Serial.print("GreenHouseLowerLayer, initLayer() with address ");
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
	Serial.println("GreenHouseLowerLayer, initDataArrays()");
	if (this->address != CommonValues::lowerLayerConsumptionAdress) {
		Serial.println("GreenHouseLowerLayer, this is regular lower layer - init data arrays");
		temperatureData = LinkedList<float>();
		soilHumidityData = LinkedList<float>();
		airHumidityData = LinkedList<float>();
		lightData = LinkedList<float>();
	}
	else {
		Serial.println("GreenHouseLowerLayer, this is consumption lower layer - NOT init data arrays");	
	}
}

void GreenHouseLowerLayer::analyze() {
	Serial.println("GreenHouseLowerLayer, analyze()");
	LinkedList<Message> sensorsData = readSensorsData();
	if (this->address == CommonValues::lowerLayerConsumptionAdress) {
		Serial.println("GreenHouseLowerLayer, this is consumption lower layer");	
		currentMillis = millis();
		for (int i = 0; i < sensorsData.size(); i++) {
			switch (sensorsData.get(i).sensorType) {
				case CommonValues::currentType:
					currentConsumptionData += sensorsData.get(i).data;
					Serial.println("GreenHouseLowerLayer, the type is C and the currentConsumptionData is ");
					Serial.print(currentConsumptionData);
				break;
				case CommonValues::waterType:
					waterConsumptionData += sensorsData.get(i).data;
					Serial.println("GreenHouseLowerLayer, the type is W and the waterConsumptionData is ");
					Serial.print(waterConsumptionData);
				break;
			}
		}
		Serial.println("GreenHouseLowerLayer, checking if day has passed");
		if ((unsigned long)(currentMillis - previousMillis) >= CommonValues::day) {
			Serial.println("GreenHouseLowerLayer, day passed");
			Message currentMessage = prepareDataMessage(currentConsumptionData, CommonValues::currentType);
			Message waterMessage = prepareDataMessage(waterConsumptionData, CommonValues::waterType);
			Serial.println("GreenHouseLowerLayer, sending currentMessage");
			bool isCurrentSent = communicationArray.get(0)->sendMessage(currentMessage);
			if (!isCurrentSent) {
				Serial.println("GreenHouseLowerLayer, message sent failed-try again");
				bool isCurrentSent = communicationArray.get(0)->sendMessage(currentMessage);
			}
			Serial.println("GreenHouseLowerLayer, sending waterMessage");
			bool isWaterSent = communicationArray.get(0)->sendMessage(waterMessage);
			if (!isWaterSent) {
				Serial.println("GreenHouseLowerLayer, message sent failed-try again");
				bool isWaterSent = communicationArray.get(0)->sendMessage(waterMessage);
			}
			Serial.println("GreenHouseLowerLayer, reset time");
			previousMillis = currentMillis;
		}
		else {
			Serial.println("GreenHouseLowerLayer, day NOT passed - just aggregate consumption data");	
		}
	}
	else {
		Serial.println("GreenHouseLowerLayer, this is regular lower layer");	
		for (int i = 0; i < sensorsData.size(); i++) {
			switch (sensorsData.get(i).sensorType) {
				Serial.print("GreenHouseLowerLayer, sensor type is ");
				Serial.print(sensorsData.get(i).sensorType);
				Serial.println();
				case CommonValues::temperatureType:
					//this is emergency state - send message to middle layer immidietly
					if (sensorsData.get(i).data >= CommonValues::EMERGENCY_TEMPERATURE) {
						Serial.println("GreenHouseLowerLayer, emergency state - send message to middle layer immidietly");
						Message newMessage = prepareDataMessage(sensorsData.get(i).data, CommonValues::emergencyType);
						bool isSent = communicationArray.get(0)->sendMessage(newMessage);
						if (!isSent) {
							Serial.println("GreenHouseLowerLayer, message sent failed- try again");
							//TODO maybe resent until received
							bool isSent = communicationArray.get(0)->sendMessage(newMessage);
						}
					}
					//add data to data array for average
					temperatureData.add(sensorsData.get(i).data);
					Serial.println("GreenHouseLowerLayer, added value to temperatureData array");
					if (temperatureData.size() == CommonValues::producersSize) {
						Serial.println("GreenHouseLowerLayer, temperatureData array is full- do average");
						float average = doAverage(temperatureData);
						Serial.print("GreenHouseLowerLayer, temperature average is ");
						Serial.print(average);
						Serial.println();					
						Message newMessage = prepareDataMessage(average, CommonValues::temperatureType);
						Serial.print("GreenHouseLowerLayer, sending message");
						communicationArray.get(0)->sendMessage(newMessage);
						//clear array after doing average
						temperatureData.clear();
						Serial.print("GreenHouseLowerLayer, clear temperatureData array");
					}
					else {
						Serial.println("GreenHouseLowerLayer, temperatureData array isn't full yet - still waiting");
					}
				break;
				case CommonValues::humidityType:
					//add data to data array for average
					airHumidityData.add(sensorsData.get(i).data);
					Serial.println("GreenHouseLowerLayer, added value to airHumidityData array");				
					if (airHumidityData.size() == CommonValues::producersSize) {
						Serial.println("GreenHouseLowerLayer, temperatureData array is full- do average");
						float average = doAverage(airHumidityData);
						Serial.print("GreenHouseLowerLayer, airHumidity average is ");
						Serial.print(average);
						Serial.println();
						Message newMessage = prepareDataMessage(average, CommonValues::humidityType);
						communicationArray.get(0)->sendMessage(newMessage);
						//clear array after doing average
						airHumidityData.clear();
						Serial.println("GreenHouseLowerLayer, clear airHumidityData array");
					}
					else {
						Serial.println("GreenHouseLowerLayer, airHumidityData array isn't full yet - still waiting");	
					}
				break;
				case CommonValues::soilHumidityType:
					Message newMessage;
					//before doing average, check if need to actuate first
					Serial.println("GreenHouseLowerLayer, soilHumidityType check if actuate needed");
					if (sensorsData.get(i).data <= CommonValues::soilHumidityThresholdMin) {
						for (int i = 0; i<actuatorsArray.size() ; i++) {
							if (actuatorsArray.get(i)->getPin() == CommonValues::soilPin) {
								Serial.println("GreenHouseLowerLayer, actuate needed");
								actuatorsArray.get(i)->actuate(true);
								if (this->address == CommonValues::lowerLayerAddress1) {
									newMessage.action = PUMP1;
									Serial.println("GreenHouseLowerLayer, PUMP1 actuate");									
								}	
								else if (this->address == CommonValues::lowerLayerAddress2) {
									newMessage.action = PUMP2;
									Serial.println("GreenHouseLowerLayer, PUMP2 actuate");
								}
								break;
							}
						}
					}
					else {
						Serial.println("GreenHouseLowerLayer, NO actuate needed");
					}
					//add data to data array for average
					soilHumidityData.add(sensorsData.get(i).data);
					Serial.println("GreenHouseLowerLayer, added value to soilHumidityData array");	
					if (soilHumidityData.size() == CommonValues::producersSize) {
						Serial.println("GreenHouseLowerLayer, soilHumidityData array is full- do average");
						float average = doAverage(soilHumidityData);
						Serial.print("GreenHouseLowerLayer, soilHumidity average is ");
						Serial.print(average);
						Serial.println();
						newMessage = prepareDataMessage(average, CommonValues::soilHumidityType);
						communicationArray.get(0)->sendMessage(newMessage);
						//clear array after doing average
						soilHumidityData.clear();
						Serial.println("GreenHouseLowerLayer, clear soilHumidityData array");

					}
					else {
						Serial.println("GreenHouseLowerLayer, soilHumidityData array isn't full yet - still waiting");		
					}
				break;
				case CommonValues::lightType:
					//add data to data array for average
					lightData.add(sensorsData.get(i).data);
					Serial.println("GreenHouseLowerLayer, added value to lightData array");	
					if (lightData.size() == CommonValues::producersSize) {
						Serial.println("GreenHouseLowerLayer, lightData array is full- do average");
						float average = doAverage(lightData);
						Serial.print("GreenHouseLowerLayer, light average is ");
						Serial.print(average);
						Serial.println();
						Message newMessage = prepareDataMessage(average, CommonValues::lightType);
						communicationArray.get(0)->sendMessage(newMessage);
						//clear array after doing average
						lightData.clear();
						Serial.println("GreenHouseLowerLayer, clear lightData array");
					}
					else {
						Serial.println("GreenHouseLowerLayer, lightData array isn't full yet - still waiting");			
					}
				break;			
			}
		}
	}
}

Message& GreenHouseLowerLayer::prepareDataMessage(float data, char type) {
	Serial.print("GreenHouseLowerLayer, prepareDataMessage() with type: ");
	Serial.print(type);
	Serial.print("and data: ");
	Serial.print(data);
	Serial.println();
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
	Serial.println("decodeMessage()");	
	if ('z' == message.sensorType) {
		Serial.println("empty message");	
		//do nothing the message is empty
		return;
	}
	if (this->address != message.dest) {
		Serial.println("redirect message");	
		//not for me, resend the message to it's original destination
		communicationArray.get(0)->sendMessage(message);	
		return;	
	}
	//means we got new policy from upper layer
	if (message.messageType == CommonValues::policyChange) {
		if (message.sensorType == CommonValues::soilHumidityType) {
			Serial.println("change soil humidity thresholds");	
			CommonValues::soilHumidityThresholdMin = message.data;
			CommonValues::soilHumidityThresholdMax = message.additionalData;
		}
	}
}

Message& GreenHouseLowerLayer::prepareMessage(Message& message, int address) {
	Serial.println("prepareMessage()");
	message.source = this->address;
	message.dest = address;
	return message;
}




