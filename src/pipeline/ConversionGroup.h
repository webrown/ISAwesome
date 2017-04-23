#ifndef CONVERSIONGROUP_H
#define CONVERSIONGROUP_H
#include "ShortArithmeticInstruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"

//Defines add, sub, mul, div and mod stuff.

class ToiInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int, int *wait);
    Value scalarOperation(float, int, int *wait);
};

class TofInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, float, int *wait);
    Value scalarOperation(float, float, int *wait);
};
#endif
