#include <nRF24L01.h>
#include <RF24.h>
#include <message.h>
#include <SPI.h>

//globals
//-------
RF24 radio(7, 8);

const byte rxAddr[6] = "00002";
const byte wxAddr[6] = "00001";

void initConsole() {
  while (!Serial);
  Serial.begin(9600);
}

void initRadio() {
    radio.begin();
    radio.setRetries(15, 15);
    radio.openWritingPipe(wxAddr);
    radio.openReadingPipe(1,rxAddr);
    radio.startListening();
}


void setup() {
  initConsole();
  initRadio();
}


Message recieveMessage(){
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


void sendMessage(Message message){
    bool ok;
    int retry_times = 30;
    radio.stopListening();
    while(!ok && --retry_times){  //if message fails , retry 30 times
        ok =  radio.write(&message, sizeof(message));
        if(ok){
           Serial.println("send seccess");      
        }
        else{
             Serial.println("send failed ");
        }
        radio.startListening();
   }
}

void decodeMessage(Message msg) {
  //TODO check from which layer the message came from

  //if the meesgae came from high layer
  //we should change policy in this layer/bottom layer
  
  /*switch(msg->sensorType) {
  //need to change soil humidity treshold in the bottom layer
  case 'S':
  //maybe prepare diiferent message
  //change msg src and dest
  //sendMessage(msg);
  break;
  case 'T': 
  //set the temperature treshold in this layer
  //no need to send down
  break;

  case 'H':
  //set the humidity treshold in this layer
  //no need to send down 
  break;

  case 'L':
  //set the light treshold in this layer
  //no need to send down
  break;

  }*/

  //if the meesgae came from bottom layer
  //the layer should act/send up the hirarchy if needed
  switch(msg.sensorType) {
    
    //soil humidity data
    case 'S':

    //do nothing, just send to high level for image status
    //change msg src and dest
    //sendMessage(msg)
    break;
    
    //temparture data
    case 'T':
    Serial.println("sensorType");
    Serial.println(msg.sensorType);
    Serial.println("Destination");
    Serial.println(msg.dest);
        Serial.println("Data temperature");
    Serial.println(msg.data[0], DEC);
    Serial.println("Data humidity");
    Serial.println(msg.data[2], DEC);
    


    //do avreage from all temperatre messages that received
    //if (average < TEMP_LOWER_TRESHOLD) {
      //turn on heat lamp
    //}
    //else if (average > TEMP_HIGHER_TRESHOLD) {
      //turn on fan in
    //}
    //else {
      //do nothing, just check that the actuators are off
    //}
    //send average to upper layer
    break;
    
    //air humidity data
    case 'H':
    //do avreage from all humidity messages that received
    //if (average < HUMIDITY_LOWER_TRESHOLD) {
      //check how to add humidity to greenhouse
    //}
    //else if (average > HUMIDITY_HIGHER_TRESHOLD) {
      //turn on fan out
    //}
    //else {
      //do nothing, just check that the actuators are off
    //}
    //send average to upper layer
    break;
    
    //light data
    case 'L':
    //do avreage from all light messages that received
    //if (average < LIGHT_LOWER_TRESHOLD && needLight) {
      //turn on lamp
    //}
    //else if (average > LIGHT_HIGHER_TRESHOLD && !needLight) {
      //turn off lump
    //}
    //else {
      //do nothing, just check that the actuators are off
    //}
    //send average to upper layer  
    break;
    
    //water consumption data
    case 'W':
    //TODO sum the amount of water and send up
    //sendMessageToUpperLayer()
    break;
    
    //TODO electricty consumption   

    default:
    //TODO error
    break;
  }
  
}

void loop() {
  //receive message from lower layer
  Message messageToRead = recieveMessage();

  //if we got data
  if ('z' != messageToRead.sensorType) {
    decodeMessage(messageToRead);
  }
  delay(3000);

}
