#include "ConversionGroup.h"

//int toInt(float v){
//    Value x;
//    x.f =v;
//    return x.i;
//}

Value ToiInstruction::scalarOperation(int a, int b) {
  Value v;
  v.i = (int)a;
  return v;
}

Value ToiInstruction::scalarOperation(float a, float b) {
  Value v;
  v.i = (int) a;
  return v;
}

Value TofInstruction::scalarOperation(int a, int b) {
  Value v;
  v.f = (float) a;
  return v;
}

Value TofInstruction::scalarOperation(float a, float b) {
  Value v;
  v.f = (float) a;
  return v;
}

