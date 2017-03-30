#include "LogicalShiftLeftOperation.h"
#include <QDebug>

LogicalShiftLeftOperation LogicalShiftLeftOperation ::singleton;

Value LogicalShiftLeftOperation::scalarOperation(int a, int b){
  Value v;
  v.i = b << a;
  return v;
}

