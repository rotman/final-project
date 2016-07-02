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
		Layer();
		virtual void initLayer(int) = 0;
		virtual void analyze() = 0;
		virtual void decodeMessage(T&) = 0;
		virtual void prepareMessage(T&, int) = 0;
		void addCommunication(ICommunicationable*);
		void removeCommunication(int);	
		LinkedList<ICommunicationable*>& getCommunicationList();
		int getLoopTime();
		WatchDog& getWatchDog();
		void setLoopTime(int);
		void sendUnsentImportantMessages();
	protected:
		int loopTime;
		LinkedList<ICommunicationable*> communicationList;
		LinkedList<T> unsentImportantMessages;
		WatchDog watchDog;
};

#endif
