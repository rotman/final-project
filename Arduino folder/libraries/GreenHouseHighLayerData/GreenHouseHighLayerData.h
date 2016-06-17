#ifndef GREEN_HOUSE_HIGH_LAYER_DATA
#define GREEN_HOUSE_HIGH_LAYER_DATA

#include <Arduino.h>
#include <LinkedList.h>
#include <DateTime.h>

struct DataValue {
  String name;
  float value;
  DateTime dateTime;
};

class GreenHouseHighLayerData {
private:
  int id;
  LinkedList<DataValue> values;
  unsigned long lastChecked;
  bool working;
public:
  GreenHouseHighLayerData();
  GreenHouseHighLayerData(int);
  void updateValue(String,float,DateTime);
  int getId();
  void setId(int);
  int getValuesSize();
  DataValue getValue(int i);
  unsigned long getLastChecked();
  void setLastChecked(unsigned long);
  bool getWorking();
  void setWorking(bool);
};

#endif
