#include <GreenHouseMiddleLayer.h>
#include <GreenHouseActuator.h>
#include <CommonValues.h>
#include <Message.h>
#include <MemoryFree.h>
//globals
//-------
GreenHouseMiddleLayer middleLayer;

//actuators
Actuator * fan1Actuator;
Actuator * fan2Actuator;
Actuator * lightActuator;
Actuator * heatActuator;
Actuator * steamActuator;

//pins
int fanPin = CommonValues::fanPin;
int ventPin = CommonValues::ventPin;  
int lampPin = CommonValues::lampPin;
int heatPin = CommonValues::heatPin;
int steamPin = CommonValues::steamPin;


void initConsole() {
  while (!Serial);  
  Serial.begin(9600);
}


void createAndAddActuators() { 
  fan1Actuator = new GreenHouseActuator(fanPin);
  fan2Actuator = new GreenHouseActuator(ventPin);
  lightActuator = new GreenHouseActuator(lampPin);
  heatActuator = new GreenHouseActuator(heatPin);
  steamActuator = new GreenHouseActuator( steamPin);
  middleLayer.addActuator(fan1Actuator);
  middleLayer.addActuator(fan2Actuator);
  middleLayer.addActuator(lightActuator);
  middleLayer.addActuator(heatActuator);
  middleLayer.addActuator(steamActuator);
}


void setup() {
  initConsole();
  middleLayer.initLayer(CommonValues::middleLayerAddress);
  createAndAddActuators();
}


void loop() {
  Serial.print("loop()");
  
  //handle with received messages
  LinkedList<Message> messages;
  middleLayer.receiveMessages(messages);
  for (int i = 0; i<messages.size(); i++) {
    middleLayer.decodeMessage(message);
  }

  Serial.print(F("Radio::sendCounter::::::::::::::::::"));
  Serial.println(Radio::sendCounter, DEC);
  Serial.print(F("Radio::receiveCounter::::::::::::::::::"));
  Serial.println(Radio::receiveCounter, DEC);
  
  middleLayer.getWatchDog().reset();
  
  //TODO maybe we donf need delay
  delay(middleLayer.getLoopTime());
}
