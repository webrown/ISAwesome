#ifndef SUBTRACT_OPERATION_H
#define SUBTRACT_OPERATION_H
#include "ArithmeticOperation.h"
class SubtractOperation : public ArithmeticOperation{
    public:
        static SubtractOperation singleton;
        Value scalarOperation(int a, int b);
        Value scalarOperation(float a, float b);
};
#endif
