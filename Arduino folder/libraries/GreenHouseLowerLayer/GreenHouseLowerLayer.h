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
		 void prepareMessage(Message&, int);

		 void initDataArrays();
		 float doAverage(LinkedList<float>&);
		 void prepareDataMessage(Message&, float, char);
		 void sendMessage(Message&);
		 void receiveMessage(Message&);
	private:
		int address;
		unsigned long currentMillis;
		unsigned long previousMillis;
		
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
