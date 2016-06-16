#include "GreenHouseHighLayer.h"
#include "CommonValues.h"

GreenHouseHighLayer layer;

unsigned long lastTimeSentToServer = 0;
unsigned long lastTimeCheckedForNewSettings = 0;

void setup() {
  Serial.begin(115200);
  delay(10);
  layer.initLayer(0);

}

void loop() {
  int i;
  delay(1000);
  StaticJsonBuffer<2000> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["key"] = String(CommonValues::key);

  unsigned long now = millis();
  //try to read RF message from lower level
  Message RFMessage = layer.recieveRFMessage();

  if ('z' != RFMessage.sensorType && 201 == RFMessage.dest) {
      layer.decodeMessage(RFMessage);
  }

  //if it passeed xxx seconds from the last time we sent to the server than send
  if (now - lastTimeSentToServer >= CommonValues::sendToServerInterval ) {
    Serial.println("sending data to the server");
    lastTimeSentToServer = now;
    layer.sendDataToServer(root);
  }

  //if it passeed xxx seconds from the last time we checked for new settings
  if (now - lastTimeCheckedForNewSettings >= CommonValues::checkedForNewSettingsInterval ) {
    Serial.println("checking for new update");
    lastTimeCheckedForNewSettings = now;
    layer.getNewSettings();
  }
}
