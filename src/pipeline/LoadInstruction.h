#ifndef LOAD_INSTRUCTION_H
#define LOAD_INSTRUCTION_H
#include "StageData.h"
#include "MemoryInstruction.h"
class LoadInstruction : public MemoryInstruction {
  public:
    virtual void execute(StageData *);
    virtual void memory(StageData *, MemoryStructure *);
    virtual void writeBack(StageData *, Register *);
    virtual QVector<char> registerDependencies(StageData *sd);
    virtual QVector<char> registersToSet(StageData *sd);
    virtual bool decodeDump(StageData *, Register *r);
};
#endif
