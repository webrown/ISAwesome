#ifndef WRITE_VECTOR_ELEMENT_INSTRUCTION_H
#define WRITE_VECTOR_ELEMENT_INSTRUCTION_H
#include "TernaryInstruction.h"
#include "../memory/Register.h"
#include "../memory/MemoryStructure.h"
class WriteVectorElementInstruction : public TernaryInstruction {
  public:
    virtual void decode(StageData *sd, Register *r, int *wait); // Grab element you want to write and vector you want to modify
    virtual void execute(StageData *sd, int *wait); // Change element of vector
    virtual void memory(StageData *sd, MemoryStructure *, int *wait); // Nothing
    virtual void writeBack(StageData *sd, Register *r, int *wait); // Write vector back to memory.
    virtual QVector<char> registerDependencies(StageData *sd); // Weirdness with isImmediate1 makes this necessary :(
    virtual bool decodeDump(StageData *, Register *r); // Obey scalar flag.
};
#endif
