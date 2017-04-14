#include "InstructionUtil.h"
#include <QDebug>
QVector<Value> pipelineDecideValue(Value operand, bool isImmediate, Register *r){
  qDebug() << "COM: pipelineDecideValue(" << operand.i << "," << isImmediate << "," << r << ")";
  QVector<Value> result;
  if(isImmediate) {
    result.push_back(operand);
    return result;
  }
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
