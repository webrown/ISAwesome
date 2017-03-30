#include "NandOperation.h"
#include <QDebug>

NandOperation NandOperation ::singleton;

Value NandOperation::scalarOperation(int a, int b){
  Value v;
  v.i = ~(a & b);
  return v;
}

