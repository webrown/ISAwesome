#ifndef TOFLOAT_OPERATION_H
#define TOFLOAT_OPERATION_H
#include "ArithmeticOperation.h"
class ToFloatOperation : public ArithmeticOperation{
    public:
        static ToFloatOperation singleton;
        Value scalarOperation(int a, int b);
        Value scalarOperation(float a, int b);
        Value scalarOperation(int a, float b);
        Value scalarOperation(float a, float b);
};
#endif
