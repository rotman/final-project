#include <MiddleLayer.h>
#include <CommonValues.h>
#include <FanActuator.h>
#include <Actions.h>

#define PRODUCERS_SIZE 3

//globals
//-------
MiddleLayer middleLayer;
RF24 radio(7, 8);
CommonValues commonValues;

//actuators
Actuator * fan1;
Actuator * fan2;
Actuator * fan3;
Actuator * lamp;
Actuator * heater;
Actuator * steamer;

//pins
int fan1Pin = 2;
int fan2Pin = 3;
int fan3Pin = 4;
int lightpin = 5;
int heatpin = 6;
int steampin = 7;

byte rxAddr[6] = "00002";
byte wxAddr[6] = "00001";

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

void createAndAddActuators() {
  Serial.println("createAndAddActuators()");

  fan1 = new FanActuator(commonValues.fan1ActuatorId, fan1Pin);
  Serial.println("FanActuator 1 created");

  fan2 = new FanActuator(commonValues.fan2ActuatorId, fan2Pin);
  Serial.println("FanActuator 2 created");

  fan3 = new FanActuator(commonValues.fan3ActuatorId, fan3Pin);
  Serial.println("FanActuator 3 created");
  
//  lamp = new LampActuator(commonValues.lampActuatorId, lightpin);
//  Serial.println("LampActuator created");
//
//  heater = new HeatActuator(commonValues.heatActuatorId, heatpin);
//  Serial.println("HeatActuator created");
//
//  steamer = new SteamActuator(commonValues.humidityActuatorId, steamtpin);
//  Serial.println("SteamActuator created");

  middleLayer.addActuator(fan1);
  middleLayer.addActuator(fan2);
  middleLayer.addActuator(fan3);
//  middleLayer.addActuator(lamp);
//  middleLayer.addActuator(heater);
//  middleLayer.addActuator(steamer);

}

void initPins() {
  pinMode(fan1Pin, OUTPUT);
  pinMode(fan2Pin, OUTPUT);
  pinMode(fan3Pin, OUTPUT);
  pinMode(lightpin, OUTPUT);
  pinMode(heatpin, OUTPUT);
  pinMode(steampin, OUTPUT);
}

void setup() {
  Serial.println("setup()");
  initConsole();
  middleLayer.initLayer(commonValues.middleLayerAddress);
  middleLayer.initCommunication(radio, rxAddr, wxAddr);
  createAndAddActuators();
  initPins();

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
  switch(type) {
    case 'T':
      if (data > commonValues.temperatureThresholdMax) {
        middleLayer.actuate(fan1, true);
        return FAN1;
      }
      else {
        middleLayer.actuate(fan1, false);
        return NONE;
      }

      if (data < commonValues.temperatureThresholdMin) {
        actuateLight(true);
        return LIGHT;
      }

      else {
        middleLayer.actuate(fan1, false);
        return NONE;
      }
      break;

    case 'L':
    //TDOO
    break;
    
  }
}

void decodeMessage(Message msg) {

  if (msg.dest != commonValues.middleLayerAddress) {
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
      prepareMessage(msg, commonValues.highLayerAddress);
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
  message.source = commonValues.middleLayerAddress;
  message.dest = address;
  return message;
}

void loop() {
//  
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
