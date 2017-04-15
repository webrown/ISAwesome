#include "AddInstruction.h"
Value AddInstruction::scalarOperation(int a, int b) {
  Value v;
  v.i = a+b;
  return v;
}

Value AddInstruction::scalarOperation(float a, float b) {
  Value v;
  v.f = a+b;
  return v;
}

