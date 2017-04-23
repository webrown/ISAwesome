#ifndef LONG_ARITHMETIC_INSTRUCTION_H
#define LONG_ARITHMETIC_INSTRUCTION_H
#include "BinaryInstruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
class LongArithmeticInstruction : public BinaryInstruction {
  public:
    virtual void decode(StageData *, Register *, int *wait);
    virtual void execute(StageData *sd, int *wait);
    virtual void memory(StageData *sd, MemoryStructure *, int *wait);
    virtual void writeBack(StageData *sd, Register *r, int *wait);
    virtual QVector<char> registerDependencies(StageData *sd);
    virtual QVector<char> registersToSet(StageData *sd);
    virtual bool decodeDump(StageData *, Register *r);

    virtual void scalarOperation(int *, int *, int *wait);     // Override these
};
#endif
