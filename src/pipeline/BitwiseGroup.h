#ifndef BITWISEGROUP_H
#define BITWISEGROUP_H
#include "ShortArithmeticInstruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"

//Defines add, sub, mul, div and mod stuff.

class AndInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int, int *wait);
    Value scalarOperation(float, float, int *wait);
};

class NandInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int, int *wait);
    Value scalarOperation(float, float, int *wait);
};
class OrInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int, int *wait);
    Value scalarOperation(float, float, int *wait);
};
class NorInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int, int *wait);
    Value scalarOperation(float, float, int *wait);
};
class XorInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int, int *wait);
    Value scalarOperation(float, float, int *wait);
};
class NotInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int, int *wait);
    Value scalarOperation(float, float, int *wait);
};
#endif
