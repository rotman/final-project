#include <Radio.h>


void Radio::init(RF24 &radio1, int readingAddress, int writingAddress) {
	radio = new RF24(3, 4);
	radio.begin();
    radio.setRetries(15, 15); // default
    radio.openWritingPipe(writingAddress);
    radio.openReadingPipe(1,readingAddress);
	radio.startListening();
}

void Radio::sendMessage(RF24 &radio, Message &message) {
	radio.openWritingPipe(message.dest); // open pipe for current destination
    bool ok = false;
    int iteration = 0;
    int delayMili = 0;
    ExponentialBackoff exponentialBackoff(5);
    radio.stopListening();
    while(!ok && delayMili != -1){  //if message fails 
		ok =  radio.write(&message, sizeof(message));
        if(ok)
			Serial.println("send success");      
        else {
			Serial.println("send failed backing off");
            delayMili = exponentialBackoff.getDelayTime(++iteration);
            if(delayMili >= 0)
              delay(delayMili);
            else break;   
            //send failed (max retries)  TODO  
        }
    }
    radio.startListening();
}

Message Radio::receiveMessage(RF24 &radio) {
	Message message;
	
	if (radio.available()){
		radio.read(&message, sizeof(message));
		Serial.print("recived message: the data is:");
		Serial.println(message.data);
	}
	else {
		Serial.println("nothing to read");
		message.sensorType = 'z';
	}
		return message;
}
