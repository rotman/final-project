#include <GreenHouseLowerLayer.h>
#include <STemptureHumidity.h>
#include <SLight.h>
#include <SSoil.h>
#include <GreenHouseActuator.h>
#include <MemoryFree.h>

//globals
//-------
GreenHouseLowerLayer lowerLayer;
Message messageToRead;

//sensors
Sensor * tempHumidity;
Sensor * soil;
Sensor * light;

//actuators
Actuator * pump;

  //pins    
int tempHumidityPin = CommonValues::tempHumidityPin;
int soilPin = CommonValues::soilPin;
int lightPin = CommonValues::lightPin;
int pumpPin = CommonValues::pumpPin;
          
void initConsole() {
  while (!Serial);
  Serial.begin(9600);
}

void createAndAddSensors() {
  tempHumidity= new STemptureHumidity(CommonValues::humidityTemperatureSensorId, tempHumidityPin);              //create new temperature sensor instanse
  light= new SLight(CommonValues::lightSensorId, lightPin);              //create new light sensor instanse
  soil= new SSoil(CommonValues::soil1SensorId, soilPin);              //create new soil sensor instanse
  lowerLayer.addSensor(tempHumidity);
  lowerLayer.addSensor(soil);
  lowerLayer.addSensor(light);
}

void createAndAddActuators() {
  pump = new GreenHouseActuator(CommonValues::pumpPin);
  lowerLayer.addActuator(pump);
}

void setup() {
  initConsole();
  Serial.println("setup()");
  lowerLayer.initLayer(CommonValues::lowerLayerAddress2);
  createAndAddSensors();
  createAndAddActuators();
}

void loop() {
  Serial.print("loop() freeMemory()=");
  Serial.println(freeMemory());

  //analyze the data from all the sensors
  lowerLayer.analyze(); 

  //handle with received messages
  lowerLayer.receiveMessage(messageToRead);
  lowerLayer.decodeMessage(messageToRead);
  
  delay(lowerLayer.getLoopTime());
}
