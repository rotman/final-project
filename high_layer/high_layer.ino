#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
//#include <nRF24L01.h>
//#include <RF24.h>
#include <message.h>

// globals
//-------

#define MIDDLE_LAYER_ADDRESS 101
#define MY_ADDRESS 201
#define AmountOfGreenHouses 1

const char* ssid = "Lugasi-2.4";
const char* password = "navelu123";

const char* host = "www.graphical-transformation.netau.net";

const char* key = "123456";

String path = "/test.php";



unsigned long lastTimeSentToServer = 0;
long sendToServerInterval = 5000;
int counter = 0;

//RF24 radio(7, 8);

struct SensorData {
  String data;
  long timestamp;
};

struct GreenHouseData {
  int id;
  SensorData humidity;
  SensorData temperature;
};

GreenHouseData greenHouseArray[AmountOfGreenHouses];

const byte rxAddr[6] = "00001";
const byte wxAddr[6] = "00002";

//void sendMessage(Message message){
//  Serial.println("sendMessage()");
//  bool ok = false;
//  int retry_times = 30;
//  radio.stopListening();
//  while(!ok && --retry_times){  //if message fails , retry 30 times
//    Serial.print("retry: ");
//    Serial.println(retry_times  );
//    ok =  radio.write(&message, sizeof(message));
//    if(ok){
//      Serial.println("send seccess");
//    }
//    else {
//      Serial.println("send failed");
//    }
//  }
//  radio.startListening();
//}
//
//Message prepareRFMessage(Message message){
//  message.source = MY_ADDRESS;
//  message.dest = MIDDLE_LAYER_ADDRESS;
//  return message;
//}
//
//Message recieveRFMessage(){
//  Message message;
//  if (radio.available()){
//    radio.read(&message, sizeof(message));
//    Serial.print("recived message:");
//    Serial.println(message.data);
//    return message;
//  }
//  else{
//    Serial.println("nothing to read");
//    message.sensorType = 'z';
//    return message;
//  }
//}

void initConsole() {
  Serial.begin(115200);
  delay(10);
}

//void initRadio() {
//    Serial.println("initRadio()");
//    radio.begin();
//    radio.setRetries(15, 15);
//    radio.openWritingPipe(wxAddr);
//    radio.openReadingPipe(1,rxAddr);
//    radio.stopListening();
//}

void initWifi() {
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.disconnect();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void initGreenhousesArray() {
    int i;
    for (i = 0 ; i < AmountOfGreenHouses ; i++ ) {
        greenHouseArray[i].id = 101 + i ;
    }
}

int findGreenHouseIndex(int id) {
  int i, result;
  for (i = 0 ; i < AmountOfGreenHouses ; i++ ) {
    if (id == greenHouseArray[i].id)
      result = i;
  }
  return result;
}

void decodeRFMessage(Message message) {

    int greenhouseId = message.source;
    int i = findGreenHouseIndex(greenhouseId);
    String integerPart;
    String fractionalPart;
    String data;
    if (AmountOfGreenHouses == i) {
      Serial.print("wrong id");
      return;
    }

    switch(message.sensorType) {
        case 'T':
          integerPart = String(message.data[0],DEC);
          fractionalPart = String(message.data[2],DEC);
          data = integerPart + "." + fractionalPart;
          greenHouseArray[i].temperature.data = data;
          greenHouseArray[i].temperature.timestamp = millis();
          break;
        case 'H':
          integerPart = String(message.data[0],DEC);
          fractionalPart = String(message.data[2],DEC);
          data = integerPart + "." + fractionalPart;
          greenHouseArray[i].humidity.data = data;
          greenHouseArray[i].humidity.timestamp = millis();
          break;
        default:
          break;

    }

}


void sendDataToServer(JsonObject& json) {

  WiFiClient client;

  Serial.print("Trying to Establish connection with  ");
  Serial.println(host);

  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  int length = json.measureLength();

  Serial.println("connection successs");

  String url = "/test.php";

  // POST URI
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n" +
               "Content-Type: application/json\r\n" +
               "Content-Length:" + String(length) + "\r\n\r\n");

  //POST message body
  String out;
  json.printTo(out);
  Serial.println("sending json: ");
  Serial.println(out);
  client.println(out);

  //print respone
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");
}

void buildRequestJson(JsonObject& json) {
  JsonArray& jGreenHouses = json.createNestedArray("greenHouses");
  int i;

  for (i = 0 ; i < AmountOfGreenHouses ; i++ ) {

      JsonObject& object = jGreenHouses.createNestedObject();
      object["id"] = greenHouseArray[i].id;

      JsonObject& humidity = object.createNestedObject("humidity");
      humidity["data"] = greenHouseArray[i].humidity.data;
      humidity["timestamp"] = greenHouseArray[i].humidity.timestamp;

      JsonObject& temperature = object.createNestedObject("temperature");
      temperature["data"] = greenHouseArray[i].temperature.data;
      temperature["timestamp"] = greenHouseArray[i].temperature.timestamp;

  }

}

void setup() {
  initGreenhousesArray();
  initConsole();
  //initRadio();
  initWifi();
}

void loop() {
  delay(1000);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["key"] = String(key);

  unsigned long now = millis();
  //try to read RF message from lower level
  //Message RFMessage = recieveRFMessage();

  Message RFMessage;
  RFMessage.dest = 201;
  RFMessage.sensorType = 'T';
  RFMessage.data[0] = counter + 1;
  RFMessage.data[2] = 1;
  counter++;

  if ('z' != RFMessage.sensorType && 201 == RFMessage.dest) {
    decodeRFMessage(RFMessage);
  }


  //if it passeed xxx seconds from the last time we sent to the server than send
  if (now - lastTimeSentToServer >= sendToServerInterval ) {
    lastTimeSentToServer = now;
    buildRequestJson(root);
    sendDataToServer(root);
  }


}
