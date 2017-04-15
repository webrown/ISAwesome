#ifndef PIPELINE_INSTRUCTION_H
#define PIPELINE_INSTRUCTION_H
#include <QVector>
#include "StageData.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
class StageData;
class Instruction {
  public:
    virtual void decode(StageData *sd, Register *r)=0;
    virtual void execute(StageData *sd)=0;
    virtual void memory(StageData *sd, MemoryStructure *)=0;
    virtual void writeBack(StageData *sd, Register *r)=0;
    virtual QVector<char> registerDependencies(StageData *sd)=0; // Returns a vector of registers this instruction depends on.
    virtual QVector<char> registersToSet(StageData *sd)=0; // Returns a vector of registers this instruction might modify.
    virtual bool decodeDump(StageData *, Register *r)=0; // If returns true, destroy this instruction right when it comes in.
};
#endif
