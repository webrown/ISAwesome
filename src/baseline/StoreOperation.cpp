#include "StoreOperation.h"
#include "../memory/QueryResult.h"
#include <QDebug>

StoreOperation StoreOperation::singleton;

void StoreOperation::memoryOperation(Register *registers, MemoryStructure *memory, unsigned int address, unsigned int registerIndex, int *wait) {
  QVector<Value> data;
  if(Register::isVectorIndex(registerIndex)) {
    // You're writting a whole VECTOR_SIZE vector!
    data = registers->readVector(registerIndex);
  }
  else {
    // You're writing just a single value.
    data += registers->read(registerIndex);
  }
  // Space out for byte addressing.
  QVector<Value> filteredData;
  for(int i = 0; i < data.size(); i++) {
    filteredData.push_back(data.at(i));
  }
  // Put in data.
  *wait = memory->getDataAccess()->write(&filteredData, address);
}
