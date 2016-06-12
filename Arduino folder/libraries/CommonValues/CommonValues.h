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
		static const int soilPin1 = A0;
		static const int lightPin = A2;
		static const int pumpPin = 5;
		static const int fan1Pin = 3;
		static const int fan2Pin = 4;
		static const int steamPin = 6;
		static const int heatPin = 9;

		//Conventions
		static const char emptyMessage = 'z';
		static const char policyChange = 'p';
		static const char dataType = 'd';		
		static const char temperateType = 'T';
		static const char humidityType = 'H';
		static const char soilHumidityType = 'S';
		static const char lightType = 'L';
		
		static const int producersSize = 3;
		static const int EMERGENCY_TEMPERATURE = 40;


		
		//thresholds - not consts!
		static byte soilHumidityThresholdMin;
		static byte soilHumidityThresholdMax;
		
		static byte airHumidityThresholdMin;
		static byte airHumidityThresholdMax;
		
		static byte temperatureThresholdMin;
		static byte temperatureThresholdMax;
		
		static byte lightThresholdMin;
		static byte lightThresholdMax;
		
};

#endif