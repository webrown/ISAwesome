#include "LoadOperation.h"
#include "../memory/QueryResult.h"

LoadOperation LoadOperation::singleton;

void LoadOperation::memoryOperation(Register *registers, MemoryStructure *memory, unsigned int address, unsigned int registerIndex, int *wait) {
  // Decide if you want a vector or a scalar and get 
  int dataRequested = Register::isVectorIndex(registerIndex)?VECTOR_SIZE:1;
  // Fetch from memory.
  QueryResult *qr = memory->getDataAccess()->read(address, dataRequested);
  *wait = 2+0+qr->time+1;
  // For code flexibility...
  QVector<Value> filteredResult;
  for(int i = 0; i < qr->result.size(); i+=1) {
    filteredResult.push_back(qr->result.at(i));
  }
  // Place the value from memory into the register specified.
  if(dataRequested == 1) {
    registers->write(qr->result.at(0), registerIndex);
  }
  else {
    registers->write(filteredResult, registerIndex);
  }
  // Cleanup.
  delete qr;
}
