#include <GreenHousePlatform.h>

RF24 radio(7, 8);
GreenHousePlatform greenHousePlatform;

byte rxAddr[6] = "00001";
byte wxAddr[6] = "00002";

void initConsole() {
  while (!Serial);
  Serial.begin(9600);
}

void setup() {
  initConsole();
  greenHousePlatform.init(radio, rxAddr, wxAddr);
}

void loop() {
  Message message;
  message = greenHousePlatform.receiveMessage(radio);
  Serial.println(message.sensorType);
  Serial.println(message.data);

}
