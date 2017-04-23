#ifndef LOAD_INSTRUCTION_H
#define LOAD_INSTRUCTION_H
#include "StageData.h"
#include "MemoryInstruction.h"
class LoadInstruction : public MemoryInstruction {
  public:
    virtual void execute(StageData *, int *wait);
    virtual void memory(StageData *, MemoryStructure *, int *wait);
    virtual void writeBack(StageData *, Register *, int *wait);
    virtual QVector<char> registerDependencies(StageData *sd);
    virtual QVector<char> registersToSet(StageData *sd);
    virtual bool decodeDump(StageData *, Register *r);
};
#endif
