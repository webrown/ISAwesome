#include "SubtractOperation.h"
#include <QDebug>

SubtractOperation SubtractOperation ::singleton;

Value SubtractOperation::scalarOperation(int a, int b){
  Value v;
  v.i = b - a;
  return v;
}

Value SubtractOperation::scalarOperation(float a, float b){
  Value v;
  v.f = b - a;
  return v;
}

