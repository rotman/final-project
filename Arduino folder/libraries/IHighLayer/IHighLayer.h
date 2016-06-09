#ifndef IHIGHLAYER
#define IHIGHLAYER
#include <ILayer.h>

template <class E, class S,class T>
//in green house project,'S' stands for Message, 'E' stands for Radio ,'T' stands for Wifi


class IHighLayer :public ILayer {
	public:

		/*ILayer methods*/
		virtual ~ILayer() {}
		virtual void initLayer(int) = 0;
		virtual void analyze() = 0;
		virtual void decodeMessage() = 0;
		virtual S prepareMessage(S, int) = 0;
		virtual void initCommunication(E&, int, int) = 0;
		virtual void sendMessage(E&, S&) = 0;
		virtual S receiveMessage(E&) = 0;
	
	
};