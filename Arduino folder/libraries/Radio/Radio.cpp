#include <Radio.h>


void Radio::init(RF24 &radio, byte rxAddr[6], byte wxAddr[6]) {
	radio.begin();
    radio.setRetries(15, 15);
    radio.openWritingPipe(wxAddr);
    radio.openReadingPipe(1,rxAddr);
}

void Radio::sendMessage(RF24 &radio, Message &message) {
	  bool ok = false;
	  radio.stopListening();
	  while (!ok) {
		ok = radio.write(&message, sizeof(message));
		if (ok) {
			Serial.println("send success");      
		}
		else {
			Serial.println("send failed");
		}  
	  }
	radio.startListening();
 
}

Message Radio::receiveMessage(RF24 &radio) {
	radio.startListening();
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
	
	radio.stopListening();
	return message;
}