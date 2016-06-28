#include <GreenHouseLowerLayer.h>
#include <STemptureHumidity.h>
#include <SLight.h>
#include <SSoil.h>
#include <GreenHouseActuator.h>
//globals
//-------
GreenHouseLowerLayer lowerLayer;

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
  Serial.println("initConsole()");
  while (!Serial);
  Serial.begin(9600);
}

void createAndAddSensors() {
  Serial.println("createAndAddSensors()");
 
  tempHumidity= new STemptureHumidity(CommonValues::humidityTemperatureSensorId, tempHumidityPin);              //create new temperature sensor instanse
  Serial.println("STemptureHumidity created");

  light= new SLight(CommonValues::lightSensorId, lightPin);              //create new light sensor instanse
  Serial.println("Slight created");

  soil= new SSoil(CommonValues::soil1SensorId, soilPin);              //create new soil sensor instanse
  Serial.println("Ssoil created");

    
  lowerLayer.addSensor(tempHumidity);
  lowerLayer.addSensor(soil);
  lowerLayer.addSensor(light);
}

void createAndAddActuators() {
  Serial.println("createAndAddActuators()");
  pump = new GreenHouseActuator(CommonValues::pumpPin);
  Serial.println("PumpActuator created");
  lowerLayer.addActuator(pump);
}


void setup() {
  Serial.println("setup()");
  initConsole();
  lowerLayer.initLayer(CommonValues::lowerLayerAddress1);
  createAndAddSensors();
  createAndAddActuators();
 
}

void loop() {
  Serial.println("loop()");
  //analyze the data from all the sensors
  lowerLayer.analyze(); 

 //handle with received messages
 // Message messageToRead;
  //lowerLayer.receiveMessage(messageToRead);
  //lowerLayer.decodeMessage(messageToRead);  

  delay(lowerLayer.getLoopTime());
}
