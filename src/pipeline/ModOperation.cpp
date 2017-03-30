#include "ModOperation.h"
#include <QDebug>

ModOperation ModOperation ::singleton;

Value ModOperation::scalarOperation(int a, int b){
  Value v;
  v.i = a % b;
  return v;
}

