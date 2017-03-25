#include "CompareOperation.h"
#include "../memory/Flag.h"

using namespace Flag;

Value CompareOperation::newFlag(int a, int b) {
  Value result;
  result.asUInt = 0;
  if(a == b) result = add(result, EQ);
  if(a != b) result = add(result, NE);
  if(a <= b) result = add(result, LE);
  if(a >= b) result = add(result, GE);
  if(a <  b) result = add(result, LT);
  if(a >  b) result = add(result, GT);
  result = add(result, AL);
  return result;
}

Value CompareOperation::newFlag(float a, float b) {
  Value result;
  result.asUInt = 0;
  if(a == b) result = add(result, EQ);
  if(a != b) result = add(result, NE);
  if(a <= b) result = add(result, LE);
  if(a >= b) result = add(result, GE);
  if(a <  b) result = add(result, LT);
  if(a >  b) result = add(result, GT);
  result = add(result, AL);
  return result;
}


Value CompareOperation::newFlag(bool arg1IsFloat, bool arg2IsFloat, Value a, Value b, Value oldFlag){
  if(!arg1IsFloat && !arg2IsFloat) return newFlag(a.i, b.i);
  if( arg1IsFloat &&  arg2IsFloat) return newFlag(a.f, b.f);
                                   return oldFlag;
}

void CompareOperation::execute(Register *registers, bool arg1IsImmediate, unsigned int arg1, unsigned int arg2){
  if(arg1IsImmediate) {
    // Immediate operations
    Value arg1Value;
    arg1Value.asUInt = arg1;
    if(Register::isVectorIndex(arg2)) {
      // immediate is being broadcast
      QVector<Value> result;
      for(int i = 0; i < registers->readVector(arg2).size(); i++) {
        result += newFlag(Register::isFloatIndex(arg2), Register::isFloatIndex(arg2), arg1Value, registers->readVector(arg2).at(i), registers->readFlags().at(i));
      }
      registers->writeFlags(result);
    }
    else {
      // immediate is being applied to scalar
      registers->writeFlag(newFlag(Register::isFloatIndex(arg1), Register::isFloatIndex(arg2), arg1Value, registers->read(arg2), registers->readFlag()));
    }
  }
  else {
    // Non-immediate operations
    if(!Register::isVectorIndex(arg1) && !Register::isVectorIndex(arg2)) {
      //pure scalar operation
      registers->writeFlag(newFlag(Register::isFloatIndex(arg1), Register::isFloatIndex(arg2), registers->read(arg1), registers->read(arg2), registers->readFlag()));
    }
    if(!Register::isVectorIndex(arg1) &&  Register::isVectorIndex(arg2)) {
      // broadcast arg1 across arg2
      QVector<Value> result;
      for(int i = 0; i < registers->readVector(arg2).size(); i++) {
        result += newFlag(Register::isFloatIndex(arg1), Register::isFloatIndex(arg2), registers->read(arg1), registers->readVector(arg2).at(i), registers->readFlags().at(i));
      }
      registers->writeFlags(result);
    }
    if( Register::isVectorIndex(arg1) && !Register::isVectorIndex(arg2)) {
      // Reduce arg1 onto arg2
      QVector<Value> result;
      for(int i = 0; i < registers->readVector(arg2).size(); i++) {
        result += newFlag(Register::isFloatIndex(arg1), Register::isFloatIndex(arg2), registers->readVector(arg1).at(i), registers->read(arg2), registers->readFlags().at(i));
      }
      registers->writeFlags(result);
    }
    if( Register::isVectorIndex(arg1) &&  Register::isVectorIndex(arg2)) {
      // dot arg1 with arg2
      QVector<Value> result;
      for(int i = 0; i < registers->readVector(arg2).size(); i++) {
        result += newFlag(Register::isFloatIndex(arg1), Register::isFloatIndex(arg2), registers->readVector(arg1).at(i), registers->readVector(arg2).at(i), registers->readFlags().at(i));
      }
      registers->writeFlags(result);
    }
  }
}
