#include "ConversionGroup.h"


Value ToiInstruction::scalarOperation(int a, int b) {
  Value v;
  v.i = (int)a;
  return v;
}

Value ToiInstruction::scalarOperation(float a, int b) {
  Value v;
  v.i = (int) a;
  return v;
}

Value TofInstruction::scalarOperation(int a, float b) {
  Value v;
  v.f = (float) a;
  return v;
}

Value TofInstruction::scalarOperation(float a, float b) {
  Value v;
  v.f = (float) a;
  return v;
}

