#ifndef TERNARY_INSTRUCTION_H
#define TERNARY_INSTRUCTION_H
#include "Instruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
class TernaryInstruction : public Instruction {
  public:
    virtual void decode(StageData *, Register *r);
};
#endif
