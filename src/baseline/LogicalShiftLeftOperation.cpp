#include "LogicalShiftLeftOperation.h"
#include <QDebug>

LogicalShiftLeftOperation LogicalShiftLeftOperation ::singleton;

Value LogicalShiftLeftOperation::scalarOperation(int a, int b, int *wait){
  *wait = 2+1+0+1;
  Value v;
  v.i = b << a;
  return v;
}

