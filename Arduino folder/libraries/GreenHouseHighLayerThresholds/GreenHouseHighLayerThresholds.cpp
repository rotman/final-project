#include "GreenHouseHighLayerThresholds.h"

GreenHouseHighLayerThresholds::GreenHouseHighLayerThresholds() {

}

GreenHouseHighLayerThresholds::GreenHouseHighLayerThresholds(int id) {
    this->id = id;
    this->values = LinkedList<ThresholdsValue>();
}

void GreenHouseHighLayerThresholds::updateValue(String name , float value) {
  int i;
  bool found = false;
  ThresholdsValue data;
  for (i = 0 ; i < values.size() ; i++) {
    if (values.get(i).name == name) {
      data = values.get(i);
      data.value = value;
      values.set(i,data);
      found = true;
    }
  }

  if (!found) {
    data.name = name;
    data.value = value;
    values.add(data);
  }
}

int GreenHouseHighLayerThresholds::getId() {
  return id;
}

void GreenHouseHighLayerThresholds::setId(int id) {
  this->id = id;
}

String GreenHouseHighLayerThresholds::getLastUpdated() {
  return last_updated;
}

void GreenHouseHighLayerThresholds::setLastUpdated(String last_updated) {
  this->last_updated = last_updated;
}

int GreenHouseHighLayerThresholds::getValuesSize() {
  return values.size();
}

ThresholdsValue GreenHouseHighLayerThresholds::getValue(int i) {
  return values.get(i);
}
