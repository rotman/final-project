#include "GreenHouseHighLayer.h"

void GreenHouseHighLayer::initLayer(int address) {
	int i;

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
    Serial.print("wrong id");
    return;
  }

  switch(message.sensorType) {
      case 'T':
        data = message.data;
        greenHouseData[i].updateValue(String("temperature"),data);
        break;
      case 'H':
        data = message.data;
        greenHouseData[i].updateValue(String('airHumidity'),data);
        break;
      case 'L':
        data = message.data;
        greenHouseData[i].updateValue(String('luminance'),data);
        break;
      case 'S':
        data = message.data;
        greenHouseData[i].updateValue(String('soilHumidity'),data);
        break;
      default:
        break;
  }

}

Message& GreenHouseHighLayer::prepareMessage(Message & message , int address) {
	message.source = CommonValues::highLayerAddress;
	message.dest = address;
	return message;
}

Message GreenHouseHighLayer::recieveRFMessage() {
  return this->communicationArray.get(0)->receiveMessage();
};

void GreenHouseHighLayer::sendDataToServer(JsonObject& json) {
  JsonArray& jGreenHouses = json.createNestedArray("greenHouses");
  int i,j;

	this->greenHouseData[0].updateValue("temperature",12.02);
	this->greenHouseData[0].updateValue("soil_humidity",1.02);

  for (i = 0 ; i < CommonValues::amountOfGreenHouses ; i++ ) {

      JsonObject& object = jGreenHouses.createNestedObject();
      object["id"] = this->greenHouseData[i].getId();

      JsonArray& dataArray = object.createNestedArray("data");

      for (j = 0 ; j < this->greenHouseData[i].getValuesSize() ; j++ ) {
          DataValue data = this->greenHouseData[i].getValue(j);
          JsonObject& jsonData = dataArray.createNestedObject();
          jsonData["key"] = data.name;
          jsonData["value"] = data.value;
      }

      this->communicationArray.get(1)->sendMessage(json,"/test.php");

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
    String last_updated = this->communicationArray.get(1)->receiveMessage(url);

    index = this->findGreenHouseThresholdsIndex(greenhouse);

    if (last_updated != this->greenHouseThresholds[index].getLastUpdated()) {
      Serial.print("greeenhouse number ");
      Serial.print(greenhouse);
      Serial.print(" changed \n");

      this->greenHouseThresholds[index].setLastUpdated(last_updated);
      url = "/options.php?greenhouse=";
      url += greenhouse ;
      response = this->communicationArray.get(1)->receiveMessage(url);

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

			//iterate through the thresholds list
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
				this->communicationArray.get(0)->sendMessage(messageArr[j]);
				delay(500);
			}

    }
  }
}
