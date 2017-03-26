#include "StoreOperation.h"
#include "../memory/QueryResult.h"

StoreOperation StoreOperation::singleton;

void StoreOperation::memoryOperation(Register *registers, MemoryStructure *memory, unsigned int address, unsigned int registerIndex) {
  QVector<Value> data;
  if(Register::isVectorIndex(registerIndex)) {
    // You're writting a whole VECTOR_SIZE vector!
    data = registers->readVector(registerIndex);
  }
  else {
    // You're writing just a single value.
    data += registers->read(registerIndex);
  }
  memory->getDataAccess()->write(&data, address);
}
