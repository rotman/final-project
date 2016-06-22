#include <GreenHouseMiddleLayer.h>
#include <GreenHouseActuator.h>
#include <CommonValues.h>
#include <Message.h>
//globals
//-------
GreenHouseMiddleLayer middleLayer;


void initConsole() {
  while (!Serial);  
  Serial.begin(9600);
}

//Example: dT300  for message type data,sensor type temperature , 30 degrees, with no additionalData data
void createFakeMessage(Message& message){
  if (Serial.available()) {      // Look for char in serial queue and process if found
    message.messageType =(char)Serial.read();
    message.sensorType =(char)Serial.read();
    message.data = (float)(((Serial.read()-48)*10)+Serial.read()-48);
    message.additionalData = (float)Serial.read();
    middleLayer.prepareMessage(message,CommonValues::highLayerAddress);
  }
}

void setup() {
  initConsole();
  middleLayer.initLayer(CommonValues::fakeMiddleLayerAddress);
}


void loop() {
  Serial.print("loop()");
  Message fakeMessage;
  createFakeMessage(fakeMessage);
  middleLayer.sendMessage(fakeMessage);
  Message message;
  middleLayer.receiveMessage(message);
  delay(middleLayer.getLoopTime());
}
