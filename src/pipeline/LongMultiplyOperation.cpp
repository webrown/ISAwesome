#include "LongMultiplyOperation.h"
#include <QDebug>

LongMultiplyOperation LongMultiplyOperation::singleton;

void LongMultiplyOperation::scalarOperation(int *a, int *b, int *wait){
  *wait = 8;
  // Calculate
  long unsigned bigA = *a;
  long unsigned bigB = *b;
  long unsigned bigC = bigA * bigB;
  // Load upper.
  *a = bigC >> 32;
  // Load lower.
  *b = bigC & 0xFFFFFFFF;
}
