#include "AndOperation.h"
#include <QDebug>

AndOperation AndOperation::singleton;

Value AndOperation::scalarOperation(int a, int b){
  Value v;
  v.i = a & b;
qDebug() << v.i << "INN";
  return v;
}
