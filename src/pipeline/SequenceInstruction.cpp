#include "SequenceInstruction.h"
void SequenceInstruction::decode(StageData *sd, Register *r) {
  UnaryInstruction::decode(sd, r);
  if(!Register::indexExists(sd->operand1)) sd->broken = 1;
  if(Register::isScalarIndex(sd->operand1)) sd->broken = 1;
}
void SequenceInstruction::execute(StageData *sd) {
  qDebug() << "COM: SequenceInstruction: execute";
  // Generate.
  sd->destVec.clear();
  for(int i = 0; i < VECTOR_SIZE; i++) {
    Value v;
    if(Register::isFloatIndex(sd->operand1)) {
      qDebug() << "COM: SequenceInstruction: working with float";
      v.f = i;
    }
    else {
      qDebug() << "COM: SequenceInstruction: working with int";
      v.i = i;
    }
    sd->destVec += v;
  }
}
void SequenceInstruction::memory(StageData *sd, MemoryStructure *m) {
  (void) sd;
  (void) m;
}
void SequenceInstruction::writeBack(StageData *sd, Register *r) {
  qDebug() << "COM: SequenceInstruction: writing to" << sd->operand1.i;
  r->write(sd->destVec, sd->operand1.i);
}
QVector<char> SequenceInstruction::registerDependencies(StageData *sd){
  (void) sd;
  // None at all.
  QVector<char> result;
  return result;
}
QVector<char> SequenceInstruction::registersToSet(StageData *sd){
  (void) sd;
  QVector<char> result;
  result.push_back(Register::PC);
  return result;
}
bool SequenceInstruction::decodeDump(StageData *sd, Register *r){
  (void) r;
  // If scalar flag is 0, dump.
  return !sd->flagValue;
}
