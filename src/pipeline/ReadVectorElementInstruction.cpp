#include "ReadVectorElementInstruction.h"
#include "InstructionUtil.h"
void ReadVectorElementInstruction::decode(StageData *sd, Register *r, int *wait){
  TernaryInstruction::decode(sd, r, wait);
  qDebug() << "COM: ReadVectorElementInstruction: In decode.";
  // First param must be vector
  if(!Register::isVectorIndex(sd->operand1)) sd->broken = 1;
  // Middle param must be scalar int unless immediate
  if((!Register::isScalarIndex(sd->operand2) || !Register::isIntIndex(sd->operand2)) && sd->isImmediate2) sd->broken = 1;
  // Third param must be scalar.
  if(!Register::isScalarIndex(sd->operand3)) sd->broken = 1;
  // First and third parameters must either both be floats or ints.
  if(Register::isFloatIndex(sd->operand1) != Register::isFloatIndex(sd->operand3)) sd->broken = 1;

  // Special case:   isImmediate1 is ignored.
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
void ReadVectorElementInstruction::execute(StageData *sd, int *wait){
  *wait = 1;
  sd->dest = sd->srcVec.at(sd->aux.i % sd->srcVec.size());
}
void ReadVectorElementInstruction::memory(StageData *sd, MemoryStructure *m, int *wait){
  *wait = 0;
  (void) sd;
  (void) m;
}
void ReadVectorElementInstruction::writeBack(StageData *sd, Register *r, int *wait){
  *wait = 1;
  qDebug() << "COM: ReadVectorElementInstruction: About to replace" << r->read(sd->operand3.i).i << "with" << sd->dest.i << "at index" << sd->operand3.i;
  r->write(sd->dest, sd->operand3.i);
  qDebug() << "COM: ReadVectorElementInstruction: Now we have" << r->read(sd->operand3.i).i << "at index" << sd->operand3.i;
}
bool ReadVectorElementInstruction::decodeDump(StageData *sd, Register *r){
  // If scalar flag is 0, dump.
  return !sd->flagValue;
}
QVector<char> ReadVectorElementInstruction::registerDependencies(StageData *sd){
  QVector<char> result;
  result.push_back(sd->operand1.i);
  if(!sd->isImmediate2) result.push_back(sd->operand2.i);
  return result;
}
