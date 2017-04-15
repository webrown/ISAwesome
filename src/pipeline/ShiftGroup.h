#ifndef SHIFTGROUP_H
#define SHIFTGROUP_H
#include "ShortArithmeticInstruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"

//Defines add, sub, mul, div and mod stuff.

class LslInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int);
    Value scalarOperation(float, float);
};

class LsrInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int);
    Value scalarOperation(float, float);
};
class AslInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int);
    Value scalarOperation(float, float);
};
class AsrInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int);
    Value scalarOperation(float, float);
};
#endif
