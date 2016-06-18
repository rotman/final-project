#include <GreenHouseMiddleLayer.h>
#include <GreenHouseActuator.h>
#include <CommonValues.h>
#include <Message.h>

//globals
//-------
GreenHouseMiddleLayer middleLayer;
RF24 radio(CommonValues::radioPin1 , CommonValues::radioPin2);
Message message;

//actuators
Actuator * fan1Actuator;
Actuator * fan2Actuator;
Actuator * lightActuator;
Actuator * heatActuator;
Actuator * steamActuator;
Actuator * steamerActuator;

//pins
int fan1Pin = CommonValues::fan1Pin;
int fan2Pin = CommonValues::fan2Pin;
int lightPin = CommonValues::lightPin;
int heatPin = CommonValues::heatPin;
int steamPin = CommonValues::steamPin;


void initConsole() {
  while (!Serial);
  Serial.begin(9600);
}

void createAndAddActuators() {
  Serial.println("createAndAddActuators()");
 
  fan1Actuator = new GreenHouseActuator(CommonValues::fan1Pin);
  fan2Actuator = new GreenHouseActuator(CommonValues::fan2Pin);
  lightActuator = new GreenHouseActuator(CommonValues::lightPin);
  heatActuator = new GreenHouseActuator(CommonValues::heatPin);
  steamActuator = new GreenHouseActuator(CommonValues::steamPin);

  middleLayer.addActuator(fan1Actuator);
  middleLayer.addActuator(fan2Actuator);
  middleLayer.addActuator(lightActuator);
  middleLayer.addActuator(heatActuator);
  middleLayer.addActuator(steamActuator);

}

void setup() {
  Serial.println("setup()");
  initConsole();
  middleLayer.initLayer(CommonValues::middleLayerAddress);
  createAndAddActuators();
}


void loop() {
  Serial.println("loop()");
  message = middleLayer.receiveMessage();
  middleLayer.decodeMessage(message);
  
  delay(middleLayer.getLoopTime());

}
