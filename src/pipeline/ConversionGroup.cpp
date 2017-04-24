#include "ConversionGroup.h"

Value ToiInstruction::scalarOperation(int a, int b, int *wait){
  *wait = 4;
  (void) b;
  Value v;
  v.i = a;
  v.i = v.f;
  return v;
}

Value ToiInstruction::scalarOperation(float a, float b, int *wait){
  *wait = 4;
  (void) b;
  Value v;
  v.f = a;
  v.i = v.f;
  return v;
}

Value ToiInstruction::scalarOperation(int a, float b, int *wait){
  *wait = 4;
  (void) b;
  Value v;
  v.i = a;
  v.i = v.f;
  return v;
}

Value ToiInstruction::scalarOperation(float a, int b, int *wait){
  *wait = 4;
  (void) b;
  Value v;
  v.f = a;
  v.i = v.f;
  return v;
}


Value TofInstruction::scalarOperation(int a, int b, int *wait){
  *wait = 3;
  (void) b;
  Value v;
  v.i = a;
  v.f = v.i;
  return v;
}

Value TofInstruction::scalarOperation(float a, float b, int *wait){
  *wait = 3;
  (void) b;
  Value v;
  v.f = a;
  v.f = v.i;
  return v;
}

Value TofInstruction::scalarOperation(int a, float b, int *wait){
  *wait = 3;
  (void) b;
  Value v;
  v.i = a;
  v.f = v.i;
  return v;
}

Value TofInstruction::scalarOperation(float a, int b, int *wait){
  *wait = 3;
  (void) b;
  Value v;
  v.f = a;
  v.f = v.i;
  return v;
}



