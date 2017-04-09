#include "ToIntOperation.h"
#include <QDebug>

ToIntOperation ToIntOperation ::singleton;

Value ToIntOperation::scalarOperation(int a, int b, int *wait){
  (void) b;
  *wait = 2;
  Value v;
  v.i = a;
  v.i = v.f;
  return v;
}

Value ToIntOperation::scalarOperation(float a, float b, int *wait){
  (void) b;
  *wait = 2;
  Value v;
  v.f = a;
  v.i = v.f;
  return v;
}

Value ToIntOperation::scalarOperation(int a, float b, int *wait){
  (void) b;
  *wait = 2;
  Value v;
  v.i = a;
  v.i = v.f;
  return v;
}

Value ToIntOperation::scalarOperation(float a, int b, int *wait){
  (void) b;
  *wait = 2;
  Value v;
  v.f = a;
  v.i = v.f;
  return v;
}
