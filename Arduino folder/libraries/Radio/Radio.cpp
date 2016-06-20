#include <Radio.h>


void Radio::initCommunication(int readingAddress, int writingAddress) {
	radio->begin();
    radio->setRetries(15, 15); // default
    radio->openWritingPipe(writingAddress);
    radio->openReadingPipe(1,readingAddress);
	radio->startListening();
}

bool Radio::sendMessage(Message message) {
	radio->openWritingPipe(message.dest);				// open pipe for current destination
    bool ok = false;
    int iteration = 0;									//
    int delayMili = 0;									//this will be the time waiting for re sending a messege that failed.
    ExponentialBackoff exponentialBackoff(5);
    radio->stopListening();							     //if you listen , you cant talk...
    while(!ok && delayMili != -1){						
		ok =  radio->write(&message, sizeof(message));
        if(ok)
			Serial.println("send success");

        else {											 //if message fails
			Serial.println("send failed backing off");
            delayMili = exponentialBackoff.getDelayTime(++iteration);
            if(delayMili >= 0)
              delay(delayMili);
			else {
				Serial.println("send failed (max retries)");
				break;
					//send failed (max retries)  TODO
			}
        }
    }
    radio->startListening();
	return ok;
}

void Radio::receiveMessage(Message& message) {
	//Message* message = new Message();
	if (radio->available()){
		radio->read(&message, sizeof(message));
		Serial.print("recived message: the data is:");
		Serial.println(message.sensorType);
		Serial.println(message.data);
	//	Serial.println(message.additionalData);
	//	Serial.println(message.dest);
	}
	else {
		Serial.println("nothing to read");
		message.sensorType = CommonValues::emptyMessage;
	}
	
}
