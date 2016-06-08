#ifndef COMMONVALUES
#define COMMONVALUES
#include <Arduino.h>
class CommonValues {
	public:
		//addresses
		static const int lowerLayerAddress1			 = 1;
		static const int lowerLayerAddress2			 = 2;

		static const int lowerLayerConsumptionAdress = 3;
		static const int middleLayerAddress 		 = 101;
		static const int highLayerAddress 			 = 201;

		//sensors id
		static const int humidityTemperatureSensorId = 1;
		static const int lightSensorId 			  	 = 2;
		static const int soil1SensorId 				 = 3;
		static const int soil2SensorId 				 = 4;
		static const int currentSensorId			 = 5;
		static const int waterFlowSensorId			 = 6;


		//pins
		static const int radioPin1 = 7;
		static const int radioPin2 = 8;
		static const int tempHumidityPin = 2;
		static const int soilPin = A0;
		static const int lightPin = A2;
		static const int pumpPin = 5;
		static const int fan1Pin = 3;
		static const int fan2Pin = 4;
		static const int steamPin = 6;
		static const int heatPin = 9;



		
		//thresholds - not consts!
		static int soilHumidityThresholdMin;
		static int soilHumidityThresholdMax;
		
		static int airHumidityThresholdMin;
		static int airHumidityThresholdMax;
		
		static int temperatureThresholdMin;
		static int temperatureThresholdMax;
		
		static int lightThresholdMin;
		static int lightThresholdMax;
		
};

#endif