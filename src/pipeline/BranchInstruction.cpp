#include "BranchInstruction.h"
void BranchInstruction::decode(StageData *currData, Register *registers, int *wait){
  UnaryInstruction::decode(currData, registers, wait);
  currData->dest = currData->operand1;
  currData->src.asUInt = registers->getPC();
  currData->destReg= Register::PC;
  currData->regInUse = 0;
}
void BranchInstruction::execute(StageData *sd, int *wait){
  *wait = 0;
  (void) sd;
}
void BranchInstruction::memory(StageData *sd, MemoryStructure *m, int *wait){
  *wait = 0;
  (void) sd;
  (void) m;
}
void BranchInstruction::writeBack(StageData *sd, Register *r, int *wait){
  *wait = 1;
  r->write(sd->dest, Register::PC);
}
QVector<char> BranchInstruction::registerDependencies(StageData *sd){
  (void) sd;
  QVector<char> result;
  result.push_back(Register::PC);
  return result;
}
QVector<char> BranchInstruction::registersToSet(StageData *sd){
  (void) sd;
  QVector<char> result;
  result.push_back(Register::PC);
  return result;
}
bool BranchInstruction::decodeDump(StageData *sd, Register *r){
  (void) r;
  // If scalar flag is 0, dump.
  return !sd->flagValue;
}
