#ifndef CPYINSTRUCTION_H
#define CPYINSTRUCTION_H
#include "ShortArithmeticInstruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"


class CpyInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int, int *wait);
    Value scalarOperation(float, float, int *wait);
    Value scalarOperation(int, float, int *wait);
    Value scalarOperation(float, int, int *wait);
};

#endif
