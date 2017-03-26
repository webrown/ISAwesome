#include "CopyOperation.h"

CopyOperation CopyOperation::singleton;

Value CopyOperation::scalarOperation(int a, int b){
  (void) b;
  Value v;
  v.i = a;
  return v;
}

Value CopyOperation::scalarOperation(int a, float b){
  (void) b;
  Value v;
  v.i = a;
  return v;
}

Value CopyOperation::scalarOperation(float a, int b){
  (void) b;
  Value v;
  v.f = a;
  return v;
}

Value CopyOperation::scalarOperation(float a, float b){
  (void) b;
  Value v;
  v.f = a;
  return v;
}
