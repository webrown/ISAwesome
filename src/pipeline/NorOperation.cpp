#include "NorOperation.h"
#include <QDebug>

NorOperation NorOperation ::singleton;

Value NorOperation::scalarOperation(int a, int b, int *wait){
  *wait = 1;
  Value v;
  v.i = ~(a | b);
  return v;
}

