#ifndef GREEN_HOUSE_HIGH_LAYER_THRESHOLDS
#define GREEN_HOUSE_HIGH_LAYER_THRESHOLDS

#include <Arduino.h>
#include <LinkedList.h>

struct ThresholdsValue {
  String name;
  float value;
};

class GreenHouseHighLayerThresholds {
private:
  int id;
  String last_updated;
  LinkedList<ThresholdsValue> values;
public:
  GreenHouseHighLayerThresholds();
  GreenHouseHighLayerThresholds(int);
  void updateValue(String,float);
  int getId();
  void setId(int);
  String getLastUpdated();
  void setLastUpdated(String);
  int getValuesSize();
  ThresholdsValue getValue(int i);
};

#endif
