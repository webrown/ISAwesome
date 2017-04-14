#include "ShortArithmeticInstruction.h"
Value ShortArithmeticInstruction::scalarOperation(int a, int b) {
  qDebug() << "COM: ShortArithmeticInstruction: scalarOperation(int, int) NOOPed out";
  Value v;
  v.i = b;
  return v;
}

Value ShortArithmeticInstruction::scalarOperation(float a, float b) {
  qDebug() << "COM: ShortArithmeticInstruction: scalarOperation(float, float) NOOPed out";
  Value v;
  v.f = b;
  return v;
}

Value ShortArithmeticInstruction::scalarOperation(int a, float b) {
  qDebug() << "COM: ShortArithmeticInstruction: scalarOperation(int, float) NOOPed out";
  (void) a;
  Value v;
  v.f = b;
  return v;
}

Value ShortArithmeticInstruction::scalarOperation(float a, int b) {
  qDebug() << "COM: ShortArithmeticInstruction: scalarOperation(float, int) NOOPed out";
  (void) a;
  Value v;
  v.i = b;
  return v;
}

Value ShortArithmeticInstruction::scalarOperation(bool arg1IsFloat, bool arg2IsFloat, Value a, Value b){
  if(!arg1IsFloat && !arg2IsFloat) return scalarOperation(a.i, b.i);
  if(!arg1IsFloat &&  arg2IsFloat) return scalarOperation(a.i, b.f);
  if( arg1IsFloat && !arg2IsFloat) return scalarOperation(a.f, b.i);
                                   return scalarOperation(a.f, b.f);
}

void ShortArithmeticInstruction::execute(StageData *sd){
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

void ShortArithmeticInstruction::memory(StageData *sd, MemoryStructure *ms) {
  // Don't touch memory
  (void) sd;
  (void) ms;
}


void ShortArithmeticInstruction::writeBack(StageData *sd, Register *r){
  qDebug() << "COM: ShortArithmeticInstruction: About to write to" << sd->operand2.i;
  if(Register::isScalarIndex(sd->operand2)){
    qDebug() << "COM: ShortArithmeticInstruction: " << sd->operand2.i << "started at" << r->read(sd->operand2).i;
    r->write(sd->dest, sd->operand2.u);
    qDebug() << "COM: ShortArithmeticInstruction: " << sd->operand2.i << "was changed to" << r->read(sd->operand2).i;
  }
  if(Register::isVectorIndex(sd->operand2)){
    qDebug() << "COM: ShortArithmeticInstruction: " << sd->operand2.i << "[0] started at" << r->readVector(sd->operand2).at(0).i;
    r->writeVector(sd->destVec, sd->operand2.u);
    qDebug() << "COM: ShortArithmeticInstruction: " << sd->operand2.i << "[0] was changed to" << r->readVector(sd->operand2).at(0).i;
  }
  
}

QVector<char> ShortArithmeticInstruction::registerDependencies(StageData *sd){
  QVector<char> result;
  // src reg (unless it's an immediate)
  if(!sd->isImmediate1) result.push_back(sd->operand1.u);
  // Dest reg
  result.push_back(sd->operand2.u);
  return result;
}
QVector<char> ShortArithmeticInstruction::registersToSet(StageData *sd){
  (void) sd;
  QVector<char> result;
  // Will change destination.
  result.push_back(sd->operand2.u);
  return result;
}
bool ShortArithmeticInstruction::decodeDump(StageData *sd, Register *r){
  (void) r;
  (void) sd;
  // Too complex to dismiss as a noop.
  return false;
}
