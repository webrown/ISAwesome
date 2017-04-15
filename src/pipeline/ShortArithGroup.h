#ifndef SHORTARITHGROUP_H
#define SHORTARITHGROUP_H
#include "ShortArithmeticInstruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"

//Defines add, sub, mul, div and mod stuff.

class AddInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int);
    Value scalarOperation(float, float);
};

class SubInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int);
    Value scalarOperation(float, float);
};
class DivInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int);
    Value scalarOperation(float, float);
};
class MulInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int);
    Value scalarOperation(float, float);
};
class ModInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int);
    Value scalarOperation(float, float);
};
#endif
