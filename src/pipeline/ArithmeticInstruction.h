#ifndef ARITHMETIC_INSTRUCTION_H
#define ARITHMETIC_INSTRUCTION_H
#include "Instruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
class ArithmeticInstruction : public Instruction {
  public:
    virtual void decode(StageData *, Register *)=0;
    virtual void execute(StageData *)=0;
    virtual void memory(StageData *, MemoryStructure *); // Nothing
    virtual void writeBack(StageData *, Register *)=0;
  
};
#endif
