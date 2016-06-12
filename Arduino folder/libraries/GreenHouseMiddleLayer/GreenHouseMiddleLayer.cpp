#include <GreenHouseMiddleLayer.h>



void GreenHouseMiddleLayer::initLayer(int address) {
	this->address = address;
	actuators = LinkedList<Actuator*>();
	//more inits here
}

void GreenHouseMiddleLayer::addActuator(Actuator* actuator) {
	actuators.add(actuator);
}

void GreenHouseMiddleLayer::actuate(Actuator* actuator, bool on) {
	actuator->actuate(on);
}

void GreenHouseMiddleLayer::removeActuator(int pin) {
	for (int i = 0; i < actuators.size(); i++) {
		if (actuators.get(i)->getPin() == pin) {
			actuators.remove(i);
			break;
		}
	}
}

void GreenHouseMiddleLayer::actuate(Actuator* actuator, bool on) {
	actuator->actuate(on);
}

Message GreenHouseMiddleLayer::prepareMessage(Message message, int address) {
	Serial.println("prepareMessage()");
	message.source = CommonValues::middleLayerAddress;
	message.dest = address;
	return message;
}

void GreenHouseMiddleLayer::analyze() {
}
void GreenHouseMiddleLayer::decodeMessage(Message msg) {
	Serial.println("decodeMessage()");
	if (msg.dest != CommonValues::middleLayerAddress) {
		Serial.println("not for me, be a good friend and pass it on");
		radioHelper.sendMessage(msg);
		return;
	}

	else if (msg.source >= 200 && msg.source < 300) {   //from higer layer
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
		if (msg.source >= 1 && msg.source < 100) {

			Serial.println("sensorType");
			Serial.println(msg.sensorType);
			Serial.println("Destination");
			Serial.println(msg.dest);

			switch (msg.sensorType) {

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
}