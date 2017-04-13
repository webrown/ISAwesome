#ifndef ADD_INSTRUCTION_H
#define ADD_INSTRUCTION_H
#include "BinaryInstruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
class AddInstruction : public BinaryInstruction {
  public:
    virtual void execute(StageData *sd);
    virtual void memory(StageData *sd, MemoryStructure *);
    virtual void writeBack(StageData *sd, Register *r);
    virtual QVector<char> registerDependencies(StageData *sd);
    virtual QVector<char> registersToSet(StageData *sd);
    virtual bool decodeDump(StageData *, Register *r);

    Value scalarOperation(int, int);
    Value scalarOperation(int, float);
    Value scalarOperation(float, int);
    Value scalarOperation(float, float);
    Value scalarOperation(bool arg1IsFloat, bool arg2IsFloat, Value a, Value b);
};
#endif
