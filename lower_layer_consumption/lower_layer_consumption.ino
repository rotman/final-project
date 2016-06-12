#include <GreenHouseLowerLayer.h>
#include <SCurrent.h>
#include <SWater.h>

//globals
//-------
GreenHouseLowerLayer lowerLayer;
Radio* radio;

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
  Serial.println("setup()");
  initConsole();
  lowerLayer.initLayer(CommonValues::lowerLayerConsumptionAdress);
  createAndAddSensors();
  radio = (Radio*)lowerLayer.getCommunicationArray().get(0);
}

void loop() {
  Serial.println("loop()");
  //analyze the data from all the sensors
  lowerLayer.analyze();
  
  delay(3000);
}
