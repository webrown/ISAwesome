#include "BranchAndLinkInstruction.h"
#include "InstructionUtil.h"
void BranchAndLinkInstruction::decode(StageData *sd, Register *r, int *wait) {
  UnaryInstruction::decode(sd, r, wait);
  *wait = 2;
  // Barf if register is a vector.
  if(Register::isVectorIndex(sd->operand1) || !Register::indexExists(sd->operand1)) sd->broken = 1;
  // Load
  QVector<Value> pdvResult = pipelineDecideValue(Register::PC, false, r, sd);
  if(pdvResult.size() == 0) {
    sd->broken = true;
  }
  else if(pdvResult.size() == 1) {
    sd->aux = pdvResult.at(0);
  }
  else {
    sd->auxVec = pdvResult;
  }

  pdvResult = pipelineDecideValue(sd->operand1, false, r, sd);
  if(pdvResult.size() == 0) {
    sd->broken = true;
  }
  else if(pdvResult.size() == 1) {
    sd->dest = pdvResult.at(0);
  }
  else {
    sd->destVec = pdvResult;
  }
}
void BranchAndLinkInstruction::execute(StageData *sd, int *wait) {
  *wait = 1;
  (void) sd;
}
void BranchAndLinkInstruction::memory(StageData *sd, MemoryStructure *m, int *wait) {
  *wait = 0;
  (void) sd;
  (void) m;
}
void BranchAndLinkInstruction::writeBack(StageData *sd, Register *r, int *wait) {
  *wait = 2;
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
