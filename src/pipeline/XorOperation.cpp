#include "XorOperation.h"
#include <QDebug>

XorOperation XorOperation ::singleton;

Value XorOperation::scalarOperation(int a, int b){
  Value v;
  v.i = a ^ b;
  return v;
}
