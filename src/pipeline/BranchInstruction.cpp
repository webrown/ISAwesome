#include "BranchInstruction.h"
void BranchInstruction::decode(StageData *currData, Register *registers) {
  UnaryInstruction::decode(currData, registers);
  currData->dest = currData->operand1;
  currData->src.asUInt = registers->getPC();
  currData->destReg= Register::PC;
  currData->regInUse = 0;
}
void BranchInstruction::execute(StageData *sd) {
  (void) sd;
}
void BranchInstruction::memory(StageData *sd, MemoryStructure *m) {
  (void) sd;
  (void) m;
}
void BranchInstruction::writeBack(StageData *sd, Register *r) {
  r->write(sd->dest, Register::PC);
}
QVector<char> BranchInstruction::registerDependencies(StageData *sd){
  QVector<char> result;
  result.push_back(Register::PC);
  return result;
}
QVector<char> BranchInstruction::registersToSet(StageData *sd){
  QVector<char> result;
  result.push_back(Register::PC);
  return result;
}
bool BranchInstruction::useFlag(void){
  return true;
}
bool BranchInstruction::useFlags(void){
  return false;
}
