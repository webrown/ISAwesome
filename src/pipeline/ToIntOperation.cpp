#include "ToIntOperation.h"
#include <QDebug>

ToIntOperation ToIntOperation ::singleton;

Value ToIntOperation::scalarOperation(int a, int b){
  (void) b;
  Value v;
  v.i = a;
  v.i = v.f;
  return v;
}

Value ToIntOperation::scalarOperation(float a, float b){
  (void) b;
  Value v;
  v.f = a;
  v.i = v.f;
  return v;
}

Value ToIntOperation::scalarOperation(int a, float b){
  (void) b;
  Value v;
  v.i = a;
  v.i = v.f;
  return v;
}

Value ToIntOperation::scalarOperation(float a, int b){
  (void) b;
  Value v;
  v.f = a;
  v.i = v.f;
  return v;
}
