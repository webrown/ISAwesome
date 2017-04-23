#include "MultiplyOperation.h"
#include <QDebug>

MultiplyOperation MultiplyOperation ::singleton;

Value MultiplyOperation::scalarOperation(int a, int b, int *wait){
  *wait = 2+4+0+1;
  Value v;
  v.i = a * b;
  return v;
}

Value MultiplyOperation::scalarOperation(float a, float b, int *wait){
  *wait = 2+8+0+1;
  Value v;
  v.f = a * b;
  return v;
}

