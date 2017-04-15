#include "ShiftGroup.h"

int toIntSG(float v){
    Value x;
    x.f =v;
    return x.i;
}

Value LslInstruction::scalarOperation(int a, int b) {
  Value v;
  v.i = b << a;
  return v;
}

Value LslInstruction::scalarOperation(float a, float b) {
  Value v;
  v.f = toIntSG(b) << toIntSG(a);
  return v;
}

Value LsrInstruction::scalarOperation(int a, int b) {
  Value v;
  v.i = ((unsigned)b) >> a;
  return v;
}

Value LsrInstruction::scalarOperation(float a, float b) {
  Value v;
  v.f = ((unsigned)toIntSG(b)) >> toIntSG(a);
  return v;
}
Value AslInstruction::scalarOperation(int a, int b) {
  Value v;
  v.i = b << a;
  return v;
}

Value AslInstruction::scalarOperation(float a, float b) {
  Value v;
  v.f = toIntSG(b) << toIntSG(a);
  return v;
}
Value AsrInstruction::scalarOperation(int a, int b) {
  Value v;
   bool mustSwap = false;
  if(b < 0) {
    mustSwap = true;
    b = ~b;
  }
  // Shift.
  b >>= a;
  // Swap back
  if(mustSwap) b = ~b;
  v.i = b;
  return v;
}

Value AsrInstruction::scalarOperation(float a, float b) {
  Value v;
  return scalarOperation(toIntSG(a), toIntSG(b));
}


