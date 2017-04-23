#include "LongAddInstruction.h"
void LongAddInstruction::scalarOperation(int *a, int *b, int *wait) {
  *wait = 4;
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


