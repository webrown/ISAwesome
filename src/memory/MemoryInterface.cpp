#include "MemoryInterface.h"
double MemoryInterface::write(QVector<int> *value, unsigned int address){
  QVector<Value> temp(value->size());
  for(int i = 0; i < value->size(); i++) {
    temp[i].asInt = value->at(i);
  }
  return write(&temp, address);
}
double MemoryInterface::write(int value, unsigned int address){
  Value v;
  v.toInt = value;
  return write(v, address);
}
double MemoryInterface::write(QVector<float> *value, unsigned int address){
  QVector<Value> temp(value->size());
  for(int i = 0; i < value->size(); i++) {
    temp[i].asFloat = value->at(i);
  }
  return write(&temp, address);
}
double MemoryInterface::write(float value, unsigned int address){
  Value v;
  v.toFloat = value;
  return write(v, address);
}
