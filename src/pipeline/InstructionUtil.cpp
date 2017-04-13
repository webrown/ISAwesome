#include "InstructionUtil.h"
QVector<Value> pipelineDecideValue(Value operand, bool isImmediate, Register *r){
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
