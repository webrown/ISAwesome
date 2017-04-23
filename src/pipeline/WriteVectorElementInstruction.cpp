#include "WriteVectorElementInstruction.h"
#include "InstructionUtil.h"
void WriteVectorElementInstruction::decode(StageData *sd, Register *r, int *wait) {
  TernaryInstruction::decode(sd, r, wait);
  // First param must be scalar unless immediate
  if(!Register::isScalarIndex(sd->operand1) && !sd->isImmediate1) sd->broken = 1;
  // Middle param must be scalar int unless immediate
  if((!Register::isScalarIndex(sd->operand2) || !Register::isIntIndex(sd->operand2)) && sd->isImmediate2) sd->broken = 1;
  // Third param must be vector.
  if(!Register::isVectorIndex(sd->operand3)) sd->broken = 1;
  // First and third parameters must either both be floats or ints.
  if(Register::isFloatIndex(sd->operand1) != Register::isFloatIndex(sd->operand3)) sd->broken = 1;

  // Special case:  WVE's isImmediate1 is ignored.
  QVector<Value> pdvResult = pipelineDecideValue(sd->operand1, false, r, sd);
  if(pdvResult.size() == 0) {
    sd->broken = true;
  }
  else if(pdvResult.size() == 1) {
    sd->src = pdvResult.at(0);
  }
  else {
    sd->srcVec = pdvResult;
  }
}
void WriteVectorElementInstruction::execute(StageData *sd, int *wait) {
  *wait = 1;
  sd->destVec[sd->aux.i % sd->destVec.size()] = sd->src;
}
void WriteVectorElementInstruction::memory(StageData *sd, MemoryStructure *m, int *wait) {
  *wait = 0;
  (void) sd;
  (void) m;
}
void WriteVectorElementInstruction::writeBack(StageData *sd, Register *r, int *wait) {
  *wait = 1;
  r->write(sd->destVec, sd->operand3.i);
}
bool WriteVectorElementInstruction::decodeDump(StageData *sd, Register *r){
  // If scalar flag is 0, dump.
  return !sd->flagValue;
}
QVector<char> WriteVectorElementInstruction::registerDependencies(StageData *sd){
  QVector<char> result;
  result.push_back(sd->operand1.i); // ALWAYS depend on operand 1!!!
  if(!sd->isImmediate2) result.push_back(sd->operand2.i);
  result.push_back(sd->operand3.i);
  return result;
}
