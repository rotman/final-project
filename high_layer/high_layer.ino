#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <TimeLib.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <message.h>

// globals
//-------

#define MIDDLE_LAYER_ADDRESS 101
#define MY_ADDRESS 201
#define AmountOfGreenHouses 1

const char* ssid = "***";
const char* password = "**";

const char* host = "www.graphical-transformation.netau.net";

const char* key = "123456";

unsigned long lastTimeSentToServer = 0;
long sendToServerInterval = 5000;

unsigned long lastTimeCheckedForNewSettings = 0;
long checkedForNewSettingsInterval = 10000;

RF24 radio(2, 15);

struct GreenHouseData {
  int id;
  String airHumidity;
  String temperature;
  String luminance;
  String soilHumidity;
};

struct GreenHouseSettings {
  int id;
  String last_updated;
  double airHumidityMax;
  double airHumidityMin;
  double luminanceMax;
  double luminanceMin;
  double temperatureMax;
  double temperatureMin;
  double soilHumidityMax;
  double soilHumidityMin;
};

//data recived from middle layer array
GreenHouseData greenHouseArray[AmountOfGreenHouses];

//setting data
GreenHouseSettings settingsArray[AmountOfGreenHouses];

const byte rxAddr[6] = "00001";
const byte wxAddr[6] = "00002";

void sendMessage(Message message){
  Serial.println("sendMessage()");
  bool ok = false;
  int retry_times = 30;
  radio.stopListening();
  while(!ok && --retry_times){  //if message fails , retry 30 times
    Serial.print("retry: ");
    Serial.println(retry_times  );
    ok =  radio.write(&message, sizeof(message));
    if(ok){
      Serial.println("send seccess");
    }
    else {
      Serial.println("send failed");
    }
  }
  radio.startListening();
}

Message prepareRFMessage(Message message){
  message.source = MY_ADDRESS;
  message.dest = MIDDLE_LAYER_ADDRESS;
  return message;
}


Message recieveRFMessage(){
  Message message;
  if (radio.available()){
    radio.read(&message, sizeof(message));
    Serial.print("recived message:");
    Serial.println(message.data);
    return message;
  }
  else{
    Serial.println("nothing to read");
    message.sensorType = 'z';
    return message;
  }
}

void initConsole() {
  Serial.begin(115200);
  delay(10);
}

void initRadio() {
    Serial.println("initRadio()");
    radio.begin();
    radio.setRetries(15, 15);
    radio.openWritingPipe(wxAddr);
    radio.openReadingPipe(1,rxAddr);
    radio.startListening();
}

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

void initSettingsArray() {
    int i;
    for (i = 0 ; i < AmountOfGreenHouses ; i++ ) {
        settingsArray[i].id = 101 + i ;
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

int findGreenHouseSettingsIndex(int id) {
  int i, result;
  for (i = 0 ; i < AmountOfGreenHouses ; i++ ) {
    if (id == settingsArray[i].id)
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
          data = String(message.data);
          greenHouseArray[i].temperature = data;
          break;
        case 'H':
          data = String(message.data);
          greenHouseArray[i].airHumidity = data;
          break;
        case 'L':
            data = String(message.data);
            greenHouseArray[i].luminance = data;
            break;
        case 'S':
            data = String(message.data);
            greenHouseArray[i].soilHumidity = data;
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

      JsonArray& dataArray = object.createNestedArray("data");

      JsonObject& temperatureData = dataArray.createNestedObject();
      temperatureData["key"] = "temperature";
      temperatureData["value"] = greenHouseArray[i].temperature;

      JsonObject& airHumidityData = dataArray.createNestedObject();
      airHumidityData["key"] = "airHumidity";
      airHumidityData["value"] = greenHouseArray[i].airHumidity;

      JsonObject& luminanceData = dataArray.createNestedObject();
      luminanceData["key"] = "luminance";
      luminanceData["value"] = greenHouseArray[i].luminance;

      JsonObject& soilHumidityData = dataArray.createNestedObject();
      soilHumidityData["key"] = "soilHumidity";
      soilHumidityData["value"] = greenHouseArray[i].soilHumidity;

      sendDataToServer(object);

  }

}

String wifiGet(String url) {
  WiFiClient client;

  Serial.print("Trying to Establish connection with  ");
  Serial.println(host);

  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return "";
  }

  Serial.println("connection successs");


    // This will send the request to the server
   client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "Connection: close\r\n\r\n");
   unsigned long timeout = millis();
   while (client.available() == 0) {
     if (millis() - timeout > 5000) {
       Serial.println(">>> Client Timeout !");
       client.stop();
       return "";
     }
   }

  String response = "";
  // Read all the lines of the reply from server and print them to Serial



  int isBody = 0;

  while(client.available()){
     String line = client.readStringUntil('\r');
     if (isBody == 0) {
       if (line == "\n") {
         isBody = 1;
       }
     }
     else {
       response += line;
     }

  }

  return response;

}

void getNewSettings(int greenhouse) {
  int index;
  String response;
  String url = "/options-updated.php?greenhouse=";
  url += greenhouse ;

  String last_updated = wifiGet(url);

  index = findGreenHouseSettingsIndex(greenhouse);

  if (last_updated != settingsArray[index].last_updated) {
      Serial.print("greeenhouse number ");
      Serial.print(greenhouse);
      Serial.print(" changed \n");

      settingsArray[index].last_updated = last_updated;
      url = "/options.php?greenhouse=";
      url += greenhouse ;
      response = wifiGet(url);
      StaticJsonBuffer<600> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(response);
      if (!root.success()) {
        Serial.println("parseObject() failed");
        return;
      }

      settingsArray[index].airHumidityMax = root["options"]["airHumidityMax"];
      settingsArray[index].airHumidityMin = root["options"]["airHumidityMin"];
      settingsArray[index].luminanceMax = root["options"]["luminanceMax"];
      settingsArray[index].luminanceMin = root["options"]["luminanceMin"];
      settingsArray[index].temperatureMax = root["options"]["temperatureMax"];
      settingsArray[index].temperatureMin = root["options"]["temperatureMin"];
      settingsArray[index].soilHumidityMax = root["options"]["soilHumidityMax"];
      settingsArray[index].soilHumidityMin = root["options"]["soilHumidityMin"];

      //send rf message to greenhouse middle layer
  }

}

void setup() {
  initGreenhousesArray();
  initSettingsArray();
  initConsole();
  initRadio();
  initWifi();
}

void loop() {
  int i;
  delay(2000);
  StaticJsonBuffer<2000> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["key"] = String(key);

  unsigned long now = millis();
  //try to read RF message from lower level
  Message RFMessage = recieveRFMessage();

  if ('z' != RFMessage.sensorType && 201 == RFMessage.dest) {
      decodeRFMessage(RFMessage);
  }

  //if it passeed xxx seconds from the last time we sent to the server than send
  if (now - lastTimeSentToServer >= sendToServerInterval ) {
    Serial.println("sending data to the server");
    lastTimeSentToServer = now;
    buildRequestJson(root);
    sendDataToServer(root);
  }

  //if it passeed xxx seconds from the last time we checked for new settings
  if (now - lastTimeCheckedForNewSettings >= checkedForNewSettingsInterval ) {
    Serial.println("checking for new update");
    lastTimeCheckedForNewSettings = now;
    for ( i = 0; i < AmountOfGreenHouses ; i++ ) {
        getNewSettings(settingsArray[i].id);
    }
  }

}
