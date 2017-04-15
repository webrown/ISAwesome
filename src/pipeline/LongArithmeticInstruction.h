#ifndef LONG_ARITHMETIC_INSTRUCTION_H
#define LONG_ARITHMETIC_INSTRUCTION_H
#include "Instruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
class LongArithmeticInstruction : public Instruction {
  public:
    virtual void decode(StageData *, Register *);
    virtual void execute(StageData *);
    virtual void memory(StageData *, MemoryStructure *);
    virtual void writeBack(StageData *, Register *);
    virtual void _operation(int *, int *);
    virtual void _operation(float *, float *);
};
#endif
