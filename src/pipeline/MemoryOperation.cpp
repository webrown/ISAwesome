#include "MemoryOperation.h"

void MemoryOperation::memory(Register *registers, MemoryStructure *memory, bool arg1IsImmediate, unsigned int arg1, unsigned int arg2) {
    if(!arg1IsImmediate) {
      // Looks like we'll need to replace arg1 with its register value....
      // If arg1 is a vector, it doesn't make sense as an address.
      if(Register::isVectorIndex(arg1)) return;

      // It's bad form to store addresses in floating registers.
      if(Register::isFloatIndex(arg1)) return;

      // Now see what's in register arg1
      arg1 = registers->read(arg1).asUInt;
    }

    // Send query to memory.
    memoryOperation(registers, memory, arg1, arg2);
}

void MemoryOperation::memoryOperation(Register *registers, MemoryStructure *memory, unsigned int address, unsigned int registerIndex) {
  (void)registers;
  (void)memory;
  (void)address;
  (void)registerIndex;
}
