#ifndef SHIFTGROUP_H
#define SHIFTGROUP_H
#include "ShortArithmeticInstruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"

//Defines add, sub, mul, div and mod stuff.

class LslInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int, int *wait);
    Value scalarOperation(float, float, int *wait);
};

class LsrInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int, int *wait);
    Value scalarOperation(float, float, int *wait);
};
class AslInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int, int *wait);
    Value scalarOperation(float, float, int *wait);
};
class AsrInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int, int *wait);
    Value scalarOperation(float, float, int *wait);
};
#endif
