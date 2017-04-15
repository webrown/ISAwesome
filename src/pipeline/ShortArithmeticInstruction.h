#ifndef SHORT_ARITHMETIC_INSTRUCTION_H
#define SHORT_ARITHMETIC_INSTRUCTION_H
#include "BinaryInstruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
class ShortArithmeticInstruction : public BinaryInstruction {
  public:
    virtual void execute(StageData *sd);
    virtual void memory(StageData *sd, MemoryStructure *);
    virtual void writeBack(StageData *sd, Register *r);
    virtual QVector<char> registerDependencies(StageData *sd);
    virtual QVector<char> registersToSet(StageData *sd);
    virtual bool decodeDump(StageData *, Register *r);

    virtual Value scalarOperation(int, int);     // Override these
    virtual Value scalarOperation(int, float);   // Override these
    virtual Value scalarOperation(float, int);   // Override these
    virtual Value scalarOperation(float, float); // Override these
    Value scalarOperation(bool arg1IsFloat, bool arg2IsFloat, Value a, Value b);
};
#endif
