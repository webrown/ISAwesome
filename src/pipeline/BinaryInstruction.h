#ifndef BINARY_INSTRUCTION_H
#define BINARY_INSTRUCTION_H
#include "Instruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
class BinaryInstruction : public Instruction {
  public:
    virtual void decode(StageData *, Register *);
};
#endif
