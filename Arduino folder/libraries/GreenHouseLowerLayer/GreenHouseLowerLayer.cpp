#include <GreenHouseLowerLayer.h>

void GreenHouseLowerLayer::initLayer(int address) {
	this->address = address;
	//more inits here , think maybe to move the inits to relevant constractors
}

void GreenHouseLowerLayer::analyze(){}

void GreenHouseLowerLayer::decodeMessage(Message message){
	if ('z' == messageToRead.sensorType) {
		//do nothing the message is empty
		return;
	}
}

//change this to add both src and dest (because lowerLayer has 3 addresses)
Message GreenHouseLowerLayer::prepareMessage(Message message, int address) {
	message.source = CommonValues::lowerLayerAddress1;
	message.dest = address;
	return message;
}




