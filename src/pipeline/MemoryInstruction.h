#ifndef MEMORY_INSTRUCTION_H
#define MEMORY_INSTRUCTION_H
#include "Instruction.h"
#include "BinaryInstruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
class MemoryInstruction : public BinaryInstruction {
  public:
    virtual void decode(StageData *, Register *, int *wait);
};
#endif
