#ifndef SHORT_ARITHMETIC_INSTRUCTION_H
#define SHORT_ARITHMETIC_INSTRUCTION_H
#include "BinaryInstruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
class ShortArithmeticInstruction : public BinaryInstruction {
  public:
    virtual void execute(StageData *sd, int *wait);
    virtual void memory(StageData *sd, MemoryStructure *, int *wait);
    virtual void writeBack(StageData *sd, Register *r, int *wait);
    virtual QVector<char> registerDependencies(StageData *sd);
    virtual QVector<char> registersToSet(StageData *sd);
    virtual bool decodeDump(StageData *, Register *r);

    virtual Value scalarOperation(int, int, int *wait);     // Override these
    virtual Value scalarOperation(int, float, int *wait);   // Override these
    virtual Value scalarOperation(float, int, int *wait);   // Override these
    virtual Value scalarOperation(float, float, int *wait); // Override these
    Value scalarOperation(bool arg1IsFloat, bool arg2IsFloat, Value a, Value b, int *wait);
    int toInt(float v){
        Value x;
        x.f =v;
        return x.i;
    }


};


#endif
