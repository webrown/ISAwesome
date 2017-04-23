#ifndef COMPARE_INSTRUCTION_H
#define COMPARE_INSTRUCTION_H
#include "StageData.h"
#include "BinaryInstruction.h"
class CompareInstruction : public BinaryInstruction {
  public:
    virtual void decode(StageData *, Register *, int *wait);
    virtual void execute(StageData *, int *wait);
    virtual void memory(StageData *, MemoryStructure *, int *wait);
    virtual void writeBack(StageData *, Register *, int *wait);
    virtual QVector<char> registerDependencies(StageData *sd);
    virtual QVector<char> registersToSet(StageData *sd);
    virtual bool decodeDump(StageData *, Register *r);

    Value newFlag(int a, int b, int *wait);
    Value newFlag(float a, float b, int *wait);
    Value newFlag(bool arg1IsFloat, bool arg2IsFloat, Value a, Value b, Value oldFlag, int *wait);
};
#endif
