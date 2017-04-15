#include "CpyInstruction.h"

Value CpyInstruction::scalarOperation(int a, int b) {
  Value v;
  v.i = a;
  return v;
}

Value CpyInstruction::scalarOperation(float a, float b) {
  Value v;
  v.f = a;
  return v;
}

