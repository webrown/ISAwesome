#include "LogicalShiftRightOperation.h"
#include <QDebug>

LogicalShiftRightOperation LogicalShiftRightOperation ::singleton;

Value LogicalShiftRightOperation::scalarOperation(int a, int b){
  Value v;
  v.i = ((unsigned)b) >> a;
  return v;
}
