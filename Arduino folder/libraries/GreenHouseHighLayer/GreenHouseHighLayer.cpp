#include "GreenHouseHighLayer.h"

void GreenHouseHighLayer::initLayer(int address) {
	int i;

	this->address = address;

	//initialize greenhouse data
	for (i = 0 ; i < CommonValues::amountOfGreenHouses ; i++ ) {
			greenHouseData[i].setId(101 + i) ;
			greenHouseThresholds[i].setId(101 + i);
	}

	//initialize communication

	ICommunicationable* radioPtr = new Radio();
	radioPtr->initCommunication(CommonValues::highLayerAddress,CommonValues::middleLayerAddress);
	this->addCommunication(radioPtr);

	ICommunicationable* wifiPtr = new Wifi();
	wifiPtr->initCommunication(CommonValues::ssid, CommonValues::password);
	this->addCommunication(wifiPtr);

}

void GreenHouseHighLayer::analyze() {}

int GreenHouseHighLayer::findGreenHouseDataIndex(int id) {
  int i, result;
  for (i = 0 ; i < CommonValues::amountOfGreenHouses ; i++ ) {
    if (id == greenHouseData[i].getId())
      result = i;
  }
  return result;
}

int GreenHouseHighLayer::findGreenHouseThresholdsIndex(int id) {
  int i, result;
  for (i = 0 ; i < CommonValues::amountOfGreenHouses ; i++ ) {
    if (id == this->greenHouseThresholds[i].getId())
      result = i;
  }
  return result;
}

void GreenHouseHighLayer::decodeMessage(Message & message) {
  int greenhouseId = message.source;
  int i = this->findGreenHouseDataIndex(greenhouseId);
  float data;
  if (CommonValues::amountOfGreenHouses == i) {
    return;
  }

	switch(message.messageType) {
		case CommonValues::emergencyType:
			break;
		case CommonValues::dataType:
			DateTime dateTime = message.dateTime;
		  switch(message.sensorType) {
		      case CommonValues::temperatureType:
		        data = message.data;
		        greenHouseData[i].updateValue(String("temperature"),data,dateTime);
		        break;
		      case CommonValues::humidityType:
		        data = message.data;
		        greenHouseData[i].updateValue(String('airHumidity'),data,dateTime);
		        break;
		      case CommonValues::lightType:
		        data = message.data;
		        greenHouseData[i].updateValue(String('luminance'),data,dateTime);
		        break;
		      case CommonValues::soilHumidityType:
		        data = message.data;
		        greenHouseData[i].updateValue(String('soilHumidity'),data,dateTime);
		        break;
					case CommonValues::currentType:
						data = message.data;
						greenHouseData[i].updateValue(String('current'),data,dateTime);
						break;
					case CommonValues::waterType:
						data = message.data;
						greenHouseData[i].updateValue(String('water'),data,dateTime);
						break;
		      default:
		        break;
		  }
			greenHouseData[i].setLastChecked(millis());
			break;
	}

}

Message& GreenHouseHighLayer::prepareMessage(Message & message , int address) {
	message.source = CommonValues::highLayerAddress;
	message.dest = address;
	return message;
}

Message GreenHouseHighLayer::recieveRFMessage() {
  return this->communicationList.get(0)->receiveMessage();
};

void GreenHouseHighLayer::sendDataToServer(JsonObject& json) {
  JsonArray& jGreenHouses = json.createNestedArray("greenHouses");
  int i,j;

  for (i = 0 ; i < CommonValues::amountOfGreenHouses ; i++ ) {

      JsonObject& object = jGreenHouses.createNestedObject();
      object["id"] = this->greenHouseData[i].getId();

      JsonArray& dataArray = object.createNestedArray("data");

      for (j = 0 ; j < this->greenHouseData[i].getValuesSize() ; j++ ) {
          DataValue data = this->greenHouseData[i].getValue(j);
          JsonObject& jsonData = dataArray.createNestedObject();
          jsonData["key"] = data.name;
          jsonData["value"] = data.value;

					JsonObject& dateTime = jsonData.createNestedObject("dateTime");
					dateTime["year"] = data.dateTime.year;
					dateTime["month"] = data.dateTime.month;
					dateTime["date"] = data.dateTime.date;
					dateTime["hour"] = data.dateTime.hours;
					dateTime["minutes"] = data.dateTime.minutes;
					dateTime["seconds"] = data.dateTime.seconds;
      }

      this->communicationList.get(1)->sendMessage(json,"/data.php");

  }
}

void GreenHouseHighLayer::getNewSettings() {
  int i,j;
	Message messageArr[4];
	String name;
	float value;

  for (i = 0; i < CommonValues::amountOfGreenHouses; i++ ){
    int greenhouse = this->greenHouseData[i].getId();
    int index;
    String response;
    String url = "/options-updated.php?greenhouse=";
    url += greenhouse ;
    String last_updated = this->communicationList.get(1)->receiveMessage(url);

    index = this->findGreenHouseThresholdsIndex(greenhouse);

    if (last_updated != this->greenHouseThresholds[index].getLastUpdated()) {
      Serial.print("greeenhouse number ");
      Serial.print(greenhouse);
      Serial.print(" changed \n");

      this->greenHouseThresholds[index].setLastUpdated(last_updated);
      url = "/options.php?greenhouse=";
      url += greenhouse ;
      response = this->communicationList.get(1)->receiveMessage(url);

      StaticJsonBuffer<600> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(response);

      if (!root.success()) {
        Serial.println("parseObject() failed");
        return;
      }

      JsonObject& options = root["options"];

      for(JsonObject::iterator it=options.begin(); it!=options.end(); ++it) {
        this->greenHouseThresholds[index].updateValue(it->key,it->value);
      }

      //send rf message to greenhouse middle layer

			//initialize messages array
			messageArr[0].sensorType = CommonValues::humidityType;
			messageArr[0].messageType = CommonValues::policyChange;

			messageArr[1].sensorType = CommonValues::soilHumidityType;
			messageArr[1].messageType = CommonValues::policyChange;

			messageArr[2].sensorType = CommonValues::temperatureType;
			messageArr[2].messageType = CommonValues::policyChange;

			messageArr[3].sensorType = CommonValues::lightType;
			messageArr[3].messageType = CommonValues::policyChange;
			//
			// //iterate through the thresholds list
			for (j = 0 ; j < this->greenHouseThresholds[index].getValuesSize() ; j++ ) {
				ThresholdsValue value = this->greenHouseThresholds[index].getValue(j);
				if (value.name == "air_humidity_min") {
					messageArr[0].data = value.value;
				}
				if (value.name == "air_humidity_max") {
					messageArr[0].additionalData = value.value;
				}
				if (value.name == "soil_humidity_min") {
					messageArr[1].data = value.value;
				}
				if (value.name == "soil_humidity_max") {
					messageArr[1].additionalData = value.value;
				}
				if (value.name == "temperature_min") {
					messageArr[2].data = value.value;
				}
				if (value.name == "temperature_max") {
					messageArr[2].additionalData = value.value;
				}
				if (value.name == "luminance_min") {
					messageArr[3].data = value.value;
				}
				if (value.name == "luminance_max") {
					messageArr[3].additionalData = value.value;
				}
			}

			//send the messages
			for (j = 0 ; j < 4 ; j++ ) {
				this->prepareMessage(messageArr[j],greenhouse);
				this->communicationList.get(0)->sendMessage(messageArr[j]);
				delay(500);
			}

    }
  }
}

void GreenHouseHighLayer::checkMiddleLayer() {
	int i;
	StaticJsonBuffer<200> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();

	for (i = 0 ; i < CommonValues::amountOfGreenHouses; i++ ) {
		root["greenhouse"] = findGreenHouseDataIndex(i);
		//if the greenhouse has not contacted in the defined time
		if (millis() - greenHouseData[i].getLastChecked() >= CommonValues::MiddleLayerLostConnectionTime ) {
			//set it to not working state
			greenHouseData[i].setWorking(false);
			this->communicationList.get(0)->sendMessage(root, "/status.php");
		}
		else {
			if (!greenHouseData[i].getWorking()) {
				//set it back to working state
				greenHouseData[i].setWorking(true);
				this->communicationList.get(0)->sendMessage(root, "/status.php");
			}
		}
	}
}
