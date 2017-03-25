#ifndef STORE_OPERATION_H
#define STORE_OPERATION_H
#include "../memory/MemoryStructure.h"
#include "../memory/Register.h"
#include "MemoryOperation.h"
class StoreOperation : public MemoryOperation{
    public:
        static void memoryOperation(Register *registers, MemoryStructure *memory, unsigned int address, unsigned int registerIndex);
};
#endif
