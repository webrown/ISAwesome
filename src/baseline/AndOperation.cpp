#include "AndOperation.h"
#include <QDebug>

AndOperation AndOperation::singleton;

Value AndOperation::scalarOperation(int a, int b, int *wait){
  Value v;
  v.i = a & b;
  *wait = 1;
  return v;
}
