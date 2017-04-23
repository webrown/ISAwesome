#include "LongArithmeticInstruction.h"

void LongArithmeticInstruction::scalarOperation(int *a, int *b, int *wait){
  *wait = 0;
  qDebug() << "COM: LongArithmeticInstruction: NOOPed int int";
  (void) a;
  (void) b;
  (void) wait;
}

void LongArithmeticInstruction::decode(StageData *sd, Register *r, int *wait){
  BinaryInstruction::decode(sd, r, wait);
  // Barf unless we're dealing with ints.
  if(Register::isFloatIndex(sd->operand1) || Register::isFloatIndex(sd->operand2) || !Register::indexExists(sd->operand1) || !Register::indexExists(sd->operand2)) {
    qDebug() << "COM:  LongArithmeticInstruction:  Can only work with int registers.";
    sd->broken = 1;
  }
  // No broadcasting or reducing is allowed.
  if(Register::isVectorIndex(sd->operand1) != Register::isVectorIndex(sd->operand2)) {
    qDebug() << "COM:  LongArithmeticInstruction:  Not able to broadcast or reduce for long ops.";
    sd->broken = 1;
  }
}

void LongArithmeticInstruction::execute(StageData *sd, int *wait){
  // Immediate is not a thing for longs.
  if(Register::isScalarIndex(sd->operand1) && Register::isScalarIndex(sd->operand2)) {
    //pure scalar operation
    if(sd->flagValue){
      int newArg1 = sd->src.i;
      int newArg2 = sd->dest.i;
      scalarOperation(&newArg1, &newArg2, wait);
      sd->src.i = newArg1;
      sd->dest.i = newArg2;
    }
  }
  else if( Register::isVectorIndex(sd->operand1) &&  Register::isVectorIndex(sd->operand2)) {
    // dot sd->operand1 with sd->operand2
    QVector<Value> result1;
    QVector<Value> result2;
    for(int i = 0; i < sd->destVec.size(); i++) {
      if(sd->flagValues.at(i)) {
        int newArg1 = sd->srcVec.at(i).i;
        int newArg2 = sd->destVec.at(i).i;
        scalarOperation(&newArg1, &newArg2, wait);
        sd->srcVec[i].i = newArg1;
        sd->destVec[i].i = newArg2;
      }
    }
  }
}

void LongArithmeticInstruction::memory(StageData *sd, MemoryStructure *ms, int *wait){
  *wait = 0;
  // Don't touch memory
  (void) sd;
  (void) ms;
}


void LongArithmeticInstruction::writeBack(StageData *sd, Register *r, int *wait){
  *wait = 2;
  qDebug() << "COM: LongArithmeticInstruction: About to write to" << sd->operand2.i;
  if(Register::isScalarIndex(sd->operand2)){
    r->write(sd->src, sd->operand1.i);
    r->write(sd->dest, sd->operand2.i);
  }
  if(Register::isVectorIndex(sd->operand2)){
    r->writeVector(sd->srcVec, sd->operand1.i);
    r->writeVector(sd->destVec, sd->operand2.i);
  }
  
}

QVector<char> LongArithmeticInstruction::registerDependencies(StageData *sd){
  QVector<char> result;
  // src reg (unless it's an immediate)
  result.push_back(sd->operand1.u);
  // Dest reg
  result.push_back(sd->operand2.u);
  return result;
}
QVector<char> LongArithmeticInstruction::registersToSet(StageData *sd){
  (void) sd;
  QVector<char> result;
  // Will change source
  result.push_back(sd->operand1.u);
  // Will change destination.
  result.push_back(sd->operand2.u);
  return result;
}
bool LongArithmeticInstruction::decodeDump(StageData *sd, Register *r){
  (void) r;
  (void) sd;
  // Too complex to dismiss as a noop.
  return false;
}
