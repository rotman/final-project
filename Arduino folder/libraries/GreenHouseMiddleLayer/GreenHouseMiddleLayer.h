#ifndef GREEN_HOUSE_MIDDLE_LAYER
#define GREEN_HOUSE_MIDDLE_LAYER

#include <MiddleLayer.h>
#include <Radio.h>
#include <Sensor.h>
#include <Clock.h>


class GreenHouseMiddleLayer :  public MiddleLayer<Message,Message,int> {

	public:

		//IMiddleLayer implementation
		void initLayer(int);
		void addActuator(Actuator*);
		void removeActuator(int);
		void actuate(Actuator*, bool);
		void analyze() {};//TODO
		void decodeMessage(Message);
		Message prepareMessage(Message, int);
		void getTime();

	private:
		int address;
		Radio radioHelper;
		LinkedList<Actuator*> actuators;
		Clock clock;

};

#endif
