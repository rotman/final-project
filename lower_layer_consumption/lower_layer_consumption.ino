#include <LowerLayer.h>
#include <SCurrent.h>
#include <SWater.h>

//globals
//-------
LowerLayer lowerLayer;
RF24 radio(7, 8);
CommonValues commonValues;

Sensor * current;
Sensor * water;

//this values are just for example
int currentPin = 3;
int waterPin = 4;

//available addresses
byte rxAddr[6] = "00001"; 
byte wxAddr[6] = "00002";

void initConsole() {
  Serial.println("initConsole()");
  while (!Serial);
  Serial.begin(9600);
}

void createAndAddSensors() {
  Serial.println("createAndAddSensors()");
 
  current= new SCurrent(commonValues.currentSensorId, currentPin);              //create new current sensor instanse
  Serial.println("SCurrent created");

  water= new SWater(commonValues.waterFlowSensorId, waterPin);              //create new water sensor instanse
  Serial.println("SWater created");
  
  lowerLayer.addSensor(current);
  lowerLayer.addSensor(water);
}

void setup() {
  Serial.println("setup()");
  initConsole();
  lowerLayer.initLayer(commonValues.lowerLayerConsumptionAdress);
  lowerLayer.initCommunication(radio, rxAddr, wxAddr);
  createAndAddSensors();
}

Message prepareMessage(Message& message) {
  message.source = commonValues.lowerLayerConsumptionAdress;
  message.dest = commonValues.middleLayerAddress;
  return message;
}

void loop() {
  Serial.println("loop()");
  LinkedList<Message> sensorsData = lowerLayer.readSensorsData();
  for (int i = 0; i<sensorsData.size(); ++i) {
    Message message = sensorsData.get(i);
    Serial.println(message.sensorType);
    Serial.println(message.data);
    prepareMessage(message);
    lowerLayer.sendMessage(radio, message);
  }
  

}
