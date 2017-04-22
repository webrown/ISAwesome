#include "StoreInstruction.h"

void StoreInstruction::decode(StageData *sd, Register *r) {
  qDebug() << "COM: StoreInstruction: decode";
  BinaryInstruction::decode(sd, r);
}

void StoreInstruction::execute(StageData *sd) {
  qDebug() << "COM: StoreInstruction: execute";
  (void) sd;
}

void StoreInstruction::memory(StageData *sd, MemoryStructure *m) {
  qDebug() << "COM: StoreInstruction: memory";
  // Write to memory.
  QVector<Value> data;
  if(Register::isVectorIndex(sd->operand1)) {
    m->getDataAccess()->write(&sd->srcVec, sd->dest.u);
  }
  else {
    m->getDataAccess()->write(sd->src, sd->dest.u);
  }
}

void StoreInstruction::writeBack(StageData *sd, Register *r) {
  qDebug() << "COM: StoreInstruction: writeBack";
  (void) sd;
  (void) r;
}

QVector<char> StoreInstruction::registerDependencies(StageData *sd){
  QVector<char> result;
  // src reg (unless it's an immediate)
  if(!sd->isImmediate1) result.push_back(sd->operand1.u);
  // Dest reg
  result.push_back(sd->operand2.u);
  return result;
}
QVector<char> StoreInstruction::registersToSet(StageData *sd){
  (void) sd;
  QVector<char> result;
  return result;
}
bool StoreInstruction::decodeDump(StageData *sd, Register *r){
  (void) r;
  // If scalar flag is 0, dump.
  return !sd->flagValue;
}
