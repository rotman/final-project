#include "GreenHouseHighLayerThresholds.h"

GreenHouseHighLayerThresholds::GreenHouseHighLayerThresholds() {

}

GreenHouseHighLayerThresholds::GreenHouseHighLayerThresholds(int id) {
    this->id = id;
    this->values = LinkedList<ThresholdsValue>();
}

void GreenHouseHighLayerThresholds::updateValue(String name , float minValue , float maxValue) {
  int i;
  bool found = false;
  ThresholdsValue data;
  for (i = 0 ; i < values.size() ; i++) {
    if (values.get(i).name == name) {
      data = values.get(i);
      data.minValue = minValue;
      data.maxValue = maxValue;
      values.set(i,data);
      found = true;
    }
  }

  if (!found) {
    data.name = name;
    data.minValue = minValue;
    data.maxValue = maxValue;
    values.add(data);
  }
}

int GreenHouseHighLayerThresholds::getId() {
  return id;
}

void GreenHouseHighLayerThresholds::setId(int id) {
  this->id = id;
}

int GreenHouseHighLayerThresholds::getValuesSize() {
  return values.size();
}

ThresholdsValue GreenHouseHighLayerThresholds::getValue(int i) {
  return values.get(i);
}
