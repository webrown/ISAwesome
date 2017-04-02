#include "LogicalShiftLeftOperation.h"
#include <QDebug>

LogicalShiftLeftOperation LogicalShiftLeftOperation ::singleton;

Value LogicalShiftLeftOperation::scalarOperation(int a, int b, int *wait){
  Value v;
  v.i = b << a;
  *wait = 1;
  return v;
}

