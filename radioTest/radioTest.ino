#include <GreenHousePlatform.h>

RF24 radio(7, 8);
GreenHousePlatform greenHousePlatform;


byte rxAddr[6] = "00002";
byte wxAddr[6] = "00001";

void initConsole() {
  while (!Serial);
  Serial.begin(9600);
}

void setup() {
  initConsole();
  greenHousePlatform.init(radio, rxAddr, wxAddr);
}

void loop() {
  Message msg;
  msg.sensorType = 'T';
  msg.data = 34.34;
  greenHousePlatform.sendMessage(radio, msg);

}
