#include "LongSubtractOperation.h"
#include <QDebug>

LongSubtractOperation LongSubtractOperation::singleton;

void LongSubtractOperation::scalarOperation(int *a, int *b){
  // Calculate
  Value v;
  v.i = *a;
  long bigA = v.asInt;
  v.i = *b;
  long bigB = v.asInt;
  long bigC = bigB - bigA;

  // Load upper.
  *a = bigC >> 32;
  // Load lower.
  *b = bigC & 0xFFFFFFFF;
}
