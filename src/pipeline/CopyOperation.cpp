#include "CopyOperation.h"

CopyOperation CopyOperation::singleton;

Value CopyOperation::scalarOperation(int a, int b, int *wait){
  (void) b;
  Value v;
  v.i = a;
  *wait = 1;
  return v;
}

Value CopyOperation::scalarOperation(int a, float b, int *wait){
  (void) b;
  Value v;
  v.i = a;
  *wait = 1;
  return v;
}

Value CopyOperation::scalarOperation(float a, int b, int *wait){
  (void) b;
  Value v;
  v.f = a;
  *wait = 1;
  return v;
}

Value CopyOperation::scalarOperation(float a, float b, int *wait){
  (void) b;
  Value v;
  v.f = a;
  *wait = 1;
  return v;
}
