#include <Layer.h>

Layer::Layer() {
	watchDog.enable(CommonValues::watchDogSecondsUntilReset);
}

void Layer::addCommunication(ICommunicationable* type) {
	communicationList.add(type);
}

void Layer::removeCommunication(int index) {
	for (int i = 0; i < communicationList.size(); i++) {
		if (i == index) {
			communicationList.remove(i);
			break;
		}
	}
}

LinkedList<ICommunicationable*>& Layer::getCommunicationList() {
	return communicationList;
}

int Layer::getLoopTime() {
	return this->loopTime;
}

WatchDog& Layer::getWatchDog() {
	return this->watchDog;
}

void Layer::setLoopTime(int time) {
	this->loopTime = time;
}

void Layer::sendUnsentImportantMessages() {
	Serial.print(F("unsentImportantMessages.size() &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"));
	Serial.println(unsentImportantMessages.size());
	for (int i = 0; i<unsentImportantMessages.size(); i++) {
		Serial.print(F("unsentImportantMessages.get(i) "));
		/*Serial.println(unsentImportantMessages.get(i).dest);
		Serial.println(unsentImportantMessages.get(i).source);
		Serial.println(unsentImportantMessages.get(i).messageType);
		Serial.println(unsentImportantMessages.get(i).data);*/
		/*Serial.print(F("resending message to--------------- "));
		Serial.println(unsentImportantMessages.get(i).dest);*/
		boolean isSent = communicationList.get(CommonValues::radioIndex)->sendMessage(unsentImportantMessages.get(i));
		Serial.print(F("isSent ???????????????????????????????????     "));
		Serial.println(isSent);
		if (isSent) {
			Serial.print(F("removing message **************************"));
			Serial.println(i);
			unsentImportantMessages.remove(i);
		}
	}
}