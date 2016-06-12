#ifndef GREEN_HOUSE_HIGH_LAYER
#define GREEN_HOUSE_HIGH_LAYER

#include <Arduino.h>
#include <HighLayer.h>
#include <Message.h>
#include <ArduinoJson.h>
#include <LinkedList.h>
#include <GreenHouseHighLayerData.h>
#include <GreenHouseHighLayerThresholds.h>
#include <CommonValues.h>
#include <ICommunicationable.h>
#include <Wifi.h>

template <class T>
class GreenHouseHighLayer : public HighLayer<T> {

private:
		GreenHouseHighLayerData greenHouseData[CommonValues::amountOfGreenHouses];
		GreenHouseHighLayerThresholds greenHouseThresholds[CommonValues::amountOfGreenHouses];

public:
		/*Layer methods*/
		~GreenHouseHighLayer() {}
		void initLayer(int);
		void analyze();
		void decodeMessage(Message&);
		Message prepareMessage(Message, int);
		void debug() {

		}

};

template <class T>
void GreenHouseHighLayer<T>::initLayer(int address) {
	int i;

	//initialize greenhouse data
	for (i = 0 ; i < CommonValues::amountOfGreenHouses ; i++ ) {
			greenHouseData[i].setId(101 + i) ;
			greenHouseThresholds[i].setId(101 + i);
	}

	//initialize communication
	Wifi wifi;
	Radio radio;
	ICommunicationable* wifiPtr = &wifi;
	this->addCommunication(wifiPtr);
	ICommunicationable* radioPtr = &radio;
	this->addCommunication(wifiPtr);

}

template<class T>
void GreenHouseHighLayer<T>::analyze() {}

template <class T>
void GreenHouseHighLayer<T>::decodeMessage(Message & message) {

}

template <class T>
Message GreenHouseHighLayer<T>::prepareMessage(Message message , int address) {
	return message;
}

#endif
