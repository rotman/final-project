#include <GreenHouseLowerLayer.h>
#include <SCurrent.h>
#include <SWater.h>

//globals
//-------
GreenHouseLowerLayer lowerLayer;

//sensors
Sensor * currentSensor;
Sensor * waterSensor1;
Sensor * waterSensor2;


//pins
int currentPin = CommonValues::currentConsumptionPin;
int waterPin1 = CommonValues::waterConsumptionPin1;
int waterPin2 = CommonValues::waterConsumptionPin2;

void initConsole() {
  Serial.println("initConsole()");
  while (!Serial);
  Serial.begin(9600);
}

void createAndAddSensors() {
  Serial.println("createAndAddSensors()");
  currentSensor = new SCurrent(CommonValues::currentSensorId, currentPin);            
  waterSensor1 = new SWater(CommonValues::waterFlowSensorId, waterPin1);              
  waterSensor2 = new SWater(CommonValues::waterFlowSensorId, waterPin2);            

  lowerLayer.addSensor(currentSensor);
  lowerLayer.addSensor(waterSensor1);
  lowerLayer.addSensor(waterSensor2);
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
  
  delay(lowerLayer.getLoopTime());
}
