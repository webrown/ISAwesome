#include "ToFloatOperation.h"
#include <QDebug>

ToFloatOperation ToFloatOperation ::singleton;

Value ToFloatOperation::scalarOperation(int a, int b){
  (void) b;
  Value v;
  v.i = a;
  v.f = v.i;
  return v;
}

Value ToFloatOperation::scalarOperation(float a, float b){
  (void) b;
  Value v;
  v.f = a;
  v.f = v.i;
  return v;
}

Value ToFloatOperation::scalarOperation(int a, float b){
  (void) b;
  Value v;
  v.i = a;
  v.f = v.i;
  return v;
}

Value ToFloatOperation::scalarOperation(float a, int b){
  (void) b;
  Value v;
  v.f = a;
  v.f = v.i;
  return v;
}
