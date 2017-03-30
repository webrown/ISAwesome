#include "NotOperation.h"
#include <QDebug>

NotOperation NotOperation ::singleton;

Value NotOperation::scalarOperation(int a, int b){
  Value v;
  v.i = ~a;
  return v;
}

