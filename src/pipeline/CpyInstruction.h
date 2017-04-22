#ifndef CPYINSTRUCTION_H
#define CPYINSTRUCTION_H
#include "ShortArithmeticInstruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"


class CpyInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int);
    Value scalarOperation(float, float);
    Value scalarOperation(int, float);
    Value scalarOperation(float, int);
};

#endif
