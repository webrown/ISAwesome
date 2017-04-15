#ifndef CpyInstruction_H
#define CpyInstruction_H
#include "ShortArithmeticInstruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"


class CpyInstruction : public ShortArithmeticInstruction {
  public:
    Value scalarOperation(int, int);
    Value scalarOperation(float, float);
};

#endif
