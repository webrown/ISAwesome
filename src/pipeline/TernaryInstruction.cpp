#include "TernaryInstruction.h"
#include "../Utility.h"
#include "InstructionUtil.h"
void TernaryInstruction::decode(StageData *sd, Register *r, int *wait){
  *wait = 3;
  uint nextInstruction = sd->instruction;
  sd->operand1.i = spliceMachineCode(nextInstruction, 15, 20);
  sd->operand2.i = spliceMachineCode(nextInstruction, 8, 13);
  sd->operand3.i = spliceMachineCode(nextInstruction, 0, 4);
  sd->isImmediate1 = !spliceMachineCode(nextInstruction, 21, 21);
  sd->isImmediate2 = !spliceMachineCode(nextInstruction, 14, 14);

  // Translate first param
  QVector<Value> pdvResult = pipelineDecideValue(sd->operand1, sd->isImmediate1, r, sd);
  if(pdvResult.size() == 0) {
    sd->broken = true;
  }
  else if(pdvResult.size() == 1) {
    sd->src = pdvResult.at(0);
  }
  else {
    sd->srcVec = pdvResult;
  }
  // Translate second param.
  pdvResult = pipelineDecideValue(sd->operand2, sd->isImmediate2, r, sd);
  if(pdvResult.size() == 0) {
    sd->broken = true;
  }
  else if(pdvResult.size() == 1) {
    sd->aux = pdvResult.at(0);
  }
  else {
    sd->auxVec = pdvResult;
  }
  // Translate third param.
  pdvResult = pipelineDecideValue(sd->operand3, false, r, sd);
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

QVector<char> TernaryInstruction::registerDependencies(StageData *sd){
  QVector<char> result;
  if(!sd->isImmediate1) result.push_back(sd->operand1.i);
  if(!sd->isImmediate2) result.push_back(sd->operand2.i);
  result.push_back(sd->operand3.i);
  return result;
}

QVector<char> TernaryInstruction::registersToSet(StageData *sd){
  QVector<char> result;
  result.push_back(sd->operand3.i);
  return result;
}
