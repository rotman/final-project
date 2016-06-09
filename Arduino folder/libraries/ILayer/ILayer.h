#ifndef ILAYER
#define ILAYER

#include <Arduino.h>
#include <ICommunicationable.h>
template <class E, class S>
//in green house project,'S' stands for Message, 'E' stands for communication type

class ILayer : public ICommunicationable<E,S> {
	public:
		virtual ~ILayer() {}
		virtual void initLayer(int) = 0;
		virtual void analyze() = 0;
		virtual void decodeMessage() = 0;
		virtual S prepareMessage(S, int) = 0;

		/*ICommunicationable methods*/

		virtual void initCommunication(E&, int, int) = 0;
		virtual void sendMessage(E&, S&) = 0;
		virtual S receiveMessage(E&) = 0;
};

#endif