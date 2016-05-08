#include <nRF24L01.h>
#include <RF24.h>
#include <message.h>
#include <SPI.h>
#include <ExponentialBackoff.h>

#define LOWER_LAYER_ADDRESS_1 1
#define LOWER_LAYER_ADDRESS_2 2
#define LOWER_LAYER_ADDRESS_3 3

#define UPPER_LAYER_ADDRESS 201

#define MY_ADDRESS 101

#define PRODUCERS_SIZE 3

//boolean fanOn = false;
//boolean lightOn = false;
int fanPin = 2;
int lightpin = 4;
int temperatureUpThreshold = 25;    //TODO 
int temperatureDownThreshold = 21;

int temperatureThreshold = 20;    //TODO 

int producersAddress[] = {LOWER_LAYER_ADDRESS_1, LOWER_LAYER_ADDRESS_2, LOWER_LAYER_ADDRESS_3};
int producersValues[PRODUCERS_SIZE] = {-1, -1, -1};

//globals
//-------
RF24 radio(7, 8);

const byte rxAddr[6] = "00002";
const byte wxAddr[6] = "00001";


void actuateFan(boolean on){
  if(on)
      digitalWrite(fanPin,HIGH);
  else
      digitalWrite(fanPin,LOW);
}
void actuateLight(boolean on){
  if(on)
      digitalWrite(lightpin,HIGH);
  else
      digitalWrite(lightpin,LOW);
}

void initConsole() {
  while (!Serial);
  Serial.begin(9600);
}

void initRadio() {
    radio.begin();
    radio.setRetries(15, 15);
    radio.openWritingPipe(wxAddr);
    radio.openReadingPipe(3,rxAddr);
    radio.startListening();
}


void setup() {
  initConsole();
  initRadio();
  pinMode(fanPin, OUTPUT);

}


Message recieveMessage(){
  Message message;
  if (radio.available()){
    radio.read(&message, sizeof(message));
    Serial.print("recived message: the data is:");
     Serial.println(message.data[0]);
  }
  else{
    Serial.println("nothing to read");
    message.sensorType = 'z';
  }
  return message;

}


    void sendMessage(Message message){
        bool ok = false;
        int iteration = 0;
        int delayMili = 0;
        ExponentialBackoff exponentialBackoff;
        radio.stopListening();
        while(!ok && delayMili != -1){  //if message fails 
            ok =  radio.write(&message, sizeof(message));
            if(ok)
               Serial.println("send success");      
            else{
              Serial.println("send failed backing off");
              delayMili = exponentialBackoff.getDelayTime(++iteration);
              if(delayMili >= 0)
                delay(delayMili);
              else;   
              //send failed (max retries)  TODO  
            }
       }
        radio.startListening();
    
   
}

boolean updateValue(int source, int value) {

  boolean exist = false;

  for (int i = 0; i < PRODUCERS_SIZE ; i++) {
    if (source == producersAddress[i]) {
      producersValues[i] = value;
      exist = true;
    }
  }

  return exist;
}

void decodeMessage(Message msg) {

  if (msg.dest != MY_ADDRESS) {
    Serial.println("not for me, ignore message");
    return;
  }
  
  if(msg.source >= 200 && msg.source < 300){   //from higer layer
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
  }
  


  //if the meesgae came from bottom layer
  //the layer should act/send up the hirarchy if needed
  if(msg.source >= 1 && msg.source < 100){
    
    Serial.println("sensorType");
    Serial.println(msg.sensorType);
    Serial.println("Destination");
    Serial.println(msg.dest);
    
    switch(msg.sensorType) {
      
      /******************soil humidity data*******************/
      case 'S':
  
      //do nothing, just send to high level for image status
      //change msg src and dest
      //sendMessage(msg)
      break;
      
      /******************temparture data*********************/
      case 'T':
      {
      
        boolean isUpdated = updateValue(msg.source, msg.data[2]);
        if (!isUpdated) {
          //TODO 
          Serial.println("value failed to update, the source isn't registered");
          return;
        }
        Serial.println("Data [0]");
        if (msg.data[2] > temperatureUpThreshold)
          actuateFan(true);
        else    
          actuateFan(false);
        if (msg.data[2] < temperatureDownThreshold)
         actuateLight(true);
        else    
          actuateLight(false);
        if (msg.data[2] > temperatureThreshold)
          actuateFan(true);
       else    
          actuateFan(false);

      
      Serial.println(msg.data[0]);
      Serial.println("Data [2]");
      Serial.println(msg.data[2]);
/*
      msg = prepareMessageToLower(msg);
      msg.minimum_threshold = 35;
      msg.maximum_threshold = 55;
      sendMessage(msg);
*/    
  
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
      }
      

      
      /***********************air humidity data***********************/
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
      
      /***************************light data***********************/
      case 'L':
      
      Serial.println("Data [0]");
      Serial.println(msg.data[0]);
      
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
      
      /*********************water consumption data*****************/
      case 'W':
      //TODO sum the amount of water and send up
      //sendMessageToUpperLayer()
      break;
      
      /*********************electricity consumption data*****************/
      case 'C':
      //TODO sum the amount of electricity and send up
      //sendMessageToUpperLayer()
      break;
      
      default:
      //TODO error
      break;
    }
  }
  
}

Message prepareMessageToUpper(Message message){
  message.source = MY_ADDRESS;
  message.dest = UPPER_LAYER_ADDRESS;
  return message;
}


Message prepareMessageToLower(Message message){
  message.source = MY_ADDRESS;
  message.dest = LOWER_LAYER_ADDRESS_1;
  return message;
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
