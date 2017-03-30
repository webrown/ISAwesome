#include "MultiplyOperation.h"
#include <QDebug>

MultiplyOperation MultiplyOperation ::singleton;

Value MultiplyOperation::scalarOperation(int a, int b){
  Value v;
  v.i = a * b;
  return v;
}

Value MultiplyOperation::scalarOperation(float a, float b){
  Value v;
  v.f = a * b;
  return v;
}

