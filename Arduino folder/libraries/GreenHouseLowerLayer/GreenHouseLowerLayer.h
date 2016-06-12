#ifndef GREEN_HOUSE_LOWER_LAYER
#define GREEN_HOUSE_LOWER_LAYER

#include <LowerLayer.h>
#include <Radio.h>
#include <CommonValues.h>
#include <Message.h>

class GreenHouseLowerLayer : public LowerLayer<Message>{

	public:
		/*LowerLayer methods*/
		~GreenHouseLowerLayer(){}
		 void initLayer(int);
		 void analyze();
		 void decodeMessage(Message);
		 Message prepareMessage(Message, int);

	private:
		int address;
};

#endif
