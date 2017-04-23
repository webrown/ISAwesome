#include "XorOperation.h"
#include <QDebug>

XorOperation XorOperation ::singleton;

Value XorOperation::scalarOperation(int a, int b, int *wait){
  *wait = 2+1+0+1;
  Value v;
  v.i = a ^ b;
  return v;
}

