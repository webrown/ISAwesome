#include "ArithmeticShiftRightOperation.h"
#include <QDebug>

ArithmeticShiftRightOperation ArithmeticShiftRightOperation ::singleton;

Value ArithmeticShiftRightOperation::scalarOperation(int a, int b, int *wait){
  Value v;
  // Get rid of -.  - is where evil happens with ASR.
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
  *wait = 1;
  return v;
}

