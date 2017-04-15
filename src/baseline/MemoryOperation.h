#ifndef MEMORY_OPERATION_H
#define MEMORY_OPERATION_H
#include "../memory/MemoryStructure.h"
#include "../memory/Register.h"
class MemoryOperation{
    public:
        void memory(Register *registers, MemoryStructure *memory, bool arg1IsImmediate, unsigned int arg1, unsigned int arg2, int *wait);
        virtual void memoryOperation(Register *registers, MemoryStructure *memory, unsigned int address, unsigned int registerIndex, int *wait);
};
#endif
