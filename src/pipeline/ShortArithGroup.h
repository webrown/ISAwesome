#ifndef SHORTARITHGROUP_H
#define SHORTARITHGROUP_H
#include "ShortArithmeticInstruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"

//Defines add, sub, mul, div and mod stuff.

class AddInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int, int *wait);
    Value scalarOperation(float, float, int *wait);
};

class SubInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int, int *wait);
    Value scalarOperation(float, float, int *wait);
};
class DivInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int, int *wait);
    Value scalarOperation(float, float, int *wait);
};
class MulInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int, int *wait);
    Value scalarOperation(float, float, int *wait);
};
class ModInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int, int *wait);
};
#endif
