#include <Radio.h>

int Radio::sendCounter = 0;
int Radio::receiveCounter = 0;

Radio::Radio(int connactionPin1, int connactionPin2){
	radio = new RF24(connactionPin1,connactionPin2);
}
void Radio::initCommunication(int readingAddress, int writingAddress) {
	radio->begin();
    radio->setRetries(15, 15); // default
    radio->openWritingPipe(writingAddress);
    radio->openReadingPipe(1,readingAddress);
	radio->startListening();
}

bool Radio::sendMessage(Message message) {
	sendCounter++;
	radio->openWritingPipe(message.dest);				// open pipe for current destination
    bool ok = false;
	int sendMaxRetries = CommonValues::sendMaxRetries;
	radio->stopListening();							     //if you listen , you cant talk...
	for (int i = 0; i < sendMaxRetries; ++i) {
		ok = radio->write(&message, sizeof(message));
		if (ok) {
			Serial.print(F("send success i sent id data and type:"));
			Serial.println(message.source);
			Serial.println(message.data);
			Serial.println(message.sensorType);
			radio->startListening();
			sendCounter++;
			return true;
		}
		else 									 //if message fails
			Serial.println(F("send failed trying again"));
	}
	//send message failed, lets try exponential backoff.
	int iteration = 0;									//
	int delayMili = 0;									//this will be the time waiting for re sending a messege that failed.
	ExponentialBackoff exponentialBackoff(CommonValues::exponentialBackoffMaxRetries);
	while(!ok && delayMili != -1){						
		ok =  radio->write(&message, sizeof(message));
		if (ok) {
			Serial.print(F("send success i sent id data and type:"));
			Serial.println(message.source);
			Serial.println(message.data);
			Serial.println(message.sensorType);
			sendCounter++;
			break;
		}
        else{											 //if message fails
			Serial.println(F("send failed backing off"));
            delayMili = exponentialBackoff.getDelayTime(++iteration);
            if(delayMili >= 0)
              delay(delayMili);
			else {
				Serial.println(F("send failed (max retries)"));
				break;
					//send failed (max retries)  TODO
			}
        }
    }
    radio->startListening();
	return ok;
}

void Radio::receiveMessage(Message& message) {
	if (radio->available()){
		receiveCounter++;
		radio->read(&message, sizeof(message));
		Serial.print(F("recived message: from and type and data is:"));
		Serial.println(message.source);
		Serial.println(message.sensorType);
		Serial.println(message.data);
		if (isnan(message.data)) {
			message.messageType = CommonValues::emptyMessage;
			Serial.println(F("message is nan"));
		}	
	}
	else{
		Serial.println(F("nothing to read"));
		message.messageType = CommonValues::emptyMessage;
	}
	
}
