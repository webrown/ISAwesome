#ifndef CONVERSIONGROUP_H
#define CONVERSIONGROUP_H
#include "ShortArithmeticInstruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"

//Defines add, sub, mul, div and mod stuff.

class ToiInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int);
    Value scalarOperation(float, float);
};

class TofInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int);
    Value scalarOperation(float, float);
};
#endif
