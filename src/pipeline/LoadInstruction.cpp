#include "LoadInstruction.h"

void LoadInstruction::execute(StageData *sd) {
  qDebug() << "COM: LoadInstruction: execute";
  (void) sd;
}

void LoadInstruction::memory(StageData *sd, MemoryStructure *m) {
  qDebug() << "COM: LoadInstruction: memory";
  // Decide if you want a vector or a scalar and get 
  int dataRequested = Register::isVectorIndex(sd->operand2.u)?VECTOR_SIZE:1;
  // Fetch from memory.
  QueryResult *qr = m->getDataAccess()->read(sd->src.u, dataRequested);
  // Place the value from memory into the register specified.
  if(dataRequested == 1) {
    sd->aux = qr->result.at(0);
  }
  else {
    sd->auxVec = qr->result;
  }
  // Cleanup.
  delete qr;
}

void LoadInstruction::writeBack(StageData *sd, Register *r) {
  qDebug() << "COM: LoadInstruction: writeBack";
  if(Register::isScalarIndex(sd->operand2.u)) {
    r->write(sd->aux, sd->operand2.u);
  }
  else {
    r->write(sd->auxVec, sd->operand2.u);
  }
}

QVector<char> LoadInstruction::registerDependencies(StageData *sd){
  QVector<char> result;
  // src reg
  result.push_back(sd->operand1.u);
  return result;
}
QVector<char> LoadInstruction::registersToSet(StageData *sd){
  (void) sd;
  QVector<char> result;
  // Dest reg
  result.push_back(sd->operand2.u);
  return result;
}
bool LoadInstruction::decodeDump(StageData *sd, Register *r){
  (void) r;
  // If scalar flag is 0, dump.
  return !sd->flagValue;
}
