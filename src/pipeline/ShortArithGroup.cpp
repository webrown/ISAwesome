#include "ShortArithGroup.h"
#define __ADD__ +
#define __SUB__ -
#define __DIV__ /
#define __MOD__ %
#define __MUL__ *

Value AddInstruction::scalarOperation(int a, int b, int *wait){
  *wait = 2;
  Value v;
  v.i = a __ADD__ b;
  return v;
}

Value AddInstruction::scalarOperation(float a, float b, int *wait){
  *wait = 4;
  Value v;
  v.f = a __ADD__ b;
  return v;
}

Value SubInstruction::scalarOperation(int a, int b, int *wait){
  *wait = 2;
  Value v;
  v.i = b __SUB__ a;
  return v;
}

Value SubInstruction::scalarOperation(float a, float b, int *wait){
  *wait = 4;
  Value v;
  v.f = b  __SUB__ a;
  return v;
}
Value DivInstruction::scalarOperation(int a, int b, int *wait){
  *wait = 8;
  Value v;
  v.i = b __DIV__ a;
  return v;
}

Value DivInstruction::scalarOperation(float a, float b, int *wait){
  *wait = 16;
  Value v;
  v.f = b __DIV__ a;
  return v;
}
Value MulInstruction::scalarOperation(int a, int b, int *wait){
  *wait = 4;
  Value v;
  v.i = a __MUL__ b;
  return v;
}

Value MulInstruction::scalarOperation(float a, float b, int *wait){
  *wait = 8;
  Value v;
  v.f = a __MUL__ b;
  return v;
}

Value ModInstruction::scalarOperation(int a, int b, int *wait){
  *wait = 8;
  Value v;
  v.i = b __MOD__ a;
  return v;
}

