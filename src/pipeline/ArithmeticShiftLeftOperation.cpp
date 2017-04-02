#include "ArithmeticShiftLeftOperation.h"
#include <QDebug>

ArithmeticShiftLeftOperation ArithmeticShiftLeftOperation ::singleton;

Value ArithmeticShiftLeftOperation::scalarOperation(int a, int b, int *wait){
  Value v;
  v.i = b << a;
  *wait = 1;
  return v;
}

