#include "NotOperation.h"
#include <QDebug>

NotOperation NotOperation ::singleton;

Value NotOperation::scalarOperation(int a, int b, int *wait){
  (void) b;
  *wait = 2+1+0+1;
  Value v;
  v.i = ~a;
  return v;
}

