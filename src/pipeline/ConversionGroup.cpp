#include "ConversionGroup.h"

Value ToiInstruction::scalarOperation(int a, int b, int *wait){
  *wait = 1;
  Value v;
  v.i = (int)a;
  return v;
}

Value ToiInstruction::scalarOperation(float a, int b, int *wait){
  *wait = 4;
  Value v;
  v.i = (int) a;
  return v;
}

Value TofInstruction::scalarOperation(int a, float b, int *wait){
  *wait = 3;
  Value v;
  v.f = (float) a;
  return v;
}

Value TofInstruction::scalarOperation(float a, float b, int *wait){
  *wait = 1;
  Value v;
  v.f = (float) a;
  return v;
}

