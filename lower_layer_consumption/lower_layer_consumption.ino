#include <GreenHouseLowerLayer.h>
#include <SCurrent.h>
#include <SWater.h>

//globals
//-------
GreenHouseLowerLayer lowerLayer;

//sensors
Sensor * currentSensor;
Sensor * waterSensor;

//pins
int currentPin = CommonValues::currentConsumptionPin;
int waterPin = CommonValues::waterConsumptionPin;

void initConsole() {
  Serial.println("initConsole()");
  while (!Serial);
  Serial.begin(9600);
}

void createAndAddSensors() {
  Serial.println("createAndAddSensors()");
 
  currentSensor = new SCurrent(CommonValues::currentSensorId, currentPin);              //create new current sensor instanse
  Serial.println("SCurrent created");

  waterSensor = new SWater(CommonValues::waterFlowSensorId, waterPin);              //create new water sensor instanse
  Serial.println("SWater created");
  
  lowerLayer.addSensor(currentSensor);
  lowerLayer.addSensor(waterSensor);
}

void setup() {
  initConsole();
  Serial.println("setup()");
  lowerLayer.initLayer(CommonValues::lowerLayerConsumptionAdress);
  createAndAddSensors();
}

void loop() {
  Serial.println("loop()");
  //analyze the data from all the sensors
  lowerLayer.analyze();

  //handle with received messages
  //messageToRead = lowerLayer.receiveMessage();
  //lowerLayer.decodeMessage(*messageToRead);
  
  delay(lowerLayer.getLoopTime());
}
