#ifndef LONG_ARITHMETIC_INSTRUCTION_H
#define LONG_ARITHMETIC_INSTRUCTION_H
#include "BinaryInstruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
class LongArithmeticInstruction : public BinaryInstruction {
  public:
    virtual void decode(StageData *, Register *);
    virtual void execute(StageData *sd);
    virtual void memory(StageData *sd, MemoryStructure *);
    virtual void writeBack(StageData *sd, Register *r);
    virtual QVector<char> registerDependencies(StageData *sd);
    virtual QVector<char> registersToSet(StageData *sd);
    virtual bool decodeDump(StageData *, Register *r);

    virtual void scalarOperation(int *, int *, int *wait);     // Override these
};
#endif
