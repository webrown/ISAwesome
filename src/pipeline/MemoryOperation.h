#ifndef MEMORY_OPERATION_H
#define MEMORY_OPERATION_H
#include "../memory/MemoryStructure.h"
#include "../memory/Register.h"
class MemoryOperation{
    public:
        static void memory(Register *registers, MemoryStructure *memory, bool arg1IsImmediate, unsigned int arg1, unsigned int arg2);
        static void memoryOperation(Register *registers, MemoryStructure *memory, unsigned int address, unsigned int registerIndex);
};
#endif
