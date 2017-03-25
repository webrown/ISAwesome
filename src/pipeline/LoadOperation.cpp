#include "LoadOperation.h"
#include "../memory/QueryResult.h"

void LoadOperation::memoryOperation(Register *registers, MemoryStructure *memory, unsigned int address, unsigned int registerIndex) {
  // Decide if you want a vector or a scalar and get 
  int dataRequested = Register::isVectorIndex(registerIndex)?VECTOR_SIZE:1;
  // Fetch from memory.
  QueryResult *qr = memory->getDataAccess()->read(address, dataRequested);
  // Place the value from memory into the register specified.
  if(dataRequested == 1) {
    registers->write(qr->result.at(0), registerIndex);
  }
  else {
    registers->write(qr->result, registerIndex);
  }
  // Cleanup.
  delete qr;
}
