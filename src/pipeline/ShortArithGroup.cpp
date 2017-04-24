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
  Value v;
  if(a == 0) {
    // /0 is just big number.
    if(b > 0) {
      v.i = 2147483647;
    }
    if(b == 0) {
      v.i = 0;
    }
    if(b < 0) {
      v.i = -2147483648;
    }
  }
  else {
    // Save division.
    v.i = b / a;
  }
  *wait = 8;
  return v;
}

Value DivInstruction::scalarOperation(float a, float b, int *wait){
  Value v;
  if(a == 0) {
    // /0 is just big number.
    if(b > 0) {
      v.f = std::numeric_limits<float>::infinity();
    }
    if(b == 0) {
      v.f = 0;
    }
    if(b < 0) {
      v.f = -std::numeric_limits<float>::infinity();
    }
  }
  else {
    // Save division.
    v.f = b / a;
  }
  *wait = 16;
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
  if(a == 0) {
    v.i = -1;
  }
  else {
    v.i = b % a;
  }
  return v;
}

