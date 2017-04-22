#include "MemoryInstruction.h"
#include "../Utility.h"
#include "InstructionUtil.h"
void MemoryInstruction::decode(StageData *sd, Register *r) {
  BinaryInstruction::decode(sd, r);

  // Both params are translated.
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
  // Translate second param.
  pdvResult = pipelineDecideValue(sd->operand2, false, r, sd);
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
