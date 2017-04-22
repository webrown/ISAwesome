#ifndef STORE_INSTRUCTION_H
#define STORE_INSTRUCTION_H
#include "StageData.h"
#include "BinaryInstruction.h"
class StoreInstruction : public BinaryInstruction {
  public:
    virtual void decode(StageData *, Register *);
    virtual void execute(StageData *);
    virtual void memory(StageData *, MemoryStructure *);
    virtual void writeBack(StageData *, Register *);
    virtual QVector<char> registerDependencies(StageData *sd);
    virtual QVector<char> registersToSet(StageData *sd);
    virtual bool decodeDump(StageData *, Register *r);
};
#endif
