#include <wifi.h>

void wifi::init(String ssid, String password) {
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

String wifi::post(JsonObject& json, String url) {

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
  }

  Serial.println();
  Serial.println("closing connection");

  return line;
}

String wifi::get(String url) {
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