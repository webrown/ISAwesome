#include "LongOperation.h"
#include <QDebug>
#include "../Utility.h"

void LongOperation::scalarOperation(int *a, int *b){
  qDebug() << "COM: LongOperation: NOOPed int int";
  (void) a;
  (void) b;
}

void LongOperation::execute(Register *registers, unsigned int arg1, unsigned int arg2, bool flag, QBitArray flags){
  // Barf unless we're dealing with ints.
  if(Register::isFloatIndex(arg1) || Register::isFloatIndex(arg2) || !Register::indexExists(arg1) || !Register::indexExists(arg2)) {
    qDebug() << "COM:  LongOperation:  Can only work with int registers.";
    return;
  }
  // Immediate is not a thing for longs.
  if(Register::isScalarIndex(arg1) && Register::isScalarIndex(arg2)) {
    //pure scalar operation
    if(flag){
      int newArg1 = registers->read(arg1).i;
      int newArg2 = registers->read(arg2).i;
      scalarOperation(&newArg1, &newArg2);
      registers->write(newArg1, arg1);
      registers->write(newArg2, arg2);
    }
  }
  else if( Register::isVectorIndex(arg1) &&  Register::isVectorIndex(arg2)) {
    // dot arg1 with arg2
    QVector<Value> result1;
    QVector<Value> result2;
    for(int i = 0; i < registers->readVector(arg2).size(); i++) {
      if(flags.at(i)) {
        int newArg1 = registers->readVector(arg1).at(i).i;
        int newArg2 = registers->readVector(arg2).at(i).i;
        scalarOperation(&newArg1, &newArg2);
        Value v;
        v.i = newArg1;
        result1 += v;
        v.i = newArg2;
        result2 += v;
      }
      else {
        result1 += registers->readVector(arg1).at(i);
        result2 += registers->readVector(arg2).at(i);
      }
    }
    registers->writeVector(result1, arg1);
    registers->writeVector(result2, arg2);
  }
  else {
    qDebug() << "COM:  LongOperation:  Can only work completely with scalars or completely with vectors.";
  }
}

