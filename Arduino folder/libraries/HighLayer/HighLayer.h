#ifndef HIGH_LAYER
#define HIGH_LAYER
#include <Layer.h>
#include <ICommunicationable.h>

template <class T,class E, class S>
//in green house project,'T' stands for Message

class HighLayer :public Layer<T,E,S> {
	public:

		/*Layer methods*/
		virtual ~HighLayer() {}
		virtual void initLayer(int) = 0;
		virtual void analyze() = 0;
		virtual void decodeMessage(T) = 0;
		virtual T prepareMessage(T, int) = 0;

		virtual void addCommunication(ICommunicationable<E,S>*) = 0;
		virtual void removeCommunication(int) = 0;

};

#endif
