#include "ArithmeticShiftLeftOperation.h"
#include <QDebug>

ArithmeticShiftLeftOperation ArithmeticShiftLeftOperation ::singleton;

Value ArithmeticShiftLeftOperation::scalarOperation(int a, int b, int *wait){
  *wait = 2+1+0+1;
  Value v;
  v.i = b << a;
  return v;
}

