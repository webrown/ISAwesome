#include "Shift.h"
#include "../memory/Value.h"
#include <QVector>
#include <QDebug>
void Shift::execute(Register *registers, bool arg1IsImmediate, int arg1, int arg2, int scale) {
  // Doesn't make sense to shift on a scalar.
  if(Register::isScalarIndex(arg2) || !Register::indexExists(arg2)) return;
  // Init new vector.
  Value zero;
  zero.i = 0;
  QVector<Value> newVector(registers->readVector(arg2).size(), zero);
  // Substitute.
  for(int i = 0; i < registers->readVector(arg2).size(); i++) {
    int shiftAmount = arg1;
    if(!arg1IsImmediate && Register::indexExists(arg1)) {
      // We gotta substitute for arg1!
      if(Register::isScalarIndex(arg1)) {
        shiftAmount = registers->read(arg1).i;
      }
      else {
        shiftAmount = registers->readVector(arg1).at(i).i;
      }
    }
    int newIndex = (i+shiftAmount*scale+newVector.size()) % newVector.size();
qDebug() << "newIndex = " << newIndex;
    newVector[newIndex] = registers->readVector(arg2).at(i);
  }
  registers->writeVector(newVector, arg2);
}

void Shift::executeUp(Register *registers, bool arg1Immediate, int arg1, int arg2) {
  execute(registers, arg1Immediate, arg1, arg2, 1);
}
void Shift::executeDown(Register *registers, bool arg1Immediate, int arg1, int arg2) {
  execute(registers, arg1Immediate, arg1, arg2, -1);
}
