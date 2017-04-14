#ifndef TERNARY_INSTRUCTION_H
#define TERNARY_INSTRUCTION_H
#include "Instruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
class TernaryInstruction : public Instruction {
  public:
    virtual void decode(StageData *sd, Register *r);
    virtual QVector<char> registerDependencies(StageData *sd); // Assumes dependence on all
    virtual QVector<char> registersToSet(StageData *sd);       // Assumes third operand is dest reg
};
#endif
