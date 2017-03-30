#include "DivideOperation.h"
#include <QDebug>

DivideOperation DivideOperation ::singleton;

Value DivideOperation::scalarOperation(int a, int b){
  Value v;
  v.i = a / b;
  return v;
}

Value DivideOperation::scalarOperation(float a, float b){
  Value v;
  v.f = a / b;
  return v;
}

