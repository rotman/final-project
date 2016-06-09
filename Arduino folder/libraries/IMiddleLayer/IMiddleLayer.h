#ifndef IMIDDLELAYER
#define IMIDDLELAYER

#include <ILayer.h>
#include <Actuatorable.h>

template <class S>

class IMiddleLayer :public ILayer<E, S>, public Actuatorable {
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

		/*Actuatorable methods*/

		virtual void addActuator(Actuator*) = 0;
		virtual void removeActuator(int) = 0;
		virtual void actuate(int, bool) = 0;
	//	virtual void initLayer(int) = 0;
	//	virtual void addActuator(Actuator*) = 0;
	//	virtual void removeActuator(int) = 0;
	//	virtual void actuate(S*, bool) = 0;	
	//	virtual void analyze() = 0;
};

#endif