#include "ToFloatOperation.h"
#include <QDebug>

ToFloatOperation ToFloatOperation ::singleton;

Value ToFloatOperation::scalarOperation(int a, int b, int *wait){
  (void) b;
  *wait = 2+3+0+1;
  Value v;
  v.i = a;
  v.f = v.i;
  return v;
}

Value ToFloatOperation::scalarOperation(float a, float b, int *wait){
  (void) b;
  *wait = 2+3+0+1;
  Value v;
  v.f = a;
  v.f = v.i;
  return v;
}

Value ToFloatOperation::scalarOperation(int a, float b, int *wait){
  (void) b;
  *wait = 2+3+0+1;
  Value v;
  v.i = a;
  v.f = v.i;
  return v;
}

Value ToFloatOperation::scalarOperation(float a, int b, int *wait){
  (void) b;
  *wait = 2+3+0+1;
  Value v;
  v.f = a;
  v.f = v.i;
  return v;
}
