#include <LowerLayer.h>
#include <message.h>
#include <CommonValues.h>
#include <SCurrent.h>
#include <SWater.h>

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
  Serial.println("addSensors()");
 
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
  lowerLayer.initLayer();
  lowerLayer.initCommunication(radio, rxAddr, wxAddr);
  createAndAddSensors();
}

void loop() {
  // put your main code here, to run repeatedly:

}
