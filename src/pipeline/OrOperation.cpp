#include "OrOperation.h"
#include <QDebug>

OrOperation OrOperation ::singleton;

Value OrOperation::scalarOperation(int a, int b){
  Value v;
  v.i = a | b;
  return v;
}

