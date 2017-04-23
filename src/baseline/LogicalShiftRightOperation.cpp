#include "LogicalShiftRightOperation.h"
#include <QDebug>

LogicalShiftRightOperation LogicalShiftRightOperation ::singleton;

Value LogicalShiftRightOperation::scalarOperation(int a, int b, int *wait){
  *wait = 2+1+0+1;
  Value v;
  v.i = ((unsigned)b) >> a;
  return v;
}
