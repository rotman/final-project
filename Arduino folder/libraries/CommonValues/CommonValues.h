#ifndef COMMONVALUES
#define COMMONVALUES

class CommonValues {
	public:
		//sensors id
		static const int humidityTemperatureSensorId = 1;
		static const int lightSensorId 			  	 = 2;
		static const int soilSensorId 				 = 3;
		static const int currentSensorId			 = 4;
		static const int waterFlowSensorId			 = 5;

		
		//actuators id
		static int const fan1ActuatorId 	= 1;
		static const int fan2ActuatorId 	= 2;
		static const int fan3ActuatorId 	= 3;
		static const int lampActuatorId 	= 4;
		static const int pamp1ActuatorId 	= 6;
		static const int pamp2ActuatorId 	= 7;
		static const int humidityActuatorId = 8;
		
};

#endif