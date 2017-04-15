#include "DivideOperation.h"
#include <QDebug>
#include <limits>

DivideOperation DivideOperation ::singleton;

Value DivideOperation::scalarOperation(int a, int b, int *wait){
  Value v;
  if(a == 0) {
    // /0 is just big number.
    if(b > 0) {
      v.i = 2147483647;
    }
    if(b == 0) {
      v.i = 0;
    }
    if(b < 0) {
      v.i = -2147483648;
    }
  }
  else {
    // Save division.
    v.i = b / a;
  }
  *wait = 4;
  return v;
}

Value DivideOperation::scalarOperation(float a, float b, int *wait){
  Value v;
  if(a == 0) {
    // /0 is just big number.
    if(b > 0) {
      v.f = std::numeric_limits<float>::infinity();
    }
    if(b == 0) {
      v.f = 0;
    }
    if(b < 0) {
      v.f = -std::numeric_limits<float>::infinity();
    }
  }
  else {
    // Save division.
    v.f = b / a;
  }
  *wait = 8;
  return v;
}

