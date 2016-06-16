#ifndef GREEN_HOUSE_MIDDLE_LAYER
#define GREEN_HOUSE_MIDDLE_LAYER

#include <MiddleLayer.h>
#include <Sensor.h>
#include <Radio.h>
#include <CommonValues.h>
#include <Clock.h>


class GreenHouseMiddleLayer :  public MiddleLayer<Message> {

	public:
		//IMiddleLayer implementation
		void initLayer(int);
		void analyze();//TODO
		void decodeMessage(Message&);
		Message& prepareMessage(Message&, int);
		
		void actuate(int);
		void initDataArrays();
		float doAverage(LinkedList<Message>&);
		bool isTimeConsistency(LinkedList<Message>&, int);
		bool isArrayFullAndUnique(LinkedList<Message>&);
		
	private:
		
		int loopTime;
		int sendDataTime;
		int sensorTypeNotRespondingTime;
		Clock clock;
		int address;
		
		LinkedList<Message> temperatureData;
		LinkedList<Message> humidityData;
		LinkedList<Message> lightData;
		LinkedList<Message> currentData;
		LinkedList<Message> waterData;
		
		bool isTemperatureReadyToAnalyze = false;
		bool isHumidityReadyToAnalyze = false;
		bool isLightReadyToAnalyze = false;

};

#endif
