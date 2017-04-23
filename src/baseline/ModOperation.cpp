#include "ModOperation.h"
#include <QDebug>

ModOperation ModOperation ::singleton;

Value ModOperation::scalarOperation(int a, int b, int *wait){
  *wait = 2+8+0+1;
  Value v;
  if(a == 0) {
    v.i = -1;
  }
  else {
    v.i = b % a;
  }
  return v;
}

