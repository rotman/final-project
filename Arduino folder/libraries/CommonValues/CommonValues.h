#ifndef COMMON_VALUES
#define COMMON_VALUES
#include <Arduino.h>
class CommonValues {
	public:
		//addresses
		static const int lowerLayerMinAddress		 = 1;
		static const int lowerLayerMaxAddress		 = 99;
		static const int middleLayerMinAddress		 = 100;
		static const int middleLayerMaxAddress		 = 199;
		static const int highLayerMinAddress		 = 200;
		static const int highLayerMaxAddress		 = 299;
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
		//static const int soilPin = A0;
		//tatic const int lightPin = A2;
		static const int pumpPin = 5;
		static const int fan1Pin = 3;
		static const int fan2Pin = 4;
		static const int steamPin = 6;
		static const int heatPin = 9;
		static const int currentConsumptionPin = 9;
		static const int waterConsumptionPin = 9;
		static const int higherLayerRadioPin1 = 2;
		static const int higherLayerRadioPin2 = 15;


		//Conventions
		static const char emptyMessage = 'z';
		static const char policyChange = 'p';
		static const char loopTimeChange = 'a';
		static const char myAddressChange = 'b';
		static const char yourAddressChange = 'y';
		static const char arduinoMalfunction = 'e';
		static const char dataType = 'd';
		static const char emergencyType = 'e';
		static const char temperatureType = 'T';
		static const char humidityType = 'H';
		static const char soilHumidityType = 'S';
		static const char lightType = 'L';
		static const char currentType = 'C';
		static const char waterType = 'W';


		static const int producersSize = 3;
		static const int lowerLayerRegisteredNum = 2;
		static const int EMERGENCY_TEMPERATURE = 40;

		static const unsigned long day	 = 86400000;  //24 hour
		static const unsigned long minute= 60000;

		//thresholds - not consts!
		static float soilHumidityThresholdMin;
		static float soilHumidityThresholdMax;

		static float airHumidityThresholdMin;
		static float airHumidityThresholdMax;

		static float temperatureThresholdMin;
		static float temperatureThresholdMax;

		static float lightThresholdMin;
		static float lightThresholdMax;

		static long whenTosendConsumption;
		static int minutesInInterval;

		static const char* ssid;
		static const char* password;
		static const char* host;
		static const char* key;
		static const unsigned long lastTimeSentToServer = 0;
		static const long sendToServerInterval = 5000;
		static const unsigned long lastTimeCheckedForNewSettings = 0;
		static const long checkedForNewSettingsInterval = 10000;
		static const int amountOfGreenHouses = 1;
		static const int MiddleLayerLostConnectionTime = 50000;

};

#endif
