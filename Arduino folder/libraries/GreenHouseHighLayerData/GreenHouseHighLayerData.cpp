#include "GreenHouseHighLayerData.h"

GreenHouseHighLayerData::GreenHouseHighLayerData() {

}

GreenHouseHighLayerData::GreenHouseHighLayerData(int id) {
    this->id = id;
    this->values = LinkedList<DataValue>();
}

void GreenHouseHighLayerData::updateValue(String name , float value) {
  int i;
  bool found = false;
  for (i = 0 ; i < values.size() ; i++) {
    if (values.get(i).name == name) {
      DataValue data = values.get(i);
      data.value = value;
      values.set(i,data);
      found = true;
    }
  }

  if (!found) {
    DataValue data;
    data.name = name;
    data.value = value;
    values.add(data);
  }
}

int GreenHouseHighLayerData::getId() {
  return id;
}

void GreenHouseHighLayerData::setId(int id) {
  this->id = id;
}

int GreenHouseHighLayerData::getValuesSize() {
  return values.size();
}

DataValue GreenHouseHighLayerData::getValue(int i) {
  return values.get(i);
}
