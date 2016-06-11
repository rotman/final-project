#ifndef GREEN_HOUSE_LOWER_LAYER
#define GREEN_HOUSE_LOWER_LAYER
#include <HighLayer.h>
#include <Message.h>
#include <ArduinoJson.h>

template <class T,class E,class S>

class GreenHouseHighLayer : public HighLayer<T,E,S> {

	public:

		/*Layer methods*/
		virtual ~GreenHouseHighLayer() {}
		virtual void initLayer(int);
		virtual void analyze();
		virtual void decodeMessage(Message);
		virtual Message prepareMessage(Message, int);


};

#endif
