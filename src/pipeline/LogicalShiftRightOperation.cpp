#include "LogicalShiftRightOperation.h"
#include <QDebug>

LogicalShiftRightOperation LogicalShiftRightOperation ::singleton;

Value LogicalShiftRightOperation::scalarOperation(int a, int b, int *wait){
  Value v;
  v.i = ((unsigned)b) >> a;
  *wait = 1;
  return v;
}
