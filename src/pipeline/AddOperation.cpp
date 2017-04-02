#include "AddOperation.h"
#include <QDebug>

AddOperation AddOperation::singleton;

Value AddOperation::scalarOperation(int a, int b, int *wait){
  Value v;
  v.i = a+b;
  *wait = 1;
  return v;
}

Value AddOperation::scalarOperation(float a, float b, int *wait){
  Value v;
  v.f = a+b;
  *wait = 2;
  return v;
}
