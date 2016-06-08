#include <MiddleLayer.h>
#include <CommonValues.h>
#include <GreenHouseActuator.h>
#include <Actions.h>

#define PRODUCERS_SIZE 3

//globals
//-------
MiddleLayer middleLayer;
RF24 radio(CommonValues::radioPin1 , CommonValues::radioPin2);

//actuators
Actuator * fan1Actuator;
Actuator * fan2Actuator;
Actuator * lightActuator;
Actuator * heatActuator;
Actuator * steamActuator;
Actuator * steamerActuator;

//pins
int fan1Pin = CommonValues::fan1Pin;
int fan2Pin = CommonValues::fan2Pin;
int lightPin = CommonValues::lightPin;
int heatPin = CommonValues::heatPin;
int steamPin = CommonValues::steamPin;


void initConsole() {
  while (!Serial);
  Serial.begin(9600);
}

void createAndAddActuators() {
  Serial.println("createAndAddActuators()");
 
  fan1Actuator = new GreenHouseActuator(CommonValues::fan1Pin);
  fan2Actuator = new GreenHouseActuator(CommonValues::fan2Pin);
  lightActuator = new GreenHouseActuator(CommonValues::lightPin);
  heatActuator = new GreenHouseActuator(CommonValues::heatPin);
  steamActuator = new GreenHouseActuator(CommonValues::steamPin);

  middleLayer.addActuator(fan1Actuator);
  middleLayer.addActuator(fan2Actuator);
  middleLayer.addActuator(lightActuator);
  middleLayer.addActuator(heatActuator);
  middleLayer.addActuator(steamActuator);

}



void setup() {
  Serial.println("setup()");
  initConsole();
  middleLayer.initLayer(CommonValues::middleLayerAddress);
  middleLayer.initCommunication(radio, CommonValues::middleLayerAddress, CommonValues::highLayerAddress);
  createAndAddActuators();
}

//boolean updateValue(Message msg) {
//
//  boolean exist = false;
//
//    if (msg.source == producers[i].source) {
//      producers[i].data = msg.data;
//      producers[i].dateTime = msg.dateTime;
//      exist = true;
//    }
//  }
//
//  return exist;
//}

Actions actuateIfNeeded(float data, char type) {
  Serial.println("actuateIfNeeded()");
  switch(type) {
    case 'T':
      if (data > CommonValues::temperatureThresholdMax) {
    //    middleLayer.actuate(fan1, true); TODO
        return FAN1;
      }
      else {
      //  middleLayer.actuate(fan1, false); TODO
        return NONE;
      }

      if (data < CommonValues::temperatureThresholdMin) {
      //  actuateLight(true); TODO
        return LIGHT;
      }

      else {
       // middleLayer.actuate(fan1, false); TODO
        return NONE;
      }
      break;

    case 'L':
    //TDOO
    break;
    
  }
}

void decodeMessage(Message msg) {
  Serial.println("decodeMessage()");
  if (msg.dest != CommonValues::middleLayerAddress) {
    Serial.println("not for me, ignore message");
    //TODO maybe think re-sending the message to its origin , ot dest.    
    return;
  }
  
  if(msg.source >= 200 && msg.source < 300){   //from higer layer
      //if the meesgae came from high layer
      //we should change policy in this layer/bottom layer

      //TODO type of message handeling!!!!!!!!!!!!!!!!!!!!!!!
      
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
      prepareMessage(msg, CommonValues::highLayerAddress);
      middleLayer.sendMessage(radio, msg);
      break;
      
      /******************temparture data*********************/
      case 'T':
      {
//        boolean isUpdated = updateValue(msg);
//        if (!isUpdated) {
//          Serial.println("value failed to update, the source isn't registered");
//          return;
//        }
        
//        float tempratureAverage = checkForAverage();
        
//        if (tempratureAverage < 0) {
//          return;
  //      }
        
    //    else {
      //    boolean isActuatorEnabled = actuateIfNeeded(tempratureAverage, msg.sensorType);
        //  if (isActuatorEnabled) {
          //  Serial.println("fan turned on");
            //TODO send message to upper

        //  }
        }

      break;
      
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
      
      Serial.println("Data ");
      Serial.println(msg.data);
      
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

Message prepareMessage(Message message, int address){
  Serial.println("prepareMessage()");
  message.source = CommonValues::middleLayerAddress;
  message.dest = address;
  return message;
}

void loop() {
  Serial.println("loop()");
//  //receive message from lower layer
//  Message messageToRead = recieveMessage();
//
//  //if we got data
//  if ('z' != messageToRead.sensorType) {
//    decodeMessage(messageToRead);
//  }
//  delay(3000);
//  rtClock.watchConsole();
//  rtClock.get3231Date();
//  Serial.print(rtClock.weekDay);
//  Serial.print(", ");
//  Serial.print(rtClock.date, DEC);
//  Serial.print("/");
//  Serial.print(rtClock.month, DEC);
//  Serial.print("/");
//  Serial.print(rtClock.year, DEC);
//  Serial.print(" - ");
//  Serial.print(rtClock.hours, DEC);
//  Serial.print(":");
//  Serial.print(rtClock.minutes, DEC);
//  Serial.print(":");
//  Serial.print(rtClock.seconds, DEC);
//  Serial.print(" - Temp: ");
//  Serial.println(rtClock.get3231Temp());
//  Serial.print("sizeeeeeeeeeeeeee of massage = " );
//  Serial.println(sizeof(Message));
Message msg;
msg.sensorType = 'T';
msg.data = 34.34;
middleLayer.sendMessage(radio, msg);

delay(1000);

}
