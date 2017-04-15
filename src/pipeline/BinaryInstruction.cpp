#include "BinaryInstruction.h"
#include "../Utility.h"
#include "InstructionUtil.h"
void BinaryInstruction::decode(StageData *sd, Register *r) {
  uint nextInstruction = sd->instruction;
  sd->operand1.i = spliceMachineCode(nextInstruction, 5, 20);
  sd->operand2.i = spliceMachineCode(nextInstruction, 0, 4);
  sd->isImmediate1 = !spliceMachineCode(nextInstruction, 21, 21);

  qDebug() << "COM: BinaryInstruction: operand1=" << sd->operand1.i;
  qDebug() << "COM: BinaryInstruction: operand2=" << sd->operand2.i;
  qDebug() << "COM: BinaryInstruction: isImmediate1=" << sd->isImmediate1;

  // Translate first param. (not required by binaries, but pretty universal)
  QVector<Value> pdvResult = pipelineDecideValue(sd->operand1, sd->isImmediate1, r);
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
  pdvResult = pipelineDecideValue(sd->operand2, false, r);
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
