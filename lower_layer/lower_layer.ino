#include <LowerLayer.h>
#include <STemptureHumidity.h>
#include <SLight.h>
#include <SSoil.h>
#include <message.h>
#include <CommonValues.h>


#define MIDDLE_LAYER_ADDRESS 101  
#define MY_ADDRESS 1  

//globals
//-------
LowerLayer lowerLayer;
RF24 radio(7, 8);
CommonValues commonValues;
Sensor* sensorsArray[3];
Sensor * tempHumidity;
Sensor * soil;
Sensor * light;

int tempHumidityPin = 2;
int soilPin = A0;
int lightPin = A1;

int soil_humidity_threshold_minimum = 40;
int soil_humidity_threshold_maximmum = 40;

//available addresses
byte rxAddr[6] = "00001"; 
byte wxAddr[6] = "00002";             


void initConsole() {
  Serial.println("initConsole()");
  while (!Serial);
  Serial.begin(9600);
}

void createAndAddSensors() {
  Serial.println("addSensors()");
 
  tempHumidity= new STemptureHumidity(commonValues.humidityTemperatureSensorId, tempHumidityPin);              //create new temperature sensor instanse
  Serial.println("STemptureHumidity created");

  light= new SLight(commonValues.lightSensorId, lightPin);              //create new light sensor instanse
  Serial.println("Slight created");

  soil= new SSoil(commonValues.soilSensorId, soilPin);              //create new soil sensor instanse
  Serial.println("Ssoil created");
  
  lowerLayer.addSensor(tempHumidity);
  lowerLayer.addSensor(soil);
  lowerLayer.addSensor(light);
}

void setup() {
  Serial.println("setup()");
  initConsole();
  lowerLayer.initLayer();
  lowerLayer.initCommunication(radio, rxAddr, wxAddr);
  createAndAddSensors();

  sensorsArray[0] = tempHumidity;
  sensorsArray[1] = light;
  sensorsArray[2] = soil; 

}
  
Message prepareMessage(Message message) {
  message.source = MY_ADDRESS;
  message.dest = MIDDLE_LAYER_ADDRESS;
  return message;
}

void readPrepareSend(Sensor * sensor,bool isHumidity){
  Message readSensor =  sensor->readSensorData(isHumidity);          //read sensor data
  Message messageToSend = prepareMessage(readSensor);             //add sender id and receiver id to message
  Serial.print("sensorType=");
  Serial.println(messageToSend.sensorType);
  Serial.print("dest=");
  Serial.println(messageToSend.dest);
  Serial.print("data =");
  Serial.println(messageToSend.data);
 // sendMessage(messageToSend);                                   //send message  
}

void loop() {
  Serial.println("loop()");
  LinkedList<Message> sensorsData = lowerLayer.readSensorsData();
  for (int i = 0; i<sensorsData.size(); ++i){
    Serial.println(sensorsData.get(i).sensorType);
    Serial.println(sensorsData.get(i).data);

    readPrepareSend(sensorsArray[i],false);
    if(i==0)
    readPrepareSend(sensorsArray[i],true);
  }
   
  Message messageToRead = lowerLayer.receiveMessage(radio);
    Serial.print("main loop, i got: ");
    Serial.println(messageToRead.minimum_threshold);
    Serial.print("and: ");
    Serial.println(messageToRead.maximum_threshold);
  
  delay(3000);
}
