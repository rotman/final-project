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
int fan1Pin = CommonValues::fan1Pin;
int fan2Pin = CommonValues::fan2Pin;  
int lampPin = CommonValues::lampPin;
int heatPin = CommonValues::heatPin;
int steamPin = CommonValues::steamPin;


void initConsole() {
  while (!Serial);  
  Serial.begin(9600);
}


void createAndAddActuators() { 
  fan1Actuator = new GreenHouseActuator(CommonValues::fan1Pin);
  fan2Actuator = new GreenHouseActuator(CommonValues::fan2Pin);
  lightActuator = new GreenHouseActuator(CommonValues::lampPin);
  heatActuator = new GreenHouseActuator(CommonValues::heatPin);
  steamActuator = new GreenHouseActuator(CommonValues::steamPin);
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
  Serial.print("loop()   freeMemory()=");
  Serial.println(freeMemory()); 
  Message message;
  middleLayer.receiveMessage(message);
  middleLayer.decodeMessage(message);

  delay(middleLayer.getLoopTime());
}
