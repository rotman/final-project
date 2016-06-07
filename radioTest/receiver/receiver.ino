#include <MiddleLayer.h>
#include <CommonValues.h>

RF24 radio(7, 8);
MiddleLayer middleLayer;
CommonValues commonValues;


byte rxAddr[6] = "00001";
byte wxAddr[6] = "00002";

void initConsole() {
  while (!Serial);
  Serial.begin(9600);
}

void setup() {
  initConsole();
  middleLayer.initLayer(commonValues.middleLayerAddress);
  middleLayer.initCommunication(radio, rxAddr, wxAddr);
}

void loop() {
  Message message = middleLayer.receiveMessage(radio);
  if (message.sensorType != 'z') {
    Serial.println("message is NOT null"); 
    Serial.println(message.sensorType);
    Serial.println(message.data);
  }
  else {
    Serial.println("message is null"); 
  }


}
