#include "CompareInstruction.h"

using namespace Flag;
Value CompareInstruction::newFlag(int a, int b, int *wait) {
  qDebug() << "COM: CompareInstruction:newFlag(" << a << "," << b << "," << wait << ")";
  Value result;
  result.asUInt = 0;
  if(a == b) result = add(result, EQ);
  if(a != b) result = add(result, NE);
  if(a <= b) result = add(result, LE);
  if(a >= b) result = add(result, GE);
  if(a <  b) result = add(result, LT);
  if(a >  b) result = add(result, GT);
  result = add(result, AL);
  *wait = 4;
  return result;
}

Value CompareInstruction::newFlag(float a, float b, int *wait) {
  Value result;
  result.asUInt = 0;
  if(a == b) result = add(result, EQ);
  if(a != b) result = add(result, NE);
  if(a <= b) result = add(result, LE);
  if(a >= b) result = add(result, GE);
  if(a <  b) result = add(result, LT);
  if(a >  b) result = add(result, GT);
  result = add(result, AL);
  *wait = 8;
  return result;
}


Value CompareInstruction::newFlag(bool arg1IsFloat, bool arg2IsFloat, Value a, Value b, Value oldFlag, int *wait){
  if(!arg1IsFloat && !arg2IsFloat) return newFlag(a.i, b.i, wait);
  if( arg1IsFloat &&  arg2IsFloat) return newFlag(a.f, b.f, wait);
                                   return oldFlag;
}


void CompareInstruction::decode(StageData *sd, Register *r) {
  qDebug() << "COM: CompareInstruction: decode";
  BinaryInstruction::decode(sd, r);
  // Also want to remember the flags.
  sd->aux = r->readFlag();
  sd->auxVec = r->readFlags();
}

void CompareInstruction::execute(StageData *sd) {
  qDebug() << "COM: CompareInstruction: execute";
  int w;
  int *wait = &w; // Trash value for now, only to allow code reuse.
  if(!Register::isVectorIndex(sd->operand1) && !Register::isVectorIndex(sd->operand2)) {
    //pure scalar operation
    sd->aux = newFlag(Register::isFloatIndex(sd->operand1), Register::isFloatIndex(sd->operand2), sd->src, sd->dest, sd->aux, wait);
qDebug() << "((((((((((((((((((((((((((((((((((((((((((";
  }
  if(!Register::isVectorIndex(sd->operand1) &&  Register::isVectorIndex(sd->operand2)) {
    // broadcast sd->operand1 across sd->operand2
    QVector<Value> result;
    for(int i = 0; i < sd->destVec.size(); i++) {
      result += newFlag(Register::isFloatIndex(sd->operand1), Register::isFloatIndex(sd->operand2), sd->src, sd->destVec.at(i), sd->auxVec.at(i), wait);
    }
    sd->auxVec = result;
  }
  if( Register::isVectorIndex(sd->operand1) && !Register::isVectorIndex(sd->operand2)) {
    // broadcast sd->operand2 across sd->operand1
    QVector<Value> result;
    for(int i = 0; i < sd->srcVec.size(); i++) {
      result += newFlag(Register::isFloatIndex(sd->operand1), Register::isFloatIndex(sd->operand2), sd->srcVec.at(i), sd->dest, sd->auxVec.at(i), wait);
    }
    sd->auxVec = result;
  }
  if( Register::isVectorIndex(sd->operand1) &&  Register::isVectorIndex(sd->operand2)) {
    // dot sd->operand1 with sd->operand2
    QVector<Value> result;
    for(int i = 0; i < sd->destVec.size(); i++) {
      result += newFlag(Register::isFloatIndex(sd->operand1), Register::isFloatIndex(sd->operand2), sd->srcVec.at(i), sd->destVec.at(i), sd->auxVec.at(i), wait);
    }
    sd->auxVec = result;
  }
}

void CompareInstruction::memory(StageData *sd, MemoryStructure *m) {
  qDebug() << "COM: CompareInstruction: memory";
  (void) sd;
  (void) m;
}
void CompareInstruction::writeBack(StageData *sd, Register *r) {
  qDebug() << "COM: CompareInstruction: writeBack";
  r->writeFlag(sd->aux);
  r->writeFlags(sd->auxVec);
}
QVector<char> CompareInstruction::registerDependencies(StageData *sd){
  QVector<char> result;
  // src reg (unless it's an immediate)
  if(!sd->isImmediate1) result.push_back(sd->operand1.u);
  // Dest reg
  result.push_back(sd->operand2.u);
  return result;
}
QVector<char> CompareInstruction::registersToSet(StageData *sd){
  (void) sd;
  QVector<char> result;
  result.push_back(-1); // -1 = flags
  return result;
}
bool CompareInstruction::decodeDump(StageData *sd, Register *r){
  (void) r;
  // If scalar flag is 0, dump.
  return !sd->flagValue;
}
