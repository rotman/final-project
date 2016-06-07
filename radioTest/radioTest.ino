#include <LowerLayer.h>
#include <FanActuator.h>
#include <CommonValues.h>


RF24 radio(7, 8);
LowerLayer lowerLayer;
CommonValues commonValues;
FanActuator fan(commonValues.fan1ActuatorId, 2);

byte rxAddr[6] = "00002";
byte wxAddr[6] = "00001";

void initConsole() {
  while (!Serial);
  Serial.begin(9600);
}

void setup() {
  initConsole();
  lowerLayer.initLayer(commonValues.lowerLayerAddress);
  lowerLayer.initCommunication(radio, rxAddr, wxAddr);
  
}

void loop() {
  Message msg;
  msg.sensorType = 'T';
  msg.data = 34.34;
  lowerLayer.sendMessage(radio, msg);

}
