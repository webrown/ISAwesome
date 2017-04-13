#include "AddInstruction.h"
Value AddInstruction::scalarOperation(int a, int b) {
  Value v;
  v.i = a+b;
  return v;
}

Value AddInstruction::scalarOperation(float a, float b) {
  Value v;
  v.f = a+b;
  return v;
}

Value AddInstruction::scalarOperation(int a, float b) {
  (void) a;
  Value v;
  v.f = b;
  return v;
}

Value AddInstruction::scalarOperation(float a, int b) {
  (void) a;
  Value v;
  v.i = b;
  return v;
}

Value AddInstruction::scalarOperation(bool arg1IsFloat, bool arg2IsFloat, Value a, Value b){
  if(!arg1IsFloat && !arg2IsFloat) return scalarOperation(a.i, b.i);
  if(!arg1IsFloat &&  arg2IsFloat) return scalarOperation(a.i, b.f);
  if( arg1IsFloat && !arg2IsFloat) return scalarOperation(a.f, b.i);
                                   return scalarOperation(a.f, b.f);
}

void AddInstruction::execute(StageData *sd){
  if(!Register::isVectorIndex(sd->operand1) && !Register::isVectorIndex(sd->operand2)) {
    //pure scalar operand
    if(sd->flagValue) sd->dest = scalarOperation(Register::isFloatIndex(sd->operand1), Register::isFloatIndex(sd->operand2), sd->src, sd->dest);
  }
  if(!Register::isVectorIndex(sd->operand1) &&  Register::isVectorIndex(sd->operand2)) {
    // broadcast sd->operand1 across sd->operand2
    QVector<Value> result;
    for(int i = 0; i < sd->destVec.size(); i++) {
      if(sd->flagValues.at(i)) result += scalarOperation(Register::isFloatIndex(sd->operand1), Register::isFloatIndex(sd->operand2), sd->src, sd->destVec.at(i));
      else result += sd->destVec.at(i);
    }
    sd->destVec = result;
  }
  if( Register::isVectorIndex(sd->operand1) && !Register::isVectorIndex(sd->operand2)) {
    // Reduce sd->operand1 onto sd->operand2
    for(int i = 0; i < sd->srcVec.size(); i++) {
      if(sd->flagValues.at(i)) sd->dest = scalarOperation(Register::isFloatIndex(sd->operand1), Register::isFloatIndex(sd->operand2), sd->srcVec.at(i), sd->dest);
    }
  }
  if( Register::isVectorIndex(sd->operand1) &&  Register::isVectorIndex(sd->operand2)) {
    // dot sd->operand1 with sd->operand2
    QVector<Value> result;
    for(int i = 0; i < sd->destVec.size(); i++) {
      if(sd->flagValues.at(i)) result += scalarOperation(Register::isFloatIndex(sd->operand1), Register::isFloatIndex(sd->operand2), sd->srcVec.at(i), sd->destVec.at(i));
      else result += sd->destVec.at(i);
    }
    sd->destVec = result;
  }
}

void AddInstruction::memory(StageData *sd, MemoryStructure *ms) {
  (void) sd;
  (void) ms;
}


void AddInstruction::writeBack(StageData *sd, Register *r){
  if(Register::isScalarIndex(sd->operand2)) r->write(sd->dest, sd->operand2.u);
  if(Register::isVectorIndex(sd->operand2)) r->writeVector(sd->destVec, sd->operand2.u);
  
}

QVector<char> AddInstruction::registerDependencies(StageData *sd){
  QVector<char> result;
  // src reg (unless it's an immediate)
  if(!sd->isImmediate1) result.push_back(sd->operand1.u);
  // Dest reg
  result.push_back(sd->operand2.u);
  return result;
}
QVector<char> AddInstruction::registersToSet(StageData *sd){
  (void) sd;
  QVector<char> result;
  // Will change destination.
  result.push_back(sd->operand2.u);
  return result;
}
bool AddInstruction::decodeDump(StageData *sd, Register *r){
  (void) r;
  (void) sd;
  // Too complex to dismiss as a noop.
  return false;
}
