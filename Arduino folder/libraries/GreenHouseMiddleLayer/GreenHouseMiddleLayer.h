#ifndef GREEN_HOUSE_MIDDLE_LAYER
#define GREEN_HOUSE_MIDDLE_LAYER

#include <MiddleLayer.h>
#include <Sensor.h>
#include <Radio.h>
#include <CommonValues.h>
#include <Clock.h>


class GreenHouseMiddleLayer :  public MiddleLayer<Message> {

	public:

		void initDataArrays();
		float doAverage(LinkedList<Message>&);
		bool isTimeConsistency(LinkedList<Message>&, int);
		bool updateDataAndCheckIfFull(LinkedList<Message>&, Message&,int);
		void actuate(int,bool);

		//MiddleLayer implementation
		void initLayer(int);
		void analyze();
		void decodeMessage(Message&);
		void prepareMessage(Message&, int);
		bool sendMessage(Message&);
		void receiveMessage(Message&);
		unsigned long convertDateTimeToMillis(DateTime);
		
	private:

		int sendDataTime;
		int sensorTypeNotRespondingTime;
		Clock clock;
		int address;
		int plantsLowerLayers; // the consumption is a lower layer, but in the green house we treat him different.
		LinkedList<Message> temperatureData;
		LinkedList<Message> humidityData;
		LinkedList<Message> lightData;
		LinkedList<Message> currentData;
		LinkedList<Message> waterData;

		//variable to know if specific sensor is ready to analyze
		bool isTemperatureReadyToAnalyze = false;
		bool isHumidityReadyToAnalyze = false;
		bool isLightReadyToAnalyze = false;

};

#endif
