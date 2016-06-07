#include <LowerLayer.h>
#include <STemptureHumidity.h>
#include <SLight.h>
#include <SSoil.h>
#include <PampActuator.h>
#include <Actions.h>

//globals
//-------
LowerLayer lowerLayer;
RF24 radio(CommonValues::radioPin1, CommonValues::radioPin2);

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
  
  pump = new PampActuator(CommonValues::pumpActuatorId, pumpPin);
  Serial.println("PumpActuator created");

  lowerLayer.addActuator(pump);
  

  
}
void setup() {
  Serial.println("setup()");
  initConsole();
  lowerLayer.initLayer(CommonValues::lowerLayerAddress);
  lowerLayer.initCommunication(radio, rxAddr, wxAddr);
  createAndAddSensors();
  createAndAddActuators();
}

//add source and destination to message
Message prepareMessage(Message& message, Actions action) {
  message.source = CommonValues::lowerLayerAddress;
  message.dest = CommonValues::middleLayerAddress;
  message.action = action;
  return message;
}

Actions actuateIfNeeded(float data, char which) {
  if (data < CommonValues::soilHumidityThresholdMin) {
      lowerLayer.actuate(pump, true);
      return PUMP1;      
  }
  else {
    return NONE;
  }
}

void loop() {
  Serial.println("loop()");
  LinkedList<Message> sensorsData = lowerLayer.readSensorsData();
  for (int i = 0; i<sensorsData.size(); ++i) {
    Message message = sensorsData.get(i);
    Serial.println(message.sensorType);
    Serial.println(message.data);
    Actions action;
    if (message.sensorType == 'S') {
      action = actuateIfNeeded(message.data,message.messageType);
    }
    prepareMessage(message, action);
    lowerLayer.sendMessage(radio, message);
  }
   
  Message messageToRead = lowerLayer.receiveMessage(radio);
    Serial.print("main loop, i got: ");
    Serial.println(messageToRead.minimum_threshold);
    Serial.print("and: ");
    Serial.println(messageToRead.maximum_threshold);
    delay(3000);
}
