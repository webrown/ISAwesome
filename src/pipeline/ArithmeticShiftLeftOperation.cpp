#include "ArithmeticShiftLeftOperation.h"
#include <QDebug>

ArithmeticShiftLeftOperation ArithmeticShiftLeftOperation ::singleton;

Value ArithmeticShiftLeftOperation::scalarOperation(int a, int b){
  Value v;
  v.i = b << a;
  return v;
}

