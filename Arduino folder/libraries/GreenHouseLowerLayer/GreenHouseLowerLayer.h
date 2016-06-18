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
		 void decodeMessage(Message&);
		 Message& prepareMessage(Message&, int);

		 void initDataArrays();
		 float doAverage(LinkedList<float>);
		 Message& prepareDataMessage(float, char);
		 void sendMessage(Message&);
		 Message& receiveMessage();
	private:
		int address;
		unsigned long currentMillis;
		unsigned long previousMillis;
		Radio radio;
		
		//lower layer data
		LinkedList<float> temperatureData;
		LinkedList<float> soilHumidityData;
		LinkedList<float> airHumidityData;
		LinkedList<float> lightData;

		//lower layer consumption data
		float currentConsumptionData;
		float waterConsumptionData;

};

#endif
