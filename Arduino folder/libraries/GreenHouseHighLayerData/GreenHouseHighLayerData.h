#ifndef GREEN_HOUSE_HIGH_LAYER_DATA
#define GREEN_HOUSE_HIGH_LAYER_DATA

#include <Arduino.h>
#include <LinkedList.h>

struct DataValue {
  String name;
  float value;
};

class GreenHouseHighLayerData {
private:
  int id;
  LinkedList<DataValue> values;
public:
  GreenHouseHighLayerData();
  GreenHouseHighLayerData(int);
  void updateValue(String,float);
  int getId();
  void setId(int);
  int getValuesSize();
  DataValue getValue(int i);
};

#endif
