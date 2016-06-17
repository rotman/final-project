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
#include <Radio.h>
#include <float.h>
#include <DateTime.h>


class GreenHouseHighLayer : public HighLayer<Message> {

private:
		GreenHouseHighLayerData greenHouseData[CommonValues::amountOfGreenHouses];
		GreenHouseHighLayerThresholds greenHouseThresholds[CommonValues::amountOfGreenHouses];

public:
		/*Layer methods*/
		~GreenHouseHighLayer() {}
		void initLayer(int);
		void analyze();
		void decodeMessage(Message&);
		Message& prepareMessage(Message&, int);
		Message recieveRFMessage();
		int findGreenHouseDataIndex(int id);
		int findGreenHouseThresholdsIndex(int id);
		void sendDataToServer(JsonObject& json);
		void getNewSettings();
		void checkMiddleLayer();
		String dateTimeToString(DateTime);

};

#endif
