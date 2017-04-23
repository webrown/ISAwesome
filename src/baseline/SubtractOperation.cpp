#include "SubtractOperation.h"
#include <QDebug>

SubtractOperation SubtractOperation ::singleton;

Value SubtractOperation::scalarOperation(int a, int b, int *wait){
  *wait = 2+2+0+1;
  Value v;
  v.i = b - a;
  return v;
}

Value SubtractOperation::scalarOperation(float a, float b, int *wait){
  *wait = 2+4+0+1;
  Value v;
  v.f = b - a;
  return v;
}

