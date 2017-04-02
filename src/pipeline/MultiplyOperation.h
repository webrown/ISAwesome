#ifndef MULTIPLY_OPERATION_H
#define MULTIPLY_OPERATION_H
#include "ArithmeticOperation.h"
class MultiplyOperation : public ArithmeticOperation{
    public:
        static MultiplyOperation singleton;
        Value scalarOperation(int a, int b, int *wait);
        Value scalarOperation(float a, float b, int *wait);
};
#endif
