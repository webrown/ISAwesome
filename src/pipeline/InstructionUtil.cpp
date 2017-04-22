#include "InstructionUtil.h"
#include "../memory/Register.h"
#include <QDebug>
QVector<Value> pipelineDecideValue(Value operand, bool isImmediate, Register *r, StageData *sd){
  qDebug() << "COM: pipelineDecideValue(" << operand.i << "," << isImmediate << "," << r << ")";
  QVector<Value> result;
  if(isImmediate) {
    result.push_back(operand);
    return result;
  }
//  // PC is a scary register that may have changed by now.  SPECIAL CASE!!! :D
//  if(operand.u == Register::PC){
//      Value v;
//      v.i = sd->instructionAddress;
//      result.push_back(v);
//      return result;
//  }
  // Non-PC case.  Dependency system will keep us safe!
  if(Register::indexExists(operand)){
    if(Register::isScalarIndex(operand)){
      result.push_back(r->read(operand));
      return result;
    }
    if(Register::isVectorIndex(operand)){
      return r->readVector(operand);
    }
  }
  return result; // Return empty.
}

QVector<Value> pipelineDecideValue(int operand, bool isImmediate, Register *r, StageData *sd){
  Value v;
  v.i = operand;
  return pipelineDecideValue(v, isImmediate, r, sd);
}
