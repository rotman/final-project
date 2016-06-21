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
Message createFakeMessage(){
  if (Serial.available()) {      // Look for char in serial queue and process if found
    Message message;
    message.messageType =(char)Serial.read();
    message.sensorType =(char)Serial.read();
    message.data = (float)((Serial.read()*10)+Serial.read());
    message.additionalData = (float)Serial.read();
    middleLayer.prepareMessage(message,CommonValues::highLayerAddress);
    middleLayer.sendMessage(message);
  }
}

void setup() {
  initConsole();
  middleLayer.initLayer(CommonValues::fakeMiddleLayerAddress);
}


void loop() {
  Serial.print("loop()");
  createFakeMessage();
  Message message;
  middleLayer.receiveMessage(message);
  delay(middleLayer.getLoopTime());
}
