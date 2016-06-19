#include <GreenHouseMiddleLayer.h>
#include <GreenHouseActuator.h>
#include <CommonValues.h>
#include <Message.h>

//globals
//-------
GreenHouseMiddleLayer middleLayer;
DateTime mockDate;


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
  mockDate.year = 88;
  mockDate.month = 11;
  mockDate.date = 26;
  mockDate.minutes = 55;
  mockDate.hours = 16;
  mockDate.seconds = 55;

}


void loop() {
  Serial.println("loop()");
  
  Message message;
  middleLayer.receiveMessage(message);
  message.dateTime = mockDate;
  middleLayer.decodeMessage(message);

//   Message msg;
// msg.sensorType = CommonValues::temperatureType;
// msg.messageType = CommonValues::dataType;
// msg.dateTime = mockDate;
// msg.data = 34.34;
// middleLayer.prepareMessage(msg, CommonValues::highLayerAddress); 
//  middleLayer.sendMessage(msg);

  delay(3000);

}
