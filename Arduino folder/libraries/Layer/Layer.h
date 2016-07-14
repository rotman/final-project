#ifndef LAYER
#define LAYER

#include <Arduino.h>
#include <ICommunicationable.h>
#include <LinkedList.h>
#include <WatchDog.h>
#include <CommonValues.h>

template <class T>
//in green house project,'T' stands for Message

class Layer {
	public:
		virtual ~Layer() {}
		Layer() {
			watchDog.enable(CommonValues::watchDogSecondsUntilReset);
		}
		virtual void initLayer(int) = 0;
		virtual void analyze() = 0;
		virtual void decodeMessage(T&) = 0;
		virtual void prepareMessage(T&, int) = 0;
		void addCommunication(ICommunicationable* type) {
			communicationList.add(type);
		}
		void removeCommunication(int index) {
			for (int i = 0; i < communicationList.size(); i++) {
				if (i == index) {
					communicationList.remove(i);
					break;
				}
			}
		}	
		LinkedList<ICommunicationable*>& getCommunicationList() {
			return communicationList;
		}
		int getLoopTime() {
			return this->loopTime;
		}
		WatchDog& getWatchDog() {
			return this->watchDog;	
		}
		void setLoopTime(int time) {
			this->loopTime = time;	
		}
		void sendUnsentImportantMessages() {
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
	protected:
		int loopTime;
		LinkedList<ICommunicationable*> communicationList;
		LinkedList<T> unsentImportantMessages;
		WatchDog watchDog;
};

#endif
