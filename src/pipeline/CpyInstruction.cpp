#include "CpyInstruction.h"
#include <QDebug>

Value CpyInstruction::scalarOperation(int a, int b) {
  Value v;
  v.i = a;
qDebug() << "GOT HERE---------------------------------------------------------------------------";
  return v;
}

Value CpyInstruction::scalarOperation(float a, float b) {
  Value v;
  v.f = a;
qDebug() << "GOT HERE---------------------------------------------------------------------------";
  return v;
}

