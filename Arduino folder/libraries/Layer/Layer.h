#ifndef LAYER
#define LAYER

#include <Arduino.h>
#include <ICommunicationable.h>
#include <LinkedList.h>

template <class T,class E,class S>
//in green house project,'T' stands for Message

class Layer {
	public:
		virtual ~Layer() {}
		virtual void initLayer(int) = 0;
		virtual void analyze() = 0;
		virtual void decodeMessage() = 0;
		virtual T prepareMessage(T, int) = 0;
		virtual void addCommunication(ICommunicationable<E,S> *) = 0;
		virtual void removeCommunication(int) = 0;

protected:

	LinkedList<ICommunicationable<E,S> *> communicationArray;

};

#endif
