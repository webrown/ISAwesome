#include "AddOperation.h"
#include <QDebug>

AddOperation AddOperation::singleton;

Value AddOperation::scalarOperation(int a, int b){
  Value v;
  v.i = a+b;
  return v;
}

Value AddOperation::scalarOperation(float a, float b){
  Value v;
  v.f = a+b;
  return v;
}
