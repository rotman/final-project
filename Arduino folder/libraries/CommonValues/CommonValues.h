#ifndef COMMONVALUES
#define COMMONVALUES

class CommonValues {
	public:
		//addresses
		static const int lowerLayerAddress 			 = 1;
		static const int lowerLayerConsumptionAdress = 2;
		static const int middleLayerAddress 		 = 101;
		static const int highLayerAddress 			 = 201;

		//sensors id
		static const int humidityTemperatureSensorId = 1;
		static const int lightSensorId 			  	 = 2;
		static const int soil1SensorId 				 = 3;
		static const int soil2SensorId 				 = 4;
		static const int currentSensorId			 = 5;
		static const int waterFlowSensorId			 = 6;

		//actuators id
		static const int fan1ActuatorId 	= 1;
		static const int fan2ActuatorId 	= 2;
		static const int fan3ActuatorId 	= 3;
		static const int lampActuatorId 	= 4;
		static const int pamp1ActuatorId 	= 6;
		static const int pamp2ActuatorId 	= 7;
		static const int humidityActuatorId = 8;
		
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