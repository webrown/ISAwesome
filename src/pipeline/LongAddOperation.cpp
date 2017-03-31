#include "LongAddOperation.h"
#include <QDebug>

LongAddOperation LongAddOperation::singleton;

void LongAddOperation::scalarOperation(int *a, int *b){
  // Calculate
  Value v;
  v.i = *a;
  long unsigned bigA = v.asUInt;
  v.i = *b;
  long unsigned bigB = v.asUInt;
  long unsigned bigC = bigA + bigB;
  // Load upper.
  *a = bigC >> 32;
  // Load lower.
  *b = bigC & 0xFFFFFFFF;
}
