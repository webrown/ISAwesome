#include "CpyInstruction.h"
#include <QDebug>

Value CpyInstruction::scalarOperation(int a, int b, int *wait){
  *wait = 1;
  (void) b;
  Value v;
  v.i = a;
  return v;
}

Value CpyInstruction::scalarOperation(float a, float b, int *wait){
  *wait = 1;
  (void) b;
  Value v;
  v.f = a;
  return v;
}

Value CpyInstruction::scalarOperation(int a, float b, int *wait){
  *wait = 1;
  (void) b;
  Value v;
  v.i = a;
  return v;
}

Value CpyInstruction::scalarOperation(float a, int b, int *wait){
  *wait = 1;
  (void) b;
  Value v;
  v.f = a;
  return v;
}
