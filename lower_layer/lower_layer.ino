#include <LowerLayer.h>
#include <STemptureHumidity.h>
#include <SLight.h>
#include <SSoil.h>
#include <PampActuator.h>
#include <message.h>
#include <CommonValues.h>

//globals
//-------
LowerLayer lowerLayer;
RF24 radio(7, 8);
CommonValues commonValues;

Sensor * tempHumidity;
Sensor * soil;
Sensor * light;

Actuator * pamp1;
Actuator * pamp2;

int tempHumidityPin = 2;
int soilPin = A0;
int lightPin = A1;

int pamp1Pin = 5;
int pamp2Pin = 6;

//available addresses
byte rxAddr[6] = "00001"; 
byte wxAddr[6] = "00002";             


void initConsole() {
  Serial.println("initConsole()");
  while (!Serial);
  Serial.begin(9600);
}

void createAndAddSensors() {
  Serial.println("createAndAddSensors()");
 
  tempHumidity= new STemptureHumidity(commonValues.humidityTemperatureSensorId, tempHumidityPin);              //create new temperature sensor instanse
  Serial.println("STemptureHumidity created");

  light= new SLight(commonValues.lightSensorId, lightPin);              //create new light sensor instanse
  Serial.println("Slight created");

  soil= new SSoil(commonValues.soil1SensorId, soilPin);              //create new soil sensor instanse
  Serial.println("Ssoil created");
  
  lowerLayer.addSensor(tempHumidity);
  lowerLayer.addSensor(soil);
  lowerLayer.addSensor(light);
}

void createAndAddActuators() {
  Serial.println("createAndAddActuators()");
  
  pamp1 = new PampActuator(commonValues.pamp1ActuatorId, pamp1Pin);
  Serial.println("PampActuator 1 created");
  
  pamp2 = new PampActuator(commonValues.pamp2ActuatorId, pamp2Pin);
  Serial.println("PampActuator 2 created");

  lowerLayer.addActuator(pamp1);
  lowerLayer.addActuator(pamp2);

  
}
void setup() {
  Serial.println("setup()");
  initConsole();
  lowerLayer.initLayer(commonValues.lowerLayerAddress);
  lowerLayer.initCommunication(radio, rxAddr, wxAddr);
  createAndAddSensors();
  createAndAddActuators();

}

//add source and destination to message
Message prepareMessage(Message& message) {
  message.source = commonValues.lowerLayerAddress;
  message.dest = commonValues.middleLayerAddress;
  return message;
}

void loop() {
  Serial.println("loop()");
  LinkedList<Message> sensorsData = lowerLayer.readSensorsData();
  for (int i = 0; i<sensorsData.size(); ++i) {
    Message message = sensorsData.get(i);
    Serial.println(message.sensorType);
    Serial.println(message.data);
    prepareMessage(message);
    lowerLayer.sendMessage(radio, message);
  }
   
  Message messageToRead = lowerLayer.receiveMessage(radio);
    Serial.print("main loop, i got: ");
    Serial.println(messageToRead.minimum_threshold);
    Serial.print("and: ");
    Serial.println(messageToRead.maximum_threshold);
    delay(3000);
}
