#ifndef LONG_ADD_INSTRUCTION_H
#define LONG_ADD_INSTRUCTION_H
#include "LongArithmeticInstruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
class LongAddInstruction : public LongArithmeticInstruction {
  public:
    virtual void scalarOperation(int *, int *, int *wait);
};
#endif
