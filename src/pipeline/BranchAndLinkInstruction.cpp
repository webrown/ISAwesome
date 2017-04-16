#include "BranchAndLinkInstruction.h"
void BranchAndLinkInstruction::decode(StageData *sd, Register *r) {
  UnaryInstruction::decode(sd, r);
  // Barf if register is a vector.
  if(Register::isVectorIndex(sd->operand1) || !Register::indexExists(sd->operand1)) sd->broken = 1;
  // Load
  sd->aux = r->read(Register::PC);
  sd->dest = r->read(sd->operand1);
}
void BranchAndLinkInstruction::execute(StageData *sd) {
  (void) sd;
}
void BranchAndLinkInstruction::memory(StageData *sd, MemoryStructure *m) {
  (void) sd;
  (void) m;
}
void BranchAndLinkInstruction::writeBack(StageData *sd, Register *r) {
  r->write(sd->aux, Register::LR);
  r->write(sd->dest, Register::PC);
}
QVector<char> BranchAndLinkInstruction::registerDependencies(StageData *sd){
  (void) sd;
  QVector<char> result;
  result.push_back(Register::PC);
  result.push_back(sd->operand1.i);
  return result;
}
QVector<char> BranchAndLinkInstruction::registersToSet(StageData *sd){
  (void) sd;
  QVector<char> result;
  result.push_back(Register::PC);
  result.push_back(Register::LR);
  return result;
}
bool BranchAndLinkInstruction::decodeDump(StageData *sd, Register *r){
  (void) r;
  // If scalar flag is 0, dump.
  return !sd->flagValue;
}
