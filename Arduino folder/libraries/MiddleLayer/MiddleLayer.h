#ifndef MIDDLE_LAYER
#define MIDDLE_LAYER

#include <Layer.h>
#include <Actuatorable.h>

template <class T>

class MiddleLayer :public Layer<T>, public Actuatorable {
	public:

		/*Layer methods*/
		virtual ~MiddleLayer() {}
		virtual void initLayer(int) = 0;
		virtual void analyze() = 0;
		virtual void decodeMessage(T) = 0;
		virtual T prepareMessage(T, int) = 0;

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
